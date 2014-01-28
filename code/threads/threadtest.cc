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
#include "ctype.h"


char * phrases[] = {  "Fly, you fools!", "Hello? Yes, this is dog.", 
						"How can mirrors be real if our eyes aren't real.", 
						"The answer is 42.",
						"So you're saying there's a chance!" };

typedef struct ShouterInfo {
	int shouterID;
	int shoutTimes;
};

void CheckInput(int nothing)
{
	char userinput[256];
	printf("Input a sequence to check:");
	fgets(userinput, 255, stdin);

	// remove the trailing newline char after getting input
	if (userinput[strlen(userinput) -1] == '\n') {
		userinput[strlen(userinput) - 1] = '\0';
	}

	bool isnumber = false;
	bool isnegative = false;
	bool isdecimal = false;
	size_t i = 0;

	if(userinput[i] == '-'){
		isnegative = true;
		i++;
	}

	if(isdigit(userinput[i])){
		isnumber = true;
		for ( i+= 1; i < strlen(userinput); ++i)
		{
			if(isdigit(userinput[i]))
				;
			else if (userinput[i] == '.' && isdecimal == false /*checks for repeated decimal */)
				isdecimal = true;
			else {
				isnumber = false;
				break; //non-decimal or non-numeral was found
			}
		}	
	}

	// print the result
	if (isnumber == false)
		printf("%s is a character", userinput);
	else if (isnegative == true){
		printf("%s is a negative ", userinput);
		if (isdecimal == true)
			printf("decimal");
		else
			printf("number");
	}
	else if (isdecimal == true)
		printf("%s is a decimal", userinput);
	else printf("%s is a number", userinput);
	printf("\n");

}

void taskOne() 
{
	Thread * t = new Thread("Check Input");
	
	t->Fork(CheckInput, 0);
}

//ZL
int randomWaitTime()
{
	int num;

	num = (Random() % 5) + 1;

	if(num < 2)
		num = 2;

	return num;
}


void shoutThread(int shoutInfo)
{
	int shouterID, shoutTimes, timeWaited, phraseShouted= 0, waitTime = 0;
	ShouterInfo * localInfo = (ShouterInfo *)shoutInfo;
	
	shouterID = localInfo -> shouterID;
	shoutTimes = localInfo ->shoutTimes;

	for(int i = 0; i < shoutTimes; i++)
	{		
		phraseShouted = Random() % 5;
		printf("Shouter %d: %s \n", shouterID + 1, phrases[phraseShouted]);

		waitTime = randomWaitTime();

		for(timeWaited = 0; timeWaited < waitTime; timeWaited++)
		{
			currentThread->Yield();
		}
	}
}
//ZL

//ZL
void taskTwo()
{
	int shouters, shoutTimes;
	Thread * t;
	ShouterInfo * info;
	char buffer[256];

	do {
		
		printf("How many threads of shouters should exist: ");
		/*QJ */
		if (fgets(buffer, sizeof(buffer), stdin) != NULL)
		{
		shouters = atoi(buffer);
		}
		/*QJ */
		if(shouters <= 0)
			printf("\n Invalid input! Try again! (Valid numbers are all reasonable non-zero natural numbers)\n");

	} while (shouters <= 0);

	do {
		
		printf("How many times should each shout: ");
		/*QJ */
		if (fgets(buffer, sizeof(buffer), stdin) != NULL)
		{
		shoutTimes = atoi(buffer);
		}/*QJ*/

		if(shoutTimes <= 0)
			printf("\n Invalid input! Try again! (Valid numbers are all reasonable non-zero natural numbers)\n");

	} while (shoutTimes <= 0);

	for(int i = 0; i < shouters; i++)
	{
		t = new Thread("Shouting thread");
		
		info = new ShouterInfo;
		info -> shouterID = i;
		info -> shoutTimes = shoutTimes;
		
		t->Fork(shoutThread, (int)info);
	}

	return;
}


//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    DEBUG('t', "Entering ThreadTest");

    switch(aFlag)
	{
		case 1:
			taskOne();
			break;

		case 2:
			taskTwo();
			break;

		default:
			printf("\nInvalid option! Good day, sir!\n\n");
			break;
	}
}
//ZL
