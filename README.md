Experiment 4A Folder contains all of the Code Run for Part 2 in Problem 4A for the Experiments


Folder 2C contains all of the code for Problem 2C

Note: For Problem 2C, each program will display the following prompt for the user: "Please Enter a Number Indicating the Number of Fibonacci Numbers You Would Like to Generate". When the user enters a number x into the terminal, the program will generate the following sequence: fib_0, fib_1, fib_2, .... fib_(x - 1)  where fib_i for all 0 <= i <= x represents the ith fibonacci number. fib_0 = 0 and fib_1 as per the definition of the Fibonacci Numbers. 

Within Folder 2C, 
- Main.c corresponds to the code used to generate a Fibonacci sequence, using two threads(i.e. the parent thread and child thread), where the parent thread must wait for the child thread
- MutexLocksWithCondition.c corresponds to the code I used to generate the Fibonacci sequence, where the parent thread is able to access the Fibonacci numbers as soon as they have been computed by the child thread— rather than waiting for the child thread to terminate using just Mutex Locks
- MutexLocksWithoutCondition.c corresponds to the code I used to generate the Fibonacci sequence, where the parent thread is able to access the Fibonacci numbers as soon as they have been computed by the child thread— rather than waiting for the child thread to terminate using Mutex Locks and Condition Variables

