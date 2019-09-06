#include <iostream>
#include <fstream>
#include <readline/readline.h>
#include "tokenizer.hpp"
#include "processor.hpp"
#include <list>
#include <string>

using namespace std;

/*
 * Assignment #2 - Program Actuator and Microshell 
 * CS 570 Summer 2019 
 * Christian De La Torre - cssc 0786 
 * Ernesto Parra - cssc 0787
 * main.cpp
 * IMPORTANT INFORMATION: EXECUTABLE PROGRAM CAN BE FOUND INSIDE OF THE CLASS ACCOUNT CSSC0786 WHICH IS CHRISTIAN DE LA TORRE
 */

int main(int argc, char const* argv[]) {
    char *input;
    //Read in input and check for an exit
    while(strncmp((input = readline("cssc0786:")), "exit", 4)) {
        tokenizer tokenizer;
        //Call tokenizer class
        list<string> *tokens = tokenizer.tokenize(input);
        processor process;
        //Call processor class
        process.execute_process(tokens);
        delete tokens;
        free(input);
    }
    cout << "Aborting program" << endl;
    return 0;
}