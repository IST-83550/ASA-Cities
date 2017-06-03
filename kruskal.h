/*
    Disjoint-Set data structure.
    Operations: Make-Set, FindSet, UnionSet.
    
    Kruskal algorithm (Minimum Spanning Tree)
*/

#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_

/* ADT MergeSort Macros. */
#define Item edge*
#define ItemToSort edge**
#define KeyToSort(A) A->cost
#define less_sort(A, B) ( KeyToSort(A) <= KeyToSort(B) )

/*  Auxiliary data index macros. */
/*  Insuficient index number. */
#define INSUFFICIENT 0

/*  Total MST cost index number. */
#define TOTALCOST 1

/*  Airports index number. */
#define NUMAIRS 2

/*  Airport representation. */
typedef struct airport {
	int vertex;
	int cost;
} airport_t;

/*  Graph edge representation. */
typedef struct edge {
    int v1;
    int v2;
    int cost;
} edge;

/*  Set element. */
typedef struct set_value {
    int p;
    int rank;
} set_value;

/*  Creates a disjoint set to represent a set of vertexes. */
void makeSet(set_value *setv, int x);

/*  Links two sets.
    It should be previously checked if x and y are in different sets. */
void link(set_value *setv, int x, int y);

/*  Identifies vertex's set.
    Uses path compression. */
int findSet(set_value *setv, int x);

/*  Merges sets of vertexes together. */
void unionSet(set_value *setv, int i, int j);

/*  Comparison function to be used by the sort algorithm. */
int cmpfunc (const void *a, const void *b);

/*  Executes the kruskal MST algorithm given the number
    of vertexes (V) and edges (E) of the graph. */
void kruskal(edge **edges, int V, int E, int* data);

#endif /* _KRUSKAL_H_ */