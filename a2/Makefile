#
# Assignment #2 - Program Actuator and Microshell 
# CS 570 Summer 2019 
# Christian De La Torre - cssc 0786 
# Ernesto Parra - cssc 0787
# Makefile
# IMPORTANT INFORMATION: EXECUTABLE PROGRAM CAN BE FOUND INSIDE OF THE CLASS ACCOUNT CSSC0786 WHICH IS CHRISTIAN DE LA TORRE

pam: tokenizer.o main.o processor.o
	g++ -std=c++11 tokenizer.o main.o processor.o -o pam -lreadline

tokenizer.o: tokenizer.cpp tokenizer.hpp
	g++ -std=c++11 -c tokenizer.cpp

main.o: tokenizer.hpp processor.hpp main.cpp
	g++ -std=c++11 -c main.cpp

processor.o: processor.hpp processor.cpp
	g++ -std=c++11 -c processor.cpp