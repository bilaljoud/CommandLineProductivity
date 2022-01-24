#include "Entry.h"
#include <string>

time_t cur = time(NULL);
tm *now = localtime(&cur);

// function definitions
std::string Entry::get_name()
{
    return name;
}
void Entry::set_name(std::string n)
{
    name = n;
}
void Entry::operator=(const std::string &s)
{
    set_name(s);
}

// constructor
Task::Task(std::string n, tm d, bool c, unsigned short p)
{
    name = n;
    due = d;
    complete = c;
    priority = p;
}
Task::Task()
{
    name = "";
    priority = 0;
    complete = false;
    due.tm_mday = 0;
    due.tm_hour = 0;
    due.tm_min = 0;
}
// member functions
std::string Task::get_name()
{
    return name;
}
void Task::set_due(tm due_)
{
    due = due_;
}
tm Task::get_due()
{
    // return std::to_string(due.tm_hour) + ":" + std::to_string(due.tm_min);
    return due;
}
bool Task::isComplete()
{
    return complete;
}
void Task::set_complete(bool val)
{
    complete = val;
}
bool Task::operator==(const Task t)
{
    if ((name == t.name) && (priority == (t.priority)) && (complete == (t.complete)) && (due.tm_mday == t.due.tm_mday))
    {
        return true;
    }
    else
        return false;
}
int Task::get_priority() { return priority; }

// constructor
CalEntry::CalEntry(int day_, std::string name_, std::string note_)
{
    name = name_;
    date.tm_mday = day_;
    date.tm_mon = now->tm_mon;
    note = note_;
}
// member functions
std::string CalEntry::get_name() { return name; }
void CalEntry::set_note(std::string note_) { note = note_; }
std::string CalEntry::get_note() { return note; }
int CalEntry::get_day() { return date.tm_mday; }
