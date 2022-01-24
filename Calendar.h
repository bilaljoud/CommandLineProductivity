#ifndef CALENDAR
#define CALENDAR

#include <vector>
#include "Entry.h"

#define DAYSINMONTH 31

// forward declaration
class Display;

// class definition
class Calendar
{
private:
    std::vector<CalEntry> entries;

public:
    Calendar()
    {
        for (int i = 1; i < DAYSINMONTH + 1; i++)
        {
            CalEntry entry = CalEntry(i);
            entries.push_back(entry);
        }
    }

    CalEntry& operator[](const int i)
    {
        return entries.at(i - 1);
    }

};

#endif