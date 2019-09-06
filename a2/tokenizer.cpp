#include "tokenizer.hpp"
#include <string>
#include <list>

using namespace std;

/*
 * Assignment #2 - Program Actuator and Microshell 
 * CS 570 Summer 2019 
 * Christian De La Torre - cssc 0786 
 * Ernesto Parra - cssc 0787
 * tokenizer.cpp
 * IMPORTANT INFORMATION: EXECUTABLE PROGRAM CAN BE FOUND INSIDE OF THE CLASS ACCOUNT CSSC0786 WHICH IS CHRISTIAN DE LA TORRE
 */

//Check for special characters
bool tokenizer::isSpecial(char c) {
    return c == '|' || c == ';' || c == '<' || c == '>' || c == '&';
}

list<string>* tokenizer::tokenize(char *line) {
    //List of tokens to be collected
    list<string> *tokens = new list<string>();

    //Token to be constructed and added to tokens
    string token = "";

    //Current character in the input line
    char c;

    while((c = *line++) != '\0') {
        //Encountered whitespace
        if(isspace(c)) {
            if(token.length() != 0) {
                tokens->push_back(token);
                token = "";
            }
            
        }
        //Encountered special character
        else if (isSpecial(c)) {
            token.push_back(c);
            if(token.length() != 0) {
                tokens->push_back(token);
                token = "";
            }
        } 
        //All other conditions
        else {
            token.push_back(c);
        }
    }

    //Add last token to list
    if(token.length() > 0) {
        tokens->push_back(token);
    }

    return tokens;
}