#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string>
#include <list>

using namespace std;

/*
 * Assignment #2 - Program Actuator and Microshell 
 * CS 570 Summer 2019 
 * Christian De La Torre - cssc 0786 
 * Ernesto Parra - cssc 0787
 * tokenizer.hpp
 * IMPORTANT INFORMATION: EXECUTABLE PROGRAM CAN BE FOUND INSIDE OF THE CLASS ACCOUNT CSSC0786 WHICH IS CHRISTIAN DE LA TORRE
 */

class tokenizer {
private:
    bool isSpecial(char c);
public:
    list<string> *tokenize(char *line);
};

#endif