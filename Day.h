#ifndef DAY
#define DAY

#include "TaskList.h"
#include "Display.h"
#include <algorithm>
#include <iostream>

// subclass definition
class Day : public TaskList
{
private:
    tm date;

public:
    // constructors
    Day(tm date_, std::vector<Task> t) : TaskList(t)
    {
        list = t;
        date = date_;
    };
    Day() : TaskList()
    {
        date.tm_mday = 0;
        date.tm_wday = 0;
    }

    // member functions with definitions
    tm get_date()
    {
        return date;
    }
    void markComplete(int i)
    {
        list[i - 1].set_complete(true);
    }

    void get_complete()
    {
        std::cout << " Completed Tasks " << std::endl;
        for (int i = 0; i < (int)list.size(); i++)
            if (list[i].isComplete() == true)
                std::cout << " - " + list[i].get_name() << std::endl;
    }

    Task operator+=(const Task t)
    {
        list.push_back(t);
        return t;
    }

    friend class Display;
};

#endif