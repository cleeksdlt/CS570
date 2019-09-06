#include <iostream>
#include <fstream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>

using namespace std;

/*
 *Authors: Christian De La Torre and Ernesto Parra
 *Class Acount: cssc0786 and cssc0787
 *Class: CS570, Summer 2019
 *Assignment: Assignment #3, Event Management Program
 *main.cpp
 */

sem_t FLAG;
pthread_mutex_t mutex;
bool trigger = false;

//Thread arguments
typedef struct {
    int timer;
} thread_args_t;

void signalHandler(int sig) {
    //Alarm check
    if (sig == 2) {
        fprintf(stdout, "Program will terminate soon\n"); 
        pthread_exit(0);
    }
    //Countdown and Wall Clock Check
    if (sig == 3) {
        trigger = true;
        pthread_exit(0);
    }
}

void * count_down(void * pointer) {
    thread_args_t thread_args = *((thread_args_t *) pointer);
    int timer = thread_args.timer;

    //Count down then raise signal to quit
    int i = timer;
    for(; i > 0; i--) {
        sem_wait(&FLAG);
        pthread_mutex_lock(&mutex);
        //fprintf(stdout, "Count Down: :%d\n", i);
        pthread_mutex_unlock(&mutex);
        sem_post(&FLAG);
        sleep(1);
    }
    raise(SIGQUIT);
    if(trigger) { pthread_exit(0);}
}

void * alarm_time(void * pointer) {
    thread_args_t thread_args = *((thread_args_t *) pointer);
    int timer = thread_args.timer;

    //Check for alarm then raise signal
    int i = timer;
    for(; i > 0; i--) {
        sem_wait(&FLAG);
        pthread_mutex_lock(&mutex);
        //fprintf(stdout, "Alarm: :%d\n", i);
        pthread_mutex_unlock(&mutex);
        sem_post(&FLAG);
        sleep(1);
    }
    raise(SIGINT);
}

void * wall_clock(void *pointer) {
    thread_args_t thread_args = *((thread_args_t *) pointer);
    int delay = thread_args.timer;
    //Hold initial value from 2nd argument
    int temp = thread_args.timer;
    time_t now;
    struct tm *lcltime;
    //Print time and quit after countdown finishes
    for(;;) {
        sem_wait(&FLAG);
        pthread_mutex_lock(&mutex);
        now = time(NULL);
        lcltime = localtime(&now);
        if(trigger) {
            raise(SIGQUIT);
        }
        //Print every minute
        if(delay == 60) {
            fprintf(stdout,"Time is %d:%d:%d\n", lcltime->tm_hour, lcltime->tm_min, lcltime->tm_sec);
        } 
        //Print every minute
        else if(delay == 1 && temp != 60) {
            fprintf(stdout,"Time is %d:%d:%d\n", lcltime->tm_hour, lcltime->tm_min, lcltime->tm_sec);
        } 
        //Start over again
        else if(delay == 0) { 
            fprintf(stdout,"Time is %d:%d:%d\n", lcltime->tm_hour, lcltime->tm_min, lcltime->tm_sec);
            delay = thread_args.timer;
        }
        delay = delay - 1;
        pthread_mutex_unlock(&mutex);
        sem_post(&FLAG);
        sleep(1);
    }     
}

int main(int argc, char const *argv[]) {
    //Initialize value array, flag, and mutex
    int argval[3];
    sem_init(&FLAG, 0, 1);
    pthread_mutex_init(&mutex, nullptr);

    //Take control of signals
    signal(SIGINT,signalHandler);
    signal(SIGQUIT,signalHandler);

    //Initialization of thread struct
    thread_args_t worker1;
    thread_args_t worker2;
    thread_args_t worker3;

    //Use default values
    if (argc == 1) {
        argval[0] = 32;
        argval[1] = 1;
        argval[2] = 17;
    } else if (argc == 4) {
        for(int i = 1; i < argc; i++) {
            argval[i-1] = atoi(argv[i]); 
        }
    } 

    if (argval[1] == 60 || argval[1] == 1) {

        //Assign thread values
        worker1.timer = argval[0];
        worker2.timer = argval[1];
        worker3.timer = argval[2];
        
        //Initialize threads
        pthread_t thread1;
        pthread_t thread2;
        pthread_t thread3;

        //Create threads
        pthread_create (&thread1, NULL, count_down, (void *) &worker1);
        pthread_create (&thread2, NULL, wall_clock, (void *) &worker2);
        pthread_create (&thread3, NULL, alarm_time, (void *) &worker3);

        //Wait for threads to finish
        pthread_join(thread1, 0);
        pthread_join(thread2, 0);
        pthread_join(thread3, 0);

        sem_destroy(&FLAG);
        fprintf(stdout, "All done!\n");

    } else {
        fprintf(stderr, "Incorrect second argument\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}