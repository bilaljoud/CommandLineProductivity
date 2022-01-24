#ifndef ENTRY
#define ENTRY

#include <string>
#include <ctime>

// forward declaration
class Display;

// abstract class definition
class Entry
{
protected:
    std::string name;

public:
    // pure virtual function
    virtual std::string get_name() = 0;

    void set_name(std::string s);
    void operator=(const std::string &s);
};

// Subclass
class Task : public Entry
{
private:
    tm due;
    bool complete;
    unsigned short priority;

public:
    // constructor(s)
    Task(std::string n, tm d, bool c = false, unsigned short p = 0);
    Task();

    // overriding parent virtual function
    std::string get_name() override;

    // getters, setters, and other useful functions
    void set_due(tm due_);
    tm get_due();
    void set_complete(bool val);
    bool isComplete();
    int get_priority();
    bool operator==(const Task t);

    friend class Display;
};

// Subclass
class CalEntry : public Entry
{
private:
    tm date;
    std::string note;

public:
    // constructor
    CalEntry(int day_, std::string name_ = "", std::string n = "");

    //overriding parent virtual function
    std::string get_name() override;

    // getters, setters, and other useful functions
    void set_note(std::string note_);
    std::string get_note();
    int get_day();

    // friend class
    friend class Display;
};

#endif