// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int T, int S)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
        currentThread->Yield();
    }
}


//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest(int number)
{
    DEBUG('t', "Entering ThreadTest");
    if(number == 1){
	Task1();
    }

    else if(number == 2){
	int T, S;
	printf("How many threads?\n");
	printf("How many shouts? (Up to 5)\n");
    	Thread *t = new Thread("forked thread");
    	t->Fork(SimpleThread, 1);
    	SimpleThread(0);
    }


}

void Task1()
{
	int c_type = 2;
	int i = 0;
	int n = 0;
        char c_in[26];

        printf("Waiting on user input:\n");
        scanf("%s",c_in);
	printf("%s \n",c_in);

	if(c_in[0] == '-'){
		n = 1;
		i = 1;		
	}  

	while(i < 26){
		if(c_in[i] == '\0'){
			printf("End of string.\n");
			break;
		}
		
		if(!isdigit(c_in[i]) || c_in[i] != '.'){
			c_type = 0;
			break;
		}
		if(c_in[i] = '.'){
			if(c_type == 1){
				c_type = 0;
				break
			}
			c_type = 1;
		}
		i++;	
	}
	
	if(c_type = 0){
		printf("Input is character string.\n");
	}
	else if(c_type = 1){
		printf("Input is a ");
		if(n == 1){
			printf("negative ");		
			}
		printf("decimal.\n");
	}
	else if(c_type = 2){
		printf("Input is a ");
		if(n == 1){
			printf("negative ");
			}
		printf("integer.\n");
	}
 	
}
