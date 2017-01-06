/*queue.c*/

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

#include "queue.h"
#include "mymem.h"


// #####################################################
//
// Queue:
//

//
// CreateQueue:
//
// Creates a queue with an initial capacity of N elements.
// The queue will dynamically grow in size if it becomes
// full, doubling its internal capacity each time.
//
Queue *CreateQueue(int N)
{
  Queue *Q;

  if (N < 1)
  {
    printf("\n**Error in CreateQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }

  //
  // allocate queue header:
  //
  Q = (Queue *)mymalloc(sizeof(Queue));
  if (Q == NULL)
  {
    printf("\n**Error in CreateQueue: malloc failed to allocate\n\n");
    exit(-1);
  }

  //
  // allocate array for queue elements:
  //
  Q->Elements = (QueueElementType *)mymalloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in CreateQueue: malloc failed to allocate\n\n");
    exit(-1);
  }

  // 
  // initialize fields:
  //
  Q->Front = 0;  // first dequeue from position 0
  Q->Back = -1;  // first enqueue will be ++Back
  Q->NumElements = 0;
  Q->Capacity = N;

  //
  // done:
  //
  return Q;
}

//
// DeleteQueue:
//
// Frees the memory associated with this queue.
//
void DeleteQueue(Queue *Q)
{
  myfree(Q->Elements);
  myfree(Q);
}

//
// isEmptyQueue: 
//
// Returns true (non-zero) if queue is empty, false (0) if not.
//
int isEmptyQueue(Queue *Q)
{
  return Q->NumElements == 0;
}

//
// Enqueue:
//
// Inserts the given element at the end of the queue, returning
// true (non-zero) if successful, false if not.  
//
int Enqueue(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)  // full
  {
    //
    // instead of failing, let's reallocate the 
    // underlying array to be twice as big:
    //
    int N = 2 * Q->Capacity;

    QueueElementType *newE = (QueueElementType *)mymalloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in Enqueue: malloc failed to allocate\n\n");
      exit(-1);
    }

    // copy elements over --- for simplicity, the elements
    // will be copied over to the front of the new array:
    int  i = Q->Front;
    int  j = 0;
    int  n;

    for (n = 0; n < Q->NumElements; ++n)
    {
      newE[j] = Q->Elements[i];
      ++j;

      ++i;
      if (i >= Q->Capacity)
        i = 0;
    }

    myfree(Q->Elements);

    Q->Front = 0;
    Q->Back = j - 1;
    Q->Elements = newE;
    Q->Capacity = N;
  }

  //
  // there's room, add to end:
  //
  Q->Back++;

  if (Q->Back >= Q->Capacity)  // did we wrap around?
    Q->Back = 0;

  Q->Elements[Q->Back] = e;  // enqueue:
  Q->NumElements++;

  return 1;  /*true*/
}

//
// Dequeue:
//
// Removes the front-most element of the queue and returns it;
// prints an error message and exits the program if the queue
// is empty.
//
QueueElementType Dequeue(Queue *Q)
{
  if (isEmptyQueue(Q))  // nothing to dequeue?!
  {
    printf("\n**Error in Dequeue: Q is empty?!\n\n");
    exit(-1);
  }

  //
  // element to dequeue:
  //
  QueueElementType e = Q->Elements[Q->Front];

  Q->Front++;
  if (Q->Front >= Q->Capacity)  // wrap around:
    Q->Front = 0;

  Q->NumElements--;

  return e;
}

//
// isElementInQueue:
//
// Return true (non-zero) if e is a member of Q, false
// (0) if not.
//
int isElementInQueue(Queue *Q, QueueElementType e)
{
  int  i = Q->Front;
  int  count;

  //
  // linear search starting at front:
  //
  for (count = 0; count < Q->NumElements; ++count)
  {
    if (Q->Elements[i] == e)  // match!
      return 1;  /*true*/

    ++i;
    if (i == Q->Capacity)  // wrap around:
      i = 0;
  }

  // if get here, not found:
  return 0;  /*false*/
}
