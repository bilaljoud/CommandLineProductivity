#ifndef TASKLIST
#define TASKLIST

// headers
#include <vector>
#include "Entry.h"

// forward declaration
class Display;

class TaskList
{
protected:
    std::vector<Task> list;

public:
    TaskList(std::vector<Task> t);
    TaskList();

    //member functions
    std::vector<Task> get_list();
    void delete_task(int taskNum);
    void sort_list();
    void operator+=(const Task &t);
    Task &operator[](const int i);

    // firend class
    friend class Display;
};

#endif