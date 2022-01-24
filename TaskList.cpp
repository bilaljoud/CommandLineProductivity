#include "TaskList.h"
#include <iostream>

// constructor(s)
TaskList::TaskList(std::vector<Task> t) {
    list = t;
}
// default constructor
TaskList::TaskList() {
    Task t;
    list = { t };
}

std::vector<Task> TaskList::get_list() {
    return list;
}

// sorting algorithm
void TaskList::sort_list() { 
    Task tmp = list[0];

    for (int i = 1; i < (int)list.size(); i++) {
        if (list[i - 1].get_priority() > list[i].get_priority() || list[i-1].isComplete()) {
            list[i-1] = list[i];
            list[i] = tmp;
            tmp = list[i];
        } else 
            continue;
    }
}

// delete task
void TaskList::delete_task(int taskNum) {
    list.erase(list.begin() + (taskNum - 1));
}

//operator overloading
Task& TaskList::operator[](const int i) {
    return list.at(i);
}