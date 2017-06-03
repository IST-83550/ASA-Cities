#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "kruskal.h"

int main() {
	/*	
		V - vertexes number.
		E - edges number.
		A - airports number.
	*/
	int V, E, A, i, j;
	airport_t* airports;
	int** data;
	edge** edges;

	/* Number of Cities. */
	assert(scanf("%d", &V) == 1);

	/* Number of Airports. */
	assert(scanf("%d", &A) == 1);
	assert(V >= 2 && 0 <= A && A <= V);
	
	airports = (airport_t*)malloc(A * sizeof(struct airport));
	assert(airports != NULL);
	
	/* Aiports cost. */
	for (i = 0; i < A; i++) {
    	assert(scanf("%d %d", &airports[i].vertex, &airports[i].cost) == 2);
	}

	/* Number of roads. */
	assert(scanf("%d", &E) == 1);
	assert(E >= 0);

	edges = (edge**)malloc((E + A) * sizeof(edge*));
	assert(edges != NULL);

	/* Reads weighted edges (Roads). */
	for (i = 0; i < E; i++) {
		int u, v, w;
    	edge* e = (edge*)malloc(sizeof(edge));		
    	assert(scanf("%d %d %d", &u, &v, &w) == 3);
    	
    	e->v1 = u;
		e->v2 = v;
		e->cost = w;

		edges[i] = e;
	}

	/* Auxiliary data. */
	data = (int**)malloc(2 * sizeof(int*));
	if (data != NULL) {
		data[0] = (int*)malloc(3 * sizeof(int));
		data[1] = (int*)malloc(3 * sizeof(int));
		if (!data[0] || !data[1]) {
			exit(EXIT_FAILURE);
		}
	}
	else {
		exit(EXIT_FAILURE);
	}

	if (E != 0) {
		/* Runs kruskal algorithm to the graph (without airports). */
		kruskal(edges, V, E, data[0]);
	}
	else {
		data[0][INSUFFICIENT] = 0;
		data[0][TOTALCOST] = INT_MAX;
	}

	if (A != 0) {
		/*	Adds a dummy node (V + 1) and connects all cities that have an
			airport to the dummy node (the weight of the edge will be the
			cost of building an airport in that city). */
		for (i = E,  j = 0; j < A; i++, j++) {
			edge* e = (edge*)malloc(sizeof(edge));
			
	    	e->v1 = airports[j].vertex;
			e->v2 = V + 1;
			e->cost = airports[j].cost;
			
			edges[i] = e;
		}

		/* Runs kruskal algorithm with roads and airports. */
		kruskal(edges, V + 1, E + A, data[1]);
	}
	else {
		data[1][INSUFFICIENT] = 0;
		data[1][TOTALCOST] = INT_MAX;
	}

	/* Outputs Result. */
	/* If both are insufficient the result is insufficient. */
	if (data[0][INSUFFICIENT] == 0 && data[1][INSUFFICIENT] == 0) {
		printf("Insuficiente\n");
	}
	else {
		/* The optimum solution uses airports because the other MST is incomplete. */
		if (data[0][INSUFFICIENT] == 0) {
			printf("%d\n", data[1][TOTALCOST]);
			printf("%d %d\n", data[1][NUMAIRS], V - data[1][NUMAIRS]);
		}
		/* The optimum solution uses airports. */
		else if (data[0][TOTALCOST] > data[1][TOTALCOST]) {
			printf("%d\n", data[1][TOTALCOST]);
			printf("%d %d\n", data[1][NUMAIRS], V - data[1][NUMAIRS]);
		}
		/* The optimum solution doesnt use airports. */
		else {
			printf("%d\n", data[0][TOTALCOST]);
			printf("0 %d\n", V - 1);
		}
	}

	/* Free previously allocated resources. */
	free(edges);
	free(airports);
	free(data[0]);
	free(data[1]);
	free(data);

	return EXIT_SUCCESS;

}