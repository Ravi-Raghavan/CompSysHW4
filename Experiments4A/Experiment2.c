#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>
 
//experiment 2
void * firstThread(void * ptr){
   printf("Hi my name is thread %d\n", (int)(pthread_self()));
   sleep(30);  //long sleep to give time for main thread to send SIGINT signals
   printf("Hi this thread %d is exiting\n", (int)(pthread_self()));
   return NULL;
}
void * otherThreads(void * ptr){
   printf("Hi my name is thread %d\n", (int)(pthread_self()));
   sleep(10);
   printf("Hi this thread %d is exiting\n", (int)(pthread_self()));
   return NULL;
}
 
int main(){
 
   pthread_t threadID[3];
   pthread_attr_t threadAttributes[3];
 
   void * ptr = NULL;
 
   for(int i = 0; i < 3; i ++){
       pthread_attr_init(&threadAttributes[i]);
       if(i == 0){
           pthread_create(&threadID[i],&threadAttributes[i], firstThread, ptr);
       }
       else{
           pthread_create(&threadID[i],&threadAttributes[i], otherThreads, ptr);
       }
   }
 
   sleep(5); //Give some time for the threads to be created and start running thread_func
 
   int firstReturnValue = kill(getpid(), SIGINT);  //Send a SIGINT signal to the process
 
   printf("Extra Stuff Here\n");
   for(int i = 0; i < 3; i ++){
       pthread_join(threadID[i], NULL);
   }
}
