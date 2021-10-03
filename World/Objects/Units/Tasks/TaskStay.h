#pragma once

#include "Task.h"
#include "../Unit.h"

class TaskStay : public Task
{
public:
    TaskStay(Unit* unit);
    int execute();
    void set(StructTask* s);
};

