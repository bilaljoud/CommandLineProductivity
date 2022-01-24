// headers
#include <iostream>
#include <iomanip>
#include "Entry.h"
#include "Display.h"

using namespace std;

time_t current = time(NULL);
tm *now_ = localtime(&current);

// Displays an individual task
void Display::display_task(Task t)
{
    // printing task info
    cout << " Name:  " << t.name << endl
         << " Priority: " << t.priority << endl
         << " Due: ";
    // if default case then displays n/a
    if (t.due.tm_hour == 0 && t.due.tm_min == 0)
        cout << "N/A" << endl;
    else
        cout << t.get_due().tm_hour << ":" << t.get_due().tm_min << endl;
}

// Displays an individual calendar entry
void Display::display_cal_entry(CalEntry c)
{
    cout << " Day: " << c.date.tm_mday << endl
         << " Name: " << c.name << endl
         << " Note: " << c.note << endl
         << endl;
}

// Displays all the tasks for a given day
void Display::display_day(Day d)
{
    cout << endl;

    // deletes any tasks without a name so they don't show up
    for (int i = 0; i < (int)d.list.size(); i++)
        if (d.list[i].name == "")
            d.delete_task(i);
    

    if (d.list.size() != 0)
    {
        // prints a table with task, priority, and time due
        cout << left << setw(25) << " TASKS" << left << setw(12) << "PRIORITY" << left << setw(10) << "DUE" << endl;
        cout << left << setw(25) << " ====================" << left << setw(12) << "========" << left << setw(10) << "=====" << endl;
        //
        for (int i = 0; i < (int)d.list.size(); i++)
        {
            // only displays non-complete tasks
            if (d[i].complete == false)
            {
                cout << " ";
                cout << left << setw(25) << to_string((i + 1)) + ". " + d[i].name
                     << setw(12) << d[i].get_priority();

                // if default case, prints N/A
                if (d[i].get_due().tm_hour == 0 && d[i].get_due().tm_min == 0)
                    cout << "N/A";
                // if task due before current time
                else if (d[i].due.tm_hour < now_->tm_hour || (d[i].due.tm_hour == now_->tm_hour && d[i].due.tm_min < now_->tm_min))
                    cout << "OVERDUE";
                else
                    cout << d.list[i].get_due().tm_hour << ":" << d.list[i].get_due().tm_min;

                cout << endl;
            }
        }
    }
    else
    {
        cout << " NO TASKS" << endl;
    }
    cout << endl;
}

// function that displays the tasks for each day from today until the following week
void Display::display_week(Week &w)
{
    cout << " WEEK: " << endl
         << endl;

    string day_of_the_week;

    // printing logic
    for (int i = 0; i < 7; i++)
    {
        if (i == 0)
            cout << " TODAY -";
        else if (i == 1)
            cout << " TOMORROW -";

        switch (w[i].date.tm_wday)
        {
        case 0:
            cout << " SUNDAY - ";
            break;
        case 1:
            cout << " MONDAY - ";
            break;
        case 2:
            cout << " TUESDAY - ";
            break;
        case 3:
            cout << " WEDNESDAY - ";
            break;
        case 4:
            cout << " THURSDAY - ";
            break;
        case 5:
            cout << " FRIDAY - ";
            break;
        case 6:
            cout << " SATURDAY - ";
            break;
        }
        cout << w[i].date.tm_mon + 1 << "/" << w[i].date.tm_mday - 1 << endl
             << " ----------";

        // printing a day's tasks
        display_day(w.week[i]);
    }
}

void Display::display_month()
{
    // displays the in-built *NIX calendar
    system("cal");
}