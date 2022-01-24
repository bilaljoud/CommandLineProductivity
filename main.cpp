/*
 * Author: Bilal Joud
 * Purpose: The purpose of this program is to serve as a productivity application 
 *          that uses task lists, due dates, prioritization, and a calendar. 
 *          Built using Object-oriented concepts learned throughout the course
 * 
 */

//headers
#include <iostream>
#include <ctime>
#include <limits>
#include "Entry.h"
#include "TaskList.h"
#include "Calendar.h"
#include "EntryIO.h"
#include "Day.h"
#include "Week.h"
#include "Calendar.h"
#include "Display.h"

using namespace std;

//function declaration
char choicesFunction(string, string, char, string = "", string = "", string = "", string = "");

//main
int main()
{
    // title
    cout << endl
         << " Todo + Calendar Program" << endl
         << " -----------------------" << endl
         << endl;

    // getting current date and time
    time_t time_ = time(NULL);
    tm *today = localtime(&time_);
    int today_ = today->tm_mday;

    // creating and displaying calendar object
    Calendar cal;
    Display::display_month();

    // creating a week object
    Week week;

    // reading entries from text file
    EntryIO::read_entry(cal);
    EntryIO::read_entry(week);

    // main program loop
    while (true)
    {
        int day_choice;
        cout << " Select day (0 to quit): ";
        while (!(cin >> day_choice))
        {
            cout << " Please enter an integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        while (day_choice > 31 || day_choice < 0)
        {
            cout << " Please enter an integer between 1 and 31: ";
            cin >> day_choice;
        }

        if (day_choice == 0)
        {
            // control goes to end of program
            break;
        }

        // while the input is valid
        while (true)
        {
            char choice1;
            int week_index;

            // if the input is within 7 days, gives the option for task operations
            if ((day_choice >= today_) && (day_choice <= today_ + 6))
            {
                choice1 = choicesFunction("Tasks", "Calendar", choice1);
                week_index = day_choice - today_;
            }
            else
            {
                choice1 = 'b';
            }

            if (choice1 == 'a')
            {
                // displays the tasks for chosen the day
                Display::display_day(week[week_index]);

                // task options
                char choice2;
                choice2 = choicesFunction("Create task", "Delete Task", choice2, "Mark Complete", "View task", "View all Tasks", "View Completed Tasks");

                if (choice2 == 'a')
                {
                    // this block of text is for data input
                    cin.ignore();
                    string name;
                    unsigned short priority;
                    tm due;
                    cout << " Task name: ";
                    getline(cin, name);
                    cout << " Priority (1-4): ";
                    while (!(cin >> priority))
                        cout << " Enter valid number";
                    cout << " Due (24 hr time) [if N/A input 00:00]: ";
                    due.tm_mday = day_choice;
                    cin >> due.tm_hour;
                    cin.ignore(1);
                    cin >> due.tm_min;

                    // instantiating task object using given data
                    Task newTsk(name, due, false, priority);

                    // adds it to the tasks for the given day in the week
                    week[week_index] += newTsk;

                    // sorting the list
                    week[week_index].sort_list();

                    // confirmation
                    cout << endl
                         << " Task Created!" << endl;
                }
                else if (choice2 == 'b')
                {
                    // user input
                    int tasknum;
                    cout << " Which task do you want to delete?: ";
                    while (!(cin >> tasknum))
                        cout << " Enter valid number: ";

                    // task deletion
                    week[week_index].delete_task(tasknum);

                    cout << " Task Deleted!" << endl;
                }
                else if (choice2 == 'c')
                {
                    //displaying all tasks and asking which task to mark complete
                    int taskNum;
                    Display::display_day(week[week_index]);
                    cout << " Which task to mark complete?: ";
                    while (!(cin >> taskNum))
                        cout << " Enter valid number: ";
                    week[week_index].markComplete(taskNum);
                    week[week_index].sort_list();

                    cout << " Complete!" << endl;
                }
                else if (choice2 == 'd')
                {
                    int tasknum;
                    cout << " Which task would you like to see?: ";
                    while (!(cin >> tasknum))
                        cout << " Enter valid number: ";

                    // displays single task
                    Display::display_task(week[week_index][tasknum - 1]);
                }
                else if (choice2 == 'e')
                {
                    char choice3;
                    choice3 = choicesFunction("Day View", "Week View", choice3);
                    if (choice3 == 'a')
                        Display::display_day(week[week_index]);
                    else
                        Display::display_week(week);
                }
                else if (choice2 == 'f')
                {
                    week[week_index].get_complete();
                }
                else if (choice2 == 'q')
                    break;
            }
            else if (choice1 == 'b')
            {
                char choice2;
                choice2 = choicesFunction("Edit Entry", "View Entry", choice2, "View Calendar");

                if (choice2 == 'a')
                {
                    string name, note;

                    cin.ignore();

                    cout << " Enter name: ";
                    getline(cin, name, '\n');
                    cout << " Enter note(s): ";
                    getline(cin, note);

                    cal[day_choice].set_name(name);
                    cal[day_choice].set_note(note);
                }
                else if (choice2 == 'b')
                    Display::display_cal_entry(cal[day_choice]);
                else if (choice2 == 'c')
                    Display::display_month();
                else if (choice2 == 'q')
                    break;
            }
            else if (choice1 == 'q')
                break;
            else
            {
                cout << " Please enter a valid choice: ";
                cin >> choice1;
            }
        }
    }

    EntryIO::write_entry(cal);
    EntryIO::write_entry(week);

    return 0;
}

// function to simplify input and output choices
char choicesFunction(string choiceA, string choiceB, char userPick, string choiceC, string choiceD, string choiceE, string choiceF)
{
    if (choiceC == "")
    {
        cout << endl
             << " Options (q to quit):" << endl
             << " a. " << choiceA << endl
             << " b. " << choiceB << endl
             << endl;
        cout << " Choice: ";
        cin >> userPick;
        while (!(userPick == 'a' || userPick == 'b' || userPick == 'q'))
        {
            cout << "Invalid selection, try again: ";
            cin >> userPick;
        }
    }
    else if (choiceD == "")
    {
        cout << endl
             << " Options (q to quit):" << endl
             << " a. " << choiceA << endl
             << " b. " << choiceB << endl
             << " c. " << choiceC << endl
             << endl;
        cout << " Choice: ";
        cin >> userPick;
        while (!(userPick == 'a' || userPick == 'b' || userPick == 'c' || userPick == 'q'))
        {
            cout << "Invalid selection, try again: ";
            cin >> userPick;
        }
    }
    else if (choiceE == "")
    {
        cout << endl
             << " Options (q to quit):" << endl
             << " a. " << choiceA << endl
             << " b. " << choiceB << endl
             << " c. " << choiceC << endl
             << " d. " << choiceD << endl
             << endl;
        cout << "Choice: ";
        cin >> userPick;
        while (!(userPick == 'a' || userPick == 'b' || userPick == 'c' || userPick == 'd' || userPick == 'q'))
        {
            cout << "Invalid selection, try again: ";
            cin >> userPick;
        }
    }
    else if (choiceF == "")
    {
        cout << endl
             << " Options (q to quit):" << endl
             << " a. " << choiceA << endl
             << " b. " << choiceB << endl
             << " c. " << choiceC << endl
             << " d. " << choiceD << endl
             << " e. " << choiceE << endl
             << endl;
        cout << "Choice: ";
        cin >> userPick;
        while (!(userPick == 'a' || userPick == 'b' || userPick == 'c' || userPick == 'd' || userPick == 'q' || userPick == 'e'))
        {
            cout << "Invalid selection, try again: ";
            cin >> userPick;
        }
    }
    else
    {
        cout << endl
             << " Options (q to quit):" << endl
             << " a. " << choiceA << endl
             << " b. " << choiceB << endl
             << " c. " << choiceC << endl
             << " d. " << choiceD << endl
             << " e. " << choiceE << endl
             << " f. " << choiceF << endl
             << endl;
        cout << " Choice: ";
        cin >> userPick;
        while (!(userPick == 'a' || userPick == 'b' || userPick == 'c' || userPick == 'd' || userPick == 'q' || userPick == 'e' || userPick == 'f'))
        {
            cout << "Invalid selection, try again: ";
            cin >> userPick;
        }
    }
    cout << endl;

    return userPick;
}
