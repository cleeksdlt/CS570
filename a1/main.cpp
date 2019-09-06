#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "player.h"

/*
 *Authors: Christian De La Torre and Ernesto Parra
 *Class Acount: cssc0786 and cssc0787
 *Class: CS570, Summer 2019
 *Assignment: Assignment #1, Thread Management
 *main.cpp
 */

//Initialization of semaphore, mutex, and file
sem_t FLAG;
pthread_mutex_t mutex;
FILE* file;

//Thread arguments
typedef struct {
    const char* name;
    int delay;
} thread_args_t;

//Main thread method
void * thread_runner(void *pointer) {

    const char* const cardValue[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    thread_args_t thread_args = *((thread_args_t *) pointer);
    const char* thread_name = thread_args.name;
    int delay = thread_args.delay;
    int thread_id = pthread_self();

    //Loop through player cards and write to file
    int j = 0;
    for(j = 0; j <= 12; j++) {
        sem_wait(&FLAG);
        pthread_mutex_lock(&mutex);
        file = fopen("STACK.txt", "a");
        fprintf(stdout, "Thread %d is running...\n", thread_id);
        fprintf(file, "%s %s\n", thread_name, cardValue[j]);
        fclose(file);
        pthread_mutex_unlock(&mutex);
        sem_post(&FLAG);
        usleep(delay);
    }
    pthread_exit(0);
}

int main(int argc, char const *argv[]) {
    
    //Get process ID
    int pid = getpid();
    
    sem_init(&FLAG, 0, 1);
    pthread_mutex_init(&mutex, nullptr);
    
    file = fopen("STACK.txt", "w");
    fprintf(file, "Process ID: %d\n", pid);
    fclose(file);

    //Call thread_args_t struct
    thread_args_t diamond;
    thread_args_t club;
    thread_args_t heart;
    thread_args_t spade;

    //Initialize/assign thread name and delay
    diamond.name = "DIAMOND";
    club.name = "CLUB";
    heart.name = "HEART";
    spade.name = "SPADE";

    diamond.delay = 125;
    club.delay = 250;
    heart.delay = 500;
    spade.delay = 750;

    //Create threads and call threads
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;

    pthread_create (&thread1, NULL, thread_runner, (void *) &diamond);
    pthread_create (&thread2, NULL, thread_runner, (void *) &club);
    pthread_create (&thread3, NULL, thread_runner, (void *) &heart);
    pthread_create (&thread4, NULL, thread_runner, (void *) &spade);

    pthread_join(thread1, 0);
    pthread_join(thread2, 0);
    pthread_join(thread3, 0);
    pthread_join(thread4, 0);

    //Destroy semaphore and print to console
    sem_destroy(&FLAG);
    fprintf(stdout, "All done!\n");
    return 0;    

}
