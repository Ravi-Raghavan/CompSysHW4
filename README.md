Experiment 4A Folder contains all of the Code Run for Part 2 in Problem 4A for the Experiments


Folder 2C contains all of the code for Problem 2C

Within Folder 2C, 
- Main.c corresponds to the code used to generate a Fibonacci sequence, using two threads(i.e. the parent thread and child thread), where the parent thread must wait for the child thread
- MutexLocksWithCondition.c corresponds to the code I used to generate the Fibonacci sequence, where the parent thread is able to access the Fibonacci numbers as soon as they have been computed by the child thread— rather than waiting for the child thread to terminate using just Mutex Locks
- MutexLocksWithoutCondition.c corresponds to the code I used to generate the Fibonacci sequence, where the parent thread is able to access the Fibonacci numbers as soon as they have been computed by the child thread— rather than waiting for the child thread to terminate using Mutex Locks and Condition Variables

