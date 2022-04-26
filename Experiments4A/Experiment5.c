#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>
 
// Experiment 5
 
void threadOneHandler(int signum){
   //sleep(1);
   printf("The First Thread, with thread ID %d that has generated has caught signal %d\n", (int)(pthread_self()), signum);
   printf("The First Thread, with thread ID %d that finished executing the signal handler for signal %d\n", (int)(pthread_self()), signum);
   //sleep(1);
}
 
 
void threadTwoHandler(int signum){
   //sleep(1);
   printf("The Second Thread, with thread ID %d that has generated has caught signal %d\n", (int)(pthread_self()), signum);
   printf("The Second Thread, with thread ID %d that finished executing the signal handler for signal %d\n", (int)(pthread_self()), signum);
   //sleep(1);
}
 
 
void threadThreeHandler(int signum){
   //sleep(1);
   printf("The Third Thread, with thread ID %d that has generated has caught signal %d\n", (int)(pthread_self()), signum);
   printf("The Third Thread, with thread ID %d that finished executing the signal handler for signal %d\n", (int)(pthread_self()), signum);
   //sleep(1);
}
 
void threadSixHandler(int signum){
   //sleep(1);
   printf("The Sixth Thread, with thread ID %d that has generated has caught signal %d\n", (int)(pthread_self()), signum);
   printf("The Sixth Thread, with thread ID %d that finished executing the signal handler for signal %d\n", (int)(pthread_self()), signum);
   //sleep(1);
}
 
 
 
void * threadOne(void * ptr){
   printf("Setting the SIGINT handler for Thread One, with thread ID %d, to be threadOneHandler \n", (int)(pthread_self()));
   signal(SIGINT, threadOneHandler);
   return NULL;
}
 
void * threadTwo(void * ptr){
   printf("Setting the SIGINT handler for Thread Two, with thread ID %d, to be threadTwoHandler \n", (int)(pthread_self()));
   signal(SIGINT, threadTwoHandler);
   return NULL;
}
 
void * threadThree(void * ptr){
   printf("Setting the SIGINT handler for Thread Three, with thread ID %d, to be threadThreeHandler \n", (int)(pthread_self()));
   signal(SIGINT, threadThreeHandler);
   return NULL;
}
 
void * threadFour(void * ptr){
   printf("Setting the SIGINT handler for Thread Four, with thread ID %d, to be SIG_DFL \n", (int)(pthread_self()));
   signal(SIGINT, SIG_DFL);
   return NULL;
}
 
void * threadFive(void * ptr){
   printf("Setting the SIGINT handler for Thread Five, with thread ID %d, to be SIG_IGN \n", (int)(pthread_self()));
   signal(SIGINT, SIG_IGN);
   return NULL;
}
 
 
void * threadSix(void * ptr){
   printf("Setting the SIGINT handler for Thread Six, with thread ID %d, to be threadSixHandler \n", (int)(pthread_self()));
   signal(SIGINT, threadSixHandler);
   return NULL;
}
 
 
int main(){
 
   pthread_t threadID[6];
   pthread_attr_t threadAttributes[6];
 
   void * ptr = NULL;
   printf("The thread ID for the main thread is %d\n",  (int)(pthread_self()));
   for(int i = 0; i < 6; i ++){
       pthread_attr_init(&threadAttributes[i]);
       if(i == 0){
           pthread_create(&threadID[i],&threadAttributes[i], threadOne, ptr);
       }
       else if(i == 1){
           pthread_create(&threadID[i],&threadAttributes[i], threadTwo, ptr);
       }
       else if(i == 2){
           pthread_create(&threadID[i],&threadAttributes[i], threadThree, ptr);
       }
       else if(i == 3){
           pthread_create(&threadID[i],&threadAttributes[i], threadFour, ptr);
       }
       else if(i == 4){
           pthread_create(&threadID[i],&threadAttributes[i], threadFive, ptr);
       }
       else if(i == 5){
           pthread_create(&threadID[i], &threadAttributes[i], threadSix, ptr);
       }
   }
 
   sleep(2);  //give the program enough time for all threads to execute their respective functions
   printf("Sending SIGINT to Thread One, whose thread ID is %d\n", (int)(threadID[0]));
   int firstReturnValue = pthread_kill(threadID[0], SIGINT); 
    
   if(firstReturnValue == 0){
       printf("First Thread was successfully terminated by SIGINT signal\n");
   }
   else{
       printf("Value of firstReturnValue: %d\n", firstReturnValue);
   }
 
 
   printf("Sending SIGINT to Thread Two, whose thread ID is %d\n", (int)(threadID[1]));
   int secondReturnValue = pthread_kill(threadID[1], SIGINT);
 
   if(secondReturnValue == 0){
       printf("First Thread was successfully terminated by SIGINT signal\n");
   }
   else{
       printf("Value of secondReturnValue: %d\n", secondReturnValue);
   }
 
   printf("Sending SIGINT to Thread Three, whose thread ID is %d\n", (int)(threadID[2]));
   int thirdReturnValue = pthread_kill(threadID[2], SIGINT);
 
   if(thirdReturnValue == 0){
       printf("First Thread was successfully terminated by SIGINT signal\n");
   }
   else{
       printf("Value of thirdReturnValue: %d\n", thirdReturnValue);
   }
 
   printf("Sending SIGINT to Thread Four, whose thread ID is %d\n", (int)(threadID[3]));
   int fourthReturnValue = pthread_kill(threadID[3], SIGINT);
 
   if(fourthReturnValue == 0){
       printf("First Thread was successfully terminated by SIGINT signal\n");
   }
   else{
       printf("Value of fourthReturnValue: %d\n", fourthReturnValue);
   }
  
 
   printf("Sending SIGINT to Thread Five, whose thread ID is %d\n", (int)(threadID[4]));
   int fifthReturnValue = pthread_kill(threadID[4], SIGINT);
 
   if(fifthReturnValue == 0){
       printf("First Thread was successfully terminated by SIGINT signal\n");
   }
   else{
       printf("Value of fifthReturnValue: %d\n", fifthReturnValue);
   }
 
   printf("Sending SIGINT to Thread Six, whose thread ID is %d\n", (int)(threadID[5]));
   int sixthReturnValue = pthread_kill(threadID[5], SIGINT);
 
   if(sixthReturnValue == 0){
       printf("First Thread was successfully terminated by SIGINT signal\n");
   }
   else{
       printf("Value of sixthReturnValue: %d\n", sixthReturnValue);
   }
 
 
}
 
