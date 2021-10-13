#pragma once

class BuildingTask {
public:
	int id;		                 // ID ������
	int quantity;                // ���������� ��������
	int counter;                 // ������� ������������
	int duration;                // ������������ , ������������ �������� ��������
	int state;                   // ?
	BuildingTask* next;          // ��� ������
	BuildingTask* prev;          //
};

class BuildingTaskList
{
public:
	void add(BuildingTask* task);
	void remove(BuildingTask* task);
	~BuildingTaskList();

	BuildingTask* root = nullptr;
	BuildingTask* end = nullptr;	
};
