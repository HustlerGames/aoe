#pragma once

#include "../CollectionNode.h"
#include "../Structures.h"

class AnimationResource : public CollectionNode
{
public:
	float speed = 1;
	int pass = 0;
	int frames_count = 0;
	int bufferID = 0;
	Frame* pFrames = nullptr;
};
