/*queue.h*/

//
// Word Ladders using Graphs
//
// Michael Mei
// Linux Mint 18(Sarah) using gcc 5.4.0
// U. of Illinois, Chicago
// CS251, Fall 2016
// HW #12
//

//
// Queue:
//
typedef int QueueElementType;
typedef struct Queue
{
  QueueElementType  *Elements;  // array of elements in queue:
  int  Front;        // index of first element in Q
  int  Back;         // index of last element in Q
  int  NumElements;  // # of elements currently in Q
  int  Capacity;     // max # of elements that can fit in Q
} Queue;

Queue *CreateQueue(int N);
void   DeleteQueue(Queue *Q);
int    isEmptyQueue(Queue *Q);
int    Enqueue(Queue *Q, QueueElementType e);
QueueElementType Dequeue(Queue *Q);
int    isElementInQueue(Queue *Q, QueueElementType e);
