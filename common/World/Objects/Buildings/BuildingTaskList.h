#pragma once

class BuildingTask {
public:
	int id;		                 // ID задачи
	int quantity;                // количество повторов
	int counter;                 // счетчик длительности
	int duration;                // длительность , максимальное значение счетчика
	int state;                   // ?
	BuildingTask* next;          // для списка
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
