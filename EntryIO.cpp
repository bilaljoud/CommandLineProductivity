#include "EntryIO.h"
#include <ctime>
#include <limits>
using namespace std;

// today's date and time
time_t time_ = time(NULL);
tm *today = localtime(&time_);

// definition
void EntryIO::read_entry(Week &w)
{
    // opening file
    ifstream file;
    file.open("tasks.txt");

    // if file opened successfully, read data, otherwise throw exception
    if (file)
    {
        bool complete;
        string name;
        tm due;
        int priority;

        // while its not end of file
        while (!file.eof())
        {
            // reading data
            if (getline(file, name, '\t'))
            {
                file >> complete >> priority >> due.tm_mon;
                file.ignore(1);
                file >> due.tm_mday >> due.tm_hour;
                file.ignore(1);
                file >> due.tm_min;
                file.ignore();

                if (due.tm_mday < today->tm_mday || due.tm_mon <= today->tm_mon)
                    continue;

                // create Task object
                Task t = Task(name, due, complete, priority);

                w[0] += t;
            }
        }
        file.close();
    }
    else
    {
        throw runtime_error("Error: Unable to open file");
    }
}
void EntryIO::read_entry(Calendar &cal)
{
    ifstream file;
    file.open("cal.txt");
    if (file)
    {
        string name, note;
        int day;
        while (!file.eof())
        {
            if (getline(file, name, '\t'))
            {
                getline(file, note, '\t');
                file >> day;
                file.ignore();

                cal[day].set_name(name);
                cal[day].set_note(note);
            }
        }
        file.close();
    }
}

void EntryIO::write_entry(Week &w)
{
    // open file for writing to
    ofstream file;
    file.open("tasks.txt");
    if (file)
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < (int)w[i].get_list().size(); i++)
            {
                Task task = w[i][j];
                // writing data
                file << task.get_name() << "\t" << task.get_priority() << "\t" << task.isComplete() << "\t" << task.get_due().tm_mon
                     << "/" << task.get_due().tm_mday << "\t" << task.get_due().tm_hour << ":" << task.get_due().tm_min << "\n";
            }
        }
    }
    file.close();
}
void EntryIO::write_entry(Calendar &cal)
{
    ofstream file;
    file.open("cal.txt");
    for (int i = 1; i < DAYSINMONTH + 1; i++)
    {
        if (file)
        {
            file << cal[i].get_name() << "\t" << cal[i].get_note() << "\t" << cal[i].get_day() << "\n";
        }
    }
    file.close();
}
