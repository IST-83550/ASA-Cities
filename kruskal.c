#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "kruskal.h"

void make_set(set_values *setv, int x) {
    setv[x].djs = x;
	setv[x].rank = 0;	
}

void lin(set_values *setv, int x, int y) {

	if(setv[x].rank > setv[y].rank){
		setv[y].djs = x;
	}
	else {
		setv[x].djs = y;
		
		if(setv[x].rank == setv[y].rank)
			setv[y].rank++;
	}	
}

int find_set(set_values *setv, int x) {
	if(setv[x].djs != x)
		setv[x].djs = find_set(setv, setv[x].djs);
	return setv[x].djs; 		
}

void union_set(set_values *setv, int i, int j) {
	lin(setv, find_set(setv, i), find_set(setv, j));
}

int cmpfunc(const void *a, const void *b) {
  	edge *ia = ( edge *)a;
    edge *ib = ( edge *)b;
    return (int)(100.f*ia->cost - 100.f*ib->cost);
}

void kruskal(edge *edges, int V, int E, int* data) {
	int i, total_cost = 0, count_edges = 0, count_airports = 0;
	set_values *setv = NULL;

	setv = malloc(V * sizeof(set_values));

	/* printf("V:%d E:%d\n", V, E);
	for (i = 0; i < E; i++) {
		printf("%d %d %d\n", edges[i].v1, edges[i].v2, edges[i].cost);
	}
	printf("----------------\n"); */

	/* Make Set. */
	for (i = 0; i < V; i++) {
		make_set(setv, i);
	}

	/* Sorts edges. */
	/* FIXME - CHANGE SORT ALGORITHM. */
	qsort(edges, E, sizeof(edge), cmpfunc);

	for (i = 0; i < E; i++) {
		if (find_set(setv, edges[i].v1 - 1) != find_set(setv, edges[i].v2 - 1)) {
			total_cost += edges[i].cost;
			union_set(setv, edges[i].v1 - 1, edges[i].v2 - 1);
			count_edges++;
			if (edges[i].v1 == V || edges[i].v2 == V) {
				count_airports++;
			}
		}
	}

	if(count_edges != V - 1) {
		data[INSUFICIENT] = 0;
	}
	else {
		data[INSUFICIENT] = 1;
	}
	
	data[NUMAIRS] = count_airports;
	data[TOTALCOST] = total_cost;

	free(setv);
	
}