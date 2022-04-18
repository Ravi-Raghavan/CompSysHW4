#include <pthread.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int SIZE;

int * FIBONACCI;

void * FibonacciIterative(void * ptr){
    int num = *((int *)(ptr));
    for(int index = 0; index < num; index ++){
        if(index == 0){
            *(FIBONACCI + index) = 0;
        }
        else if(index == 1){
            *(FIBONACCI + index) = 1;
        }
        else{
            *(FIBONACCI + index) = *(FIBONACCI + index - 1) + *(FIBONACCI + index - 2);
        }
    }
    return NULL;
}

void displayFibonacci(){
    for(int i = 0; i< SIZE; i ++){
        printf("The %d th Fibonacci Number is: %d\n", i, *(FIBONACCI + i));
    }
}

int main(){
    printf("Please Enter a Number Indicating the Number of Fibonacci Numbers You Would Like to Generate\n");
    int x = scanf("%d", &SIZE);
    FIBONACCI = (int*)(malloc(SIZE * sizeof(int)));
    pthread_t threadID;
    pthread_attr_t threadAttribute;
    int * ptr = &SIZE;
    pthread_attr_init(&threadAttribute);
    pthread_create(&threadID, &threadAttribute, FibonacciIterative, (void*)(ptr));
    pthread_join(threadID, NULL);
    displayFibonacci();
}