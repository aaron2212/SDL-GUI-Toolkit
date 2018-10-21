#ifndef _PROGRAM_H
#define _PROGRAM_H

#include "window.h"

class Program
{
    public:
        Program(); // Program that accepts no command line arguments
        Program(int argc, char** argv); // Program that accepts command line arguments
        void run(); // Run the program
        void pollEvent(); // Poll for an event and handle it

    private:
        int _argc = 0; // The number of command line arguments
        char** _argv = NULL; // The command line arguments
};

#endif