#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <string>
#include <list>

using namespace std;

/*
 * Assignment #2 - Program Actuator and Microshell 
 * CS 570 Summer 2019 
 * Christian De La Torre - cssc 0786 
 * Ernesto Parra - cssc 0787
 * processor.hpp
 * IMPORTANT INFORMATION: EXECUTABLE PROGRAM CAN BE FOUND INSIDE OF THE CLASS ACCOUNT CSSC0786 WHICH IS CHRISTIAN DE LA TORRE
 */

typedef enum {
    Default,
    Read,
    Write
} direction_t;

class processor {
    private:
        void execute(int argc, char **argv);
        void start(char **argv);
    public:
        void execute_process(list<string> *tokens);

};

#endif