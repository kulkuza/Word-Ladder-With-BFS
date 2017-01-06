/*main.c*/

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

#include "graph.h"
#include "mymem.h"


void SimpleGraphTest()
{
  Graph  *G;

  G = CreateGraph(1);

  int A = AddVertex(G, "A");
  int B = AddVertex(G, "B");
  int C = AddVertex(G, "C");
  int D = AddVertex(G, "D");

  if (A < 0 || B < 0 || C < 0 || D < 0)
  {
    printf("**Error: AddVertex failed?!\n\n");
    exit(-1);
  }

  if (!AddEdge(G, A, B, 2))
    { printf("**Error: AddEdge failed?!\n\n"); exit(-1); }
  if (!AddEdge(G, A, D, 2))
    { printf("**Error: AddEdge failed?!\n\n"); exit(-1); }
  if (!AddEdge(G, B, C, 2))
    { printf("**Error: AddEdge failed?!\n\n"); exit(-1); }
  if (!AddEdge(G, C, D, 2))
    { printf("**Error: AddEdge failed?!\n\n"); exit(-1); }
  if (!AddEdge(G, C, C, 99))
    { printf("**Error: AddEdge failed?!\n\n"); exit(-1); }
  if (!AddEdge(G, A, B, 1))
    { printf("**Error: AddEdge failed?!\n\n"); exit(-1); }
  if (!AddEdge(G, A, D, 1))
    { printf("**Error: AddEdge failed?!\n\n"); exit(-1); }
  if (!AddEdge(G, B, C, 1))
    { printf("**Error: AddEdge failed?!\n\n"); exit(-1); }
  if (!AddEdge(G, C, D, 1))
    { printf("**Error: AddEdge failed?!\n\n"); exit(-1); }

  PrintGraph(G, "Simple Test", 1 /*true*/);

  DeleteGraph(G);
}

void BuildGraph(Graph *G, char *filename)
{

  printf(">>Building Graph from '%s'...\n", filename);

  FILE *infile;
  char line[256];
  int linesize = sizeof(line) / sizeof(line[0]);

  infile = fopen(filename, "r");
  if (infile == NULL)
  {
    printf("**Error: unable to open '%s'\n\n", filename);
    exit(-1);
  }

  fgets(line, linesize, infile);
  //word[strcspn(word, "\r\n")] = '\0';  // strip EOL char(s):
  while (!feof(infile))
  {
    char *token;
    token = strtok(line, "\n");

    int A = AddVertex(G, token);

    //printf("%s\n", token);
    fgets(line, linesize, infile);
    //word[strcspn(word, "\r\n")] = '\0';  // strip EOL char(s):
  }

  fclose(infile);

  int len = strlen(G->Names[0]);	//get length of dictionary;

  int i;
  int j;
  int k;
  int count = 0;	//count number of letter differences

  for (i = 0; i < G->NumVertices; i++)     //goes through each word
  {
    for (j = 0; j < G->NumVertices; j++)   //compares each word
    {
      for (k = 0; k < len; k++)   //goes through each character in the word
      {
        if (G->Names[i][k] != G->Names[j][k])	//character is not equal
          ++count;	//increment count
      }

      if (count == 1)	//count is equal to 1
        AddEdge(G, i, j, 0);	//differ by 1 character, so add edge

      count = 0;	//reset counter
    }
  }

}

int main()
{
  printf("** Starting Word Ladder App **\n\n");

  //
  // Run simple test:
  //
  //SimpleGraphTest();

  //
  // input the dictionary with words of length 4
  //
  Graph *G = CreateGraph(1);
  BuildGraph(G, "merriam-webster-len4.txt");
  PrintGraph(G, "Word Ladder", 0);
  printf("\n");

  char userInput[128];
  int userD;
  char carriageRet;

  printf(">> enter a word (ENTER to quit): ");
  fgets(userInput, 128, stdin);
  userInput[strcspn(userInput, "\r\n")] = '\0';  // strip EOL char(s):
  while (strlen(userInput) > 0)
  {

    Vertex v = LookUp(G, userInput);

    if (v == -1)
    	printf("'%s' is not found in the graph.\n", userInput);
    else
    {
		  PrintNeighbors(G, v);

		  printf(">> enter a BFS distance: ");
		  scanf("%d%c", &userD, &carriageRet);
		  PrintBFSd(G, v, userD);
    }
    printf("\n");



    printf(">> enter a word (ENTER to quit): ");
    fgets(userInput, 128, stdin);
    userInput[strcspn(userInput, "\r\n")] = '\0';  // strip EOL char(s):
  }
  

  DeleteGraph(G);

  //
  // done:
  //
  printf("\n** Done **\n");
  mymem_stats();

  printf("\n");

  return 0;
}
