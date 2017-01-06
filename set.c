/*set.c*/

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

#include "set.h"
#include "mymem.h"


// #####################################################
//
// Set:
//

//
// CreateSet:
//
// Creates a set with an initial capacity of N elements.
// The set will dynamically grow in size if it becomes
// full, doubling its internal capacity each time.
//
Set *CreateSet(int N)
{
  Set *S;

  if (N < 1)
  {
    printf("\n**Error in CreateSet invalid parameter N (%d)\n\n", N);
    return NULL;
  }

  //
  // allocate set header:
  //
  S = (Set *)mymalloc(sizeof(Set));
  if (S == NULL)
  {
    printf("\n**Error in CreateSet: malloc failed to allocate\n\n");
    exit(-1);
  }

  //
  // allocate array for set elements:
  //
  S->Elements = (SetElementType *)mymalloc(N * sizeof(SetElementType));
  if (S->Elements == NULL)
  {
    printf("\n**Error in CreateSet: malloc failed to allocate\n\n");
    exit(-1);
  }

  // 
  // initialize fields:
  //
  S->NumElements = 0;
  S->Capacity = N;

  //
  // done:
  //
  return S;
}

//
// DeleteSet:
//
// Frees the memory associated with this set.
//
void DeleteSet(Set *S)
{
  myfree(S->Elements);
  myfree(S);
}

//
// isEmptySet: 
//
// Returns true (non-zero) if set is empty, false (0) if not.
//
int isEmptySet(Set *S)
{
  return S->NumElements == 0;
}

//
// AddToSet:
//
// Inserts the given element into the set in sorted order,
// returning true (non-zero) if successful, false if not.  
//
int AddToSet(Set *S, SetElementType e)
{
  //
  // sets don't have duplicates, so first check to see
  // if e is already in the set, and if so, return now:
  //
  if (isElementInSet(S, e))  // already in set:
    return 1;  /*true*/

  //
  // we need to add --- is set full?
  //
  if (S->NumElements == S->Capacity)  // full
  {
    //
    // instead of failing, let's reallocate the 
    // underlying array to be twice as big:
    //
    int N = 2 * S->Capacity;

    SetElementType *newE = (SetElementType *)mymalloc(N * sizeof(SetElementType));
    if (newE == NULL)
    {
      printf("\n**Error in AddToSet: malloc failed to allocate\n\n");
      exit(-1);
    }

    // copy elements over:
    int  i;

    for (i = 0; i < S->NumElements; ++i)
    {
      newE[i] = S->Elements[i];
    }

    myfree(S->Elements);

    S->Elements = newE;
    S->Capacity = N;
  }

  //
  // there's room, insert in order:
  //
  int  i;

  for (i = 0; i < S->NumElements; ++i)
  {
    if (e == S->Elements[i])  // already in set:
      return 1;  /*true*/
    if (e < S->Elements[i])   // insert before this element:
      break;

    // else keep going to find insertion spot:
  }

  //
  // if we get here, insert e before ith element:
  //
  int  j;

  for (j = S->NumElements; j > i; --j)
    S->Elements[j] = S->Elements[j - 1];

  S->Elements[i] = e;  // store:
  S->NumElements++;

  return 1;  /*true*/
}

//
// isElementInSet:
//
// Return true (non-zero) if e is a member of S, false
// (0) if not.  Note that if e is a member of S, then
// the value returned is the "position" of e in the set,
// starting at 1.  Example:  suppose S = {10, 13, 45},
// then isElementInSet(S, 13) would return 2.
//
int isElementInSet(Set *S, SetElementType e)
{
  //
  // since elements are ordered, use binary search:
  //
  int low = 0;
  int high = S->NumElements - 1;

  while (low <= high)
  {
    int mid = low + ((high - low) / 2);

    if (e == S->Elements[mid])
      return mid + 1;  // return position in set, 1-based:
    else if (e < S->Elements[mid])
      high = mid - 1;
    else
      low = mid + 1;
  }

  // if get here, not found:
  return 0;  /*false*/
}
