/*set.h*/

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
// Set:
//
typedef int SetElementType;
typedef struct Set
{
  SetElementType  *Elements;  // array of elements in Set:
  int  NumElements;  // # of elements currently in Set
  int  Capacity;     // max # of elements that can fit in Set
} Set;

Set *CreateSet(int N);
void DeleteSet(Set *S);
int  isEmptySet(Set *S);
int  AddToSet(Set *S, SetElementType e);
int  isElementInSet(Set *S, SetElementType e);
