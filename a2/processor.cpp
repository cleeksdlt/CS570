#include "processor.hpp"
#include <string>
#include <list>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

/*
 * Assignment #2 - Program Actuator and Microshell 
 * CS 570 Summer 2019 
 * Christian De La Torre - cssc 0786 
 * Ernesto Parra - cssc 0787
 * processor.cpp
 * IMPORTANT INFORMATION: EXECUTABLE PROGRAM CAN BE FOUND INSIDE OF THE CLASS ACCOUNT CSSC0786 WHICH IS CHRISTIAN DE LA TORRE
 */

void processor::execute_process(list<string> *tokens) {

    const int MAX_ARGUMENTS = 100;
    char **argv = new char*[MAX_ARGUMENTS+1];
    int argcounter = 0;
    bool ignoreflag = false;

    list<string>::iterator iterate = tokens->begin();
    while(iterate != tokens->end()) {

        //Value of the current pointer
        string token = *iterate;

        //Check for pipe argument
        if(token == "|") {
            cout << "Pipe encountered" << endl;
        }

        //Check for other symbols
        else if(token == "<" || token == ">" || token == "&" || token == ";") {
            cout << "Special symbols: [< > & ;] are not implemented" << endl;

            if(token == "<" || token == ">")
                ignoreflag = true;
        }

        else if(!ignoreflag) {
            //Too many arguments; then fail
            if(argcounter == MAX_ARGUMENTS) {
                cout << "Error: too many arguments" << endl;
                delete[] argv;
                return;
            }
            //Start of a new argument
            char *arg = new char[token.length()+1];
            strcpy(arg, token.c_str());
            argv[argcounter++] = arg;
        }
        iterate++;
    }
    //Add last argument and add null to the end
    argv[argcounter] = NULL;
    start(argv);
    delete[] argv;
}

//Method for executing and running pipes
void processor::execute(int argc, char **argv) {
    pid_t pid;
    int stat;
    int fd[2];

    if((pipe(fd)) < 0) {
        perror("Pipe Error");
        exit(EXIT_FAILURE);
    }

    if((pid = fork()) < 0) {
        cout << "Unable to fork" << endl;
        exit(EXIT_FAILURE);
    }

    //Child Process
    else if(pid == 0) {
        close(1);
        dup(fd[1]);
        close(fd[0]);
        if(execvp(argv[0], argv) < 0) {
            printf("Unable to execute %s\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    //Parent Process
    else {
        while(wait(&stat) != pid);
        if(stat == 0) {
            close(0);
            dup(fd[0]);
            close(fd[1]);
            cout << "Success" << endl;
        } else {
            cout << "Failure" << endl;
        }
    }

}

//Method for executing all other arguments
void processor::start(char **argv) {
    pid_t pid;
    int stat;
    
    if((pid = fork()) < 0) {
        cout << "Unable to fork" << endl;
    }

    //Child Process
    else if(pid == 0) {
        //Child process could not start, exit normally
        if(execvp(argv[0], argv) < 0) {
            printf("Unable to execute %s\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    //Parent Process
    else {
        while(wait(&stat) != pid);
        if(stat == 0) {
            cout << "Process was a success" << endl;
        }
    }
}