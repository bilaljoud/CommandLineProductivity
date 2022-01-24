#ifndef DISPLAY
#define DISPLAY

// necessary headers
#include "Entry.h"
#include "Day.h"
#include "Week.h"
#include "Calendar.h"

// forward declarations
class Day;
class Week;

// class definition
class Display {
public:
    static void display_task(Task t);
    static void display_cal_entry(CalEntry c);
    static void display_day(Day d);
    static void display_week(Week& w);
    static void display_month();
};

#endif