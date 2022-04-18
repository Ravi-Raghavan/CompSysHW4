//Alternate Code with Condition Variables
#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int SIZE;

int * FIBONACCI;
int writeDone = 0;
int readDone = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
void* FibonacciIterative(void * ptr){
    int num = *((int*)ptr);
    for(int i = 0; i < num; i ++){
        pthread_mutex_lock(&m);
        while(i > 0 && readDone == 0){
            pthread_cond_wait(&c, &m);
        }
        readDone = 0;
        printf("(Iteration %d) Mutex Locked by FibonacciIterative \n", i);
        writeDone = 0;
        if(i == 0){
            *(FIBONACCI + i) = 0;
            writeDone = 1;
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
            printf("(Iteration %d) Mutex Unlocked by FibonacciIterative \n", i);
        }
        else if(i == 1){
            *(FIBONACCI + i) = 1;
            writeDone = 1;
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
            printf("(Iteration %d) Mutex Unlocked by FibonacciIterative \n", i);
        }
        else{
            *(FIBONACCI + i) = *(FIBONACCI + i - 1) + *(FIBONACCI + i - 2);
            writeDone = 1;
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
            printf("(Iteration %d) Mutex Unlocked by FibonacciIterative \n", i);
        }
    }
    return NULL;
}

void displayFibonacci(){
    for(int i = 0; i< SIZE; i ++){
        pthread_mutex_lock(&m);
        while(writeDone == 0){
            pthread_cond_wait(&c, &m);
        }
        writeDone = 0;
        printf("Mutex Locked by displayFibonacci \n");
        readDone = 0;
        printf("The %d th Fibonacci Number is: %d\n", i, *(FIBONACCI + i));
        readDone = 1;
        pthread_cond_signal(&c);
        pthread_mutex_unlock(&m);
        printf("Mutex Unlocked by displayFibonacci \n");
    }
}

int main(){
    printf("Please Enter a Number Indicating the Number of Fibonacci Numbers You Would Like to Generate\n");
    int x = scanf("%d", &SIZE);
    FIBONACCI = (int*)(malloc(SIZE * sizeof(int)));
    pthread_t threadID;
    pthread_attr_t threadAttribute;
    void * ptr = (void*)(&SIZE);
    pthread_attr_init(&threadAttribute);
    pthread_create(&threadID, &threadAttribute, FibonacciIterative, ptr);
    pthread_detach(&threadID);
    displayFibonacci();
}

