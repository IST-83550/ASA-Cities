#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "kruskal.h"
#include "mergesort.h"

void makeSet(set_value *setv, int x) {
    setv[x].p = x;
	setv[x].rank = 0;
}

void link(set_value *setv, int x, int y) {

	/*	If x and y are not in the same set.
		(Should be previously checked). */
	if(setv[x].rank > setv[y].rank) {
		setv[y].p = x;
	}
	else {
		setv[x].p = y;
		
		if(setv[x].rank == setv[y].rank)
			setv[y].rank++;
	}	
}

int findSet(set_value *setv, int x) {
	if(setv[x].p != x) {
		setv[x].p = findSet(setv, setv[x].p);		
	}
	return setv[x].p;
}

void unionSet(set_value *setv, int i, int j) {
	link(setv, findSet(setv, i), findSet(setv, j));
}

void kruskal(edge **edges, int V, int E, int* data) {
	int i, total_cost = 0, n_edges = 0, n_airports = 0;
	set_value *setv = NULL;

	setv = malloc(V * sizeof(set_value));

	/* Make Set. */
	for (i = 0; i < V; i++) {
		makeSet(setv, i);
	}

	/* Sorts edges (MergeSort). */
	Sort(edges, 0, E - 1);

	for (i = 0; i < E; i++) {
		if (findSet(setv, edges[i]->v1 - 1) != findSet(setv, edges[i]->v2 - 1)) {
			
			total_cost += edges[i]->cost;
			unionSet(setv, edges[i]->v1 - 1, edges[i]->v2 - 1);
			n_edges++;

			/* If one of the two vertexes is the dummy node
				then an airport was used to build the MST. */
			if (edges[i]->v1 == V || edges[i]->v2 == V) {
				n_airports++;
			}
		}
	}

	/*	Updates data.
		If the number of edges is different than V - 1
		the MST doesnt cover all vertexes (insufficient). */
	if(n_edges != V - 1) {
		data[INSUFFICIENT] = 0;
	}
	else {
		data[INSUFFICIENT] = 1;
	}
	data[NUMAIRS] = n_airports;
	data[TOTALCOST] = total_cost;

	free(setv);

}
