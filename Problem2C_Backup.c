#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int SIZE;

int * FIBONACCI;
int count = 0;
pthread_mutex_t mutexVariable = PTHREAD_MUTEX_INITIALIZER;
void* FibonacciIterative(void * ptr){
    int num = *((int*) ptr);
    for(; count < 2 * num;){
        if(count % 2 == 0){
            int index = count / 2;
            pthread_mutex_lock(&mutexVariable);
            printf("Mutex Locked by FibonacciIterative \n");
            if(index == 0){
                *(FIBONACCI + index) = 0;
                count ++;
                pthread_mutex_unlock(&mutexVariable);
                printf("Mutex Unlocked by FibonacciIterative \n");
            }
            else if(index == 1){
                *(FIBONACCI + index) = 1;
                count ++;
                pthread_mutex_unlock(&mutexVariable);
                printf("Mutex Unlocked by FibonacciIterative \n");
            }
            else{
                *(FIBONACCI + index) = *(FIBONACCI + index - 1) + *(FIBONACCI + index - 2);
                count ++;
                pthread_mutex_unlock(&mutexVariable);
                printf("Mutex Unlocked by FibonacciIterative \n");
            }
        }
    }
    return NULL;
}

void displayFibonacci(){
    for(; count < 2 * SIZE;){
        if(count % 2 != 0){
            int index = count / 2;
            pthread_mutex_lock(&mutexVariable);
            printf("Mutex Locked by displayFibonacci \n");
            printf("The %d th Fibonacci Number is: %d\n", index, *(FIBONACCI + index));
            count ++;
            pthread_mutex_unlock(&mutexVariable);
            printf("Mutex Unlocked by displayFibonacci \n");
        }
    }
}

int main(){
    printf("Please Enter a Number Indicating the Number of Fibonacci Numbers You Would Like to Generate\n");
    int x = scanf("%d", &SIZE);
    FIBONACCI = (int*)(malloc(SIZE * sizeof(int)));

    pthread_t threadID;
    pthread_attr_t threadAttribute;
    void * ptr = (void *)(&SIZE);
    pthread_attr_init(&threadAttribute);
    pthread_create(&threadID, &threadAttribute, FibonacciIterative, ptr);
    pthread_detach(&threadID);
    displayFibonacci();
}
