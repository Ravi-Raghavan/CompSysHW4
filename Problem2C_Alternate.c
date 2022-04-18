#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int SIZE;

int * FIBONACCI;
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
void* FibonacciIterative(void * ptr){
    int num = *((int*)ptr);
    for(int i = 0; i < num; i ++){
        pthread_mutex_lock(&m);
        
        while(done == 1){
            pthread_cond_wait(&c, &m);
        }
        
        printf("Mutex Locked by FibonacciIterative \n");
        done = 0;
        if(i == 0){
            *(FIBONACCI + i) = 0;
            done = 1;
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
            printf("Mutex Unlocked by FibonacciIterative \n");
        }
        else if(i == 1){
            *(FIBONACCI + i) = 1;
            done = 1;
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
            printf("Mutex Unlocked by FibonacciIterative \n");
        }
        else{
            *(FIBONACCI + i) = *(FIBONACCI + i - 1) + *(FIBONACCI + i - 2);
            done = 1;
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
            printf("Mutex Unlocked by FibonacciIterative \n");
        }
    }
    return NULL;
}

void displayFibonacci(){
    for(int i = 0; i< SIZE; i ++){
        pthread_mutex_lock(&m);
        while(done == 0){
            pthread_cond_wait(&c, &m);
        }
        printf("Mutex Locked by displayFibonacci \n");
        done = 1;
        pthread_cond_signal(&c);
        printf("The %d th Fibonacci Number is: %d\n", i, *(FIBONACCI + i));
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

/**
 * @brief 
 * Basically, I had a global integer variable called done. Every time the child thread began a recursive execution of FibonacciRecursive(), 
 * I created a lock for the child thread. When the child was done generating a fibonaci number and writing that number to array storage, 
 * the child thread would signal to the parent thread that it was done using the condition variable. Furthermore, the child thread would release its lock 
 * 
 * 
 */
