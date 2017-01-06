/*stack.c*/

//
// Word Ladders using Graphs
//
// Michael Mei
// Linux Mint 18(Sarah) using gcc 5.4.0
// U. of Illinois, Chicago
// CS251, Fall 2016
// HW #12
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "stack.h"
#include "mymem.h"


// #####################################################
//
// Stack:
//

//
// CreateStack:
//
// Creates a stack with an initial capacity of N elements.
// The stack will dynamically grow in size if it becomes
// full, doubling its internal capacity each time.
//
Stack *CreateStack(int N)
{
  Stack *S;

  if (N < 1)
  {
    printf("\n**Error in CreateStack invalid parameter N (%d)\n\n", N);
    return NULL;
  }

  //
  // allocate stack header:
  //
  S = (Stack *)mymalloc(sizeof(Stack));
  if (S == NULL)
  {
    printf("\n**Error in CreateStack: malloc failed to allocate\n\n");
    exit(-1);
  }

  //
  // allocate array for queue elements:
  //
  S->Elements = (StackElementType *)mymalloc(N * sizeof(StackElementType));
  if (S->Elements == NULL)
  {
    printf("\n**Error in CreateStack: malloc failed to allocate\n\n");
    exit(-1);
  }

  // 
  // initialize fields:
  //
  S->Top = -1;  // first push will be ++Top
  S->NumElements = 0;
  S->Capacity = N;

  //
  // done:
  //
  return S;
}

//
// DeleteStack:
//
// Frees the memory associated with this stack.
//
void DeleteStack(Stack *S)
{
  myfree(S->Elements);
  myfree(S);
}

//
// isEmptyStack: 
//
// Returns true (non-zero) if stack is empty, false (0) if not.
//
int isEmptyStack(Stack *S)
{
  return S->NumElements == 0;
}

//
// Push:
//
// Pushes the given element onto top of stack, returning
// true (non-zero) if successful, false if not.  
//
int Push(Stack *S, StackElementType e)
{
  if (S->NumElements == S->Capacity)  // full
  {
    //
    // instead of failing, let's reallocate the 
    // underlying array to be twice as big:
    //
    int N = 2 * S->Capacity;

    StackElementType *newE = (StackElementType *)mymalloc(N * sizeof(StackElementType));
    if (newE == NULL)
    {
      printf("\n**Error in Push: malloc failed to allocate\n\n");
      exit(-1);
    }

    // copy elements over:
    int  i;

    for (i = 0; i <= S->Top; ++i)
    {
      newE[i] = S->Elements[i];
    }

    myfree(S->Elements);

    S->Elements = newE;
    S->Capacity = N;
  }

  //
  // there's room, add to *END* since that's faster than
  // shifting everyone to the right:
  //
  S->Top++;

  S->Elements[S->Top] = e; 
  S->NumElements++;

  return 1;  /*true*/
}

//
// Pop:
//
// Pops the top element off the stack and returns it; prints
// an error message and exits the program if the stack is 
// empty.
//
StackElementType Pop(Stack *S)
{
  if (isEmptyStack(S))  // nothing to pop!
  {
    printf("\n**Error in Pop: S is empty?!\n\n");
    exit(-1);
  }

  //
  // element to pop:
  //
  StackElementType e = S->Elements[S->Top];

  S->Top--;
  S->NumElements--;

  return e;
}
