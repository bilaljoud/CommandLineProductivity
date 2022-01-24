#ifndef ENTRYIO
#define ENTRYIO

#include "Entry.h"
#include "Week.h"
#include <iostream>
#include <vector>
#include <fstream>

class EntryIO {
public:
    static void read_entry(Week& w);
    static void read_entry(Calendar& cal);
    static void write_entry(Week& w);
    static void write_entry(Calendar& cal);
};

#endif