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
#include "elevatortest.h"

// testnum is set in main.cc
int testnum = 1;
//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------
extern ThreadTable threadTable;
void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 2; num++) {
		printf("*** thread %d looped %d times\n", which, num);
		threadTable.ThreadDump();
        currentThread->Yield();
    }
	threadTable.ThreadDump();
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------
void add(int a){
	printf("1+1=2\n");
	return;
}

void
subtract(int a){
	printf("1-1=0\n");
	return ;
}
void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");
    t->Fork(SimpleThread, (void*)t->getPid());

	Thread *t2=new Thread("t2 thread");
	t2->Fork(add,(void*)t2->getPid());
	
	Thread *t3 = new Thread("t3 thread");
	t3->Fork(subtract,(void*)t3->getPid());
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}


