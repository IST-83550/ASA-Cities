#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_

struct airport {
	int vertex;
	int cost;
};

/* Airport. */
typedef struct airport airport_t;

/* Auxiliary data index macros. */
/* Insuficient index number. */
#define INSUFICIENT 0

/* Total MST cost index number. */
#define TOTALCOST 1

/* Airports index number. */
#define NUMAIRS 2

/* Roads index number. */
#define NUMRODS 3

typedef struct edge{
    int v1;
    int v2;
    int cost;
} edge;

typedef struct set_values{
    int djs;
    int rank;
} set_values;

void make_set(set_values *setv, int x);

void lin(set_values *setv, int x, int y);

int find_set(set_values *setv, int x);

void union_set(set_values *setv, int i, int j);

int cmpfunc (const void *a, const void *b);

/* Minimum Spanning Tree - Kruskal algorithm. */
void kruskal(edge *edges, int V, int E, int* data);

#endif