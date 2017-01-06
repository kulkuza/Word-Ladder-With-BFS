/*graph.h*/

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
// Graph:
//
typedef int Vertex;

typedef struct Edge
{
  Vertex  src;
  Vertex  dest;
  int     weight;
  struct Edge *next;
} Edge;

typedef struct Graph
{
  Edge **Vertices;
  char **Names;
  int    NumVertices;
  int    NumEdges;
  int    Capacity;
} Graph;

Graph  *CreateGraph(int N);
int     AddVertex(Graph *G, char *name);
int     AddEdge(Graph *G, Vertex src, Vertex dest, int weight);
Vertex *Neighbors(Graph *G, Vertex v);
void    PrintGraph(Graph *G, char *title, int complete);
Vertex *BFS(Graph *G, Vertex v);
Vertex *DFS(Graph *G, Vertex v);

void freeNames(Graph *G);
void freeVerticesHelper(Edge *Vertices);
void freeVertices(Graph *G);
void freeGraph(Graph *G);
void DeleteGraph(Graph *G);

Vertex LookUp(Graph *G, char *name);

void PrintNeighbors(Graph *G, Vertex v);

Vertex *BFSd(Graph *G, Vertex v, int d);
void PrintBFSd(Graph *G, Vertex v, int d);
