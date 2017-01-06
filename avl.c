/*avl.c*/

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
#include <assert.h>

#include "avl.h"
#include "mymem.h"


//
// CreateAVLTree:
//
// Returns an empty tree (NULL).
//
AVLNode *CreateAVLTree()
{
  return NULL;
}

//
// Contains:
//
// Searches for the given value, if found, returns
// pointer to node in tree, otherwise NULL is returned.
//
AVLNode *Contains(AVLNode *root, AVLElementType value)
{
  AVLNode *cur = root;

  while (cur != NULL)
  {
    if (strcmp(value.Word, cur->value.Word) == 0)  // match!
      return cur;
    else if (strcmp(value.Word, cur->value.Word) < 0)  // smaller, go left:
      cur = cur->left;
    else  // larger, go right:
      cur = cur->right;
  }

  // if get here, not found:
  return NULL;
}


//
// Rotate right the sub-tree rooted at node N, return pointer
// to root of newly-rotated sub-tree --- i.e. return pointer
// to node L that was rotated up to top of sub-tree.  Heights
// are adjusted as well after rotation.
//
int _height(AVLNode *N)
{
  if (N == NULL)
    return -1;
  else
    return N->height;
}

int _max(int a, int b)
{
  if (a > b)
    return a;
  else
    return b;
}

AVLNode *RightRotate(AVLNode *N)
{
  assert(N->left != NULL);  // must have left child to rotate up:

  AVLNode *L = N->left;

  AVLNode *A = L->left;
  AVLNode *B = L->right;
  AVLNode *C = N->right;

  //
  // rotate L up, and N down to the right:
  //
  L->right = N;
  N->left = B;

  //
  // recompute heights of nodes that moved:  N, then L
  //
  N->height = 1 + _max(_height(N->left), _height(N->right));
  L->height = 1 + _max(_height(L->left), _height(L->right));

  return L;  // L is the new root of rotated sub-tree:
}

//
// Rotate left the sub-tree rooted at node N, return pointer
// to root of newly-rotated sub-tree --- i.e. return pointer
// to node R that was rotated up to top of sub-tree.  Heights
// are adjusted as well after rotation.
//
AVLNode *LeftRotate(AVLNode *N)
{
  assert(N->right != NULL);  // must have right child to rotate up:

  AVLNode *R = N->right;

  AVLNode *A = N->left;
  AVLNode *B = R->left;
  AVLNode *C = R->right;

  //
  // rotate R up, and N down to the left:
  //
  R->left = N;
  N->right = B;

  //
  // recompute heights of nodes that moved:  N, then R
  //
  N->height = 1 + _max(_height(N->left), _height(N->right));
  R->height = 1 + _max(_height(R->left), _height(R->right));

  return R;  // R is the new root of rotated sub-tree:
}


//
// AVL Insert:
//
// Inserts the given value into the AVL tree, rebalancing
// the tree as necessary.  Returns a pointer to the root of
// the new tree; if the value to insert is already in the
// tree, nothing happens and a pointer to the root of the
// original tree is returned.
// 
//
#define TRUE  1
#define FALSE 0

AVLNode *Insert(AVLNode *root, AVLElementType value)
{
  AVLNode *prev = NULL;
  AVLNode *cur = root;

  AVLNode *stack[64];
  int      top = -1;

  while (cur != NULL)
  {
    top++;
    stack[top] = cur;

    if (strcmp(value.Word, cur->value.Word) == 0)  // already present:
      return root;
    else if (strcmp(value.Word, cur->value.Word) < 0)  // smaller, go left:
    {
      prev = cur;
      cur = cur->left;
    }
    else  // larger, go right:
    {
      prev = cur;
      cur = cur->right;
    }
  }

  //
  // when get here, insert:
  //
  AVLNode *newNode;

  newNode = (AVLNode *)mymalloc(sizeof(AVLNode));
  newNode->value = value;
  newNode->height = 0;
  newNode->left = NULL;
  newNode->right = NULL;

  if (prev == NULL)  // insert at root:
    root = newNode;
  else if (strcmp(value.Word, prev->value.Word) < 0)  // insert to left of prev:
    prev->left = newNode;
  else  // insert to the right:
    prev->right = newNode;

  //
  // Now walk back up the tree, updating heights and looking for
  // where the AVL balancing criteria may be broken.  If we reach
  // a node where the height doesn't change, then we're done -- the
  // tree is still balanced.  If we reach a node where the AVL 
  // condition is broken, we fix locally and we're done.  1 or 2 local
  // rotations is enough to re-balance the tree.
  //
  int rebalance = FALSE;

  while (top >= 0)  // walk back up the stack:
  {
    cur = stack[top];
    top--;

    // what's the new height of cur?
    int hl = _height(cur->left);
    int hr = _height(cur->right);
    int newH = 1 + _max(hl, hr);

    if (cur->height == newH)  // hasn't changed, nothing to do!
    {
      rebalance = FALSE;  // no rebalance, exit loop:
      break;
    }
    else if (abs(hl - hr) > 1)  // height changed --- is AVL condition broken?
    {
      rebalance = TRUE;  // yes, so rebalance tree and exit loop to fix:
      break;
    }
    else  // update height in current node and continue walking up tree:
    {
      cur->height = newH;
    }
  }//while

   //
   // Okay, does the tree need to be rebalanced?
   //
  if (rebalance)
  {
    //
    // if we get here, then the AVL condition is broken at "cur".  So we
    // have to decide which of the 4 cases it is and then rotate to fix.
    //

    // we need cur's parent, so pop the stack one more time
    if (top < 0)     // stack is empty, ==> cur is root
      prev = NULL;   // flag this with prev == NULL
    else  // stack not empty, so obtain ptr to cur's parent:
      prev = stack[top];

    // which of the 4 cases?
    if (strcmp(newNode->value.Word, cur->value.Word) < 0)  // case 1 or 2:
    {

      // case 1 or case 2?  either way, we know cur->left exists:
      AVLNode *L;
      L = cur->left;
      assert(L != NULL);

      // case 2 performs 2 rotations, so check that first:
      if (strcmp(newNode->value.Word, L->value.Word) > 0)  // to the right => case 2:
      {
        // case 2: left rotate @L 
        cur->left = LeftRotate(L);
      }

      // case 1 and 2: now we right rotate @cur:
      if (prev == NULL)
        root = RightRotate(cur);
      else if (prev->left == cur)
        prev->left = RightRotate(cur);
      else
        prev->right = RightRotate(cur);

    }
    else  // case 3 or 4:
    {
      assert(strcmp(newNode->value.Word, cur->value.Word) > 0);

      // case 3 or case 4?  either way, we know cur->right exists:
      AVLNode *R;
      R = cur->right;
      assert(R != NULL);

      // case 3 performs 2 rotations, so check that first:
      if (strcmp(newNode->value.Word, R->value.Word) < 0)  // to the left => case 3:
      {
        // case 3: right rotate @R 
        cur->right = RightRotate(R);
      }

      // case 3 and 4: now we left rotate @cur
      if (prev == NULL)
        root = LeftRotate(cur);
      else if (prev->left == cur)
        prev->left = LeftRotate(cur);
      else
        prev->right = LeftRotate(cur);

    }
  }

  //
  // done, return ptr to new tree:
  //
  return root;
}


//
// Count
//
// Returns the # of nodes in the tree.  This is a recursive call that traverses
// the entire tree.
//
int Count(AVLNode *root)
{
  if (root == NULL)  // base case: empty
    return 0;
  else
    return 1 + Count(root->left) + Count(root->right);
}


//
// Height
//
// Returns the overall height of the tree.  Since this is an AVL tree,
// the heights are stored internally so we just look at root node.
//
int Height(AVLNode *root)
{
  if (root == NULL)
    return -1;
  else
    return root->height;
}


//
// PrintInorder
//
// Prints the tree inorder to the console; a debugging function.
//
void PrintInorder(AVLNode *root)
{
  if (root == NULL)  // base case: empty tree
    return;
  else  // recursive case: non-empty tree
  {
    PrintInorder(root->left);
    printf("%s: %d\n", root->value.Word, root->value.Vertex);
    PrintInorder(root->right);
  }
}


//
// FreeAVLTree
//
// Frees the memory associated with this AVL tree.
//
void FreeAVLTree(AVLNode *root)
{
  if (root == NULL)
    ;
  else
  {
    FreeAVLTree(root->left);
    FreeAVLTree(root->right);
    myfree(root);
  }
}
