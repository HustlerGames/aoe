#include "AudioSystem.h"

#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'

class VoiceCallback : public IXAudio2VoiceCallback
{
public:
    GameSound* parent = nullptr;
    
    VoiceCallback()  {}
    ~VoiceCallback() {  }

    //Called when the voice has just finished playing a contiguous audio stream.
    void STDMETHODCALLTYPE OnStreamEnd() {  }

    //Unused methods are stubs
    void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() { }
    void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 SamplesRequired) {    }
    void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext) { }
    void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext) {    }
    void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext) { 
        parent->pSourceVoice->Stop();
        parent->state = SOUND_STOPPED;
    }
    void STDMETHODCALLTYPE OnVoiceError(void* pBufferContext, HRESULT Error) { }
};



HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());
    DWORD dwRead;
    if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
        hr = HRESULT_FROM_WIN32(GetLastError());
    return hr;
}

HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
    HRESULT hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                hr = HRESULT_FROM_WIN32(GetLastError());
            break;

        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
                return HRESULT_FROM_WIN32(GetLastError());
        }

        dwOffset += sizeof(DWORD) * 2;

        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;

        if (bytesRead >= dwRIFFDataSize) return S_FALSE;

    }

    return S_OK;

}

bool ReadWaveFile(TCHAR* filename, void* wfx, XAUDIO2_BUFFER* buffer)
{
    HANDLE hFile = CreateFile(
        filename,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (INVALID_HANDLE_VALUE == hFile)
        return false;

    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return false;


    DWORD dwChunkSize;
    DWORD dwChunkPosition;
    //check the file type, should be fourccWAVE or 'XWMA'
    FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
    DWORD filetype;
    ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
    if (filetype != fourccWAVE)
        return false;

    FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
    ReadChunkData(hFile, wfx, dwChunkSize, dwChunkPosition);

    //fill out the audio data buffer with the contents of the fourccDATA chunk
    FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
    BYTE* pDataBuffer = new BYTE[dwChunkSize];
    ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

    buffer->AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
    buffer->pAudioData = pDataBuffer;  //buffer containing audio data
    buffer->Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

    CloseHandle(hFile);
}

GameSound::~GameSound()
{
    if (pSourceVoice)
    {
        pSourceVoice->DestroyVoice();
    }
}

void AudioSystem::play(unsigned int id)
{
    if (sounds[id])
    {
        if (sounds[id]->state == SOUND_STOPPED)
        {
            sounds[id]->pSourceVoice->Start();
            sounds[id]->state = SOUND_PLAYING;
        }
    }
}

AudioSystem::AudioSystem()
{
    
}


void AudioSystem::loadSounds()
{
    sounds[SOUND_PICK1] = createSound(TEXT("d:\\projects\\testgame\\repo\\data\\sounds\\pick1.wav"));
    sounds[SOUND_BACKGROUND1] = createSound(TEXT("d:\\projects\\testgame\\repo\\data\\sounds\\background1.wav"));
    sounds[SOUND_HARVEST_TREE] = createSound(TEXT("d:\\projects\\testgame\\repo\\data\\sounds\\harvest_tree1.wav"));
    sounds[SOUND_BUSH] = createSound(TEXT("d:\\projects\\testgame\\repo\\data\\sounds\\bush.wav"));
    sounds[SOUND_BUILD] = createSound(TEXT("d:\\projects\\testgame\\repo\\data\\sounds\\build.wav"));
    sounds[SOUND_BUILDING] = createSound(TEXT("d:\\projects\\testgame\\repo\\data\\sounds\\building.wav"));
}

bool AudioSystem::init()
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    pXAudio2->CreateMasteringVoice(&pMasterVoice);


    loadSounds();

    CoUninitialize();

    return true;
}

GameSound* AudioSystem::createSound(const TCHAR* filename)
{
    GameSound* gSound = new GameSound;

    VoiceCallback* callbackObj = new VoiceCallback;
    callbackObj->parent = gSound;

    ReadWaveFile(_wcsdup(filename), &gSound->wfx, &gSound->buffer);
    gSound->buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
    pXAudio2->CreateSourceVoice(&gSound->pSourceVoice, (WAVEFORMATEX*)&gSound->wfx,0,2.0f, callbackObj);
    gSound->pSourceVoice->SubmitSourceBuffer(&gSound->buffer);
    return gSound;
}

AudioSystem::~AudioSystem()
{
    for (int i = 0; i < 3; i++) {
        if (sounds[i]) {
            delete sounds[i];
        }
    }

    if (pMasterVoice)
    {
        pMasterVoice->DestroyVoice();
    }

    if (pXAudio2)
    {
        pXAudio2->Release();
        pXAudio2 = nullptr;
    }
}

bool AudioSystem::LoadSound(unsigned int id, const TCHAR* filename)
{
    if (sounds[id] == nullptr)
    {
        sounds[id] = createSound(filename);
        return true;
    }

    return false;
}