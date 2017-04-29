#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "kruskal.h"

int main() {

	int V, E, A, i, j;
	airport_t* airports;
	int** data;
	edge* edges;

	/* Number of Cities. */
	assert(scanf("%d", &V) == 1);

	/* Number of Airports. */
	assert(scanf("%d", &A) == 1);
	assert(V >= 2 && 0 <= A && A <= V);
	
	airports = (airport_t*)malloc(A * sizeof(struct airport));
	
	/* Reads aiports cost. */
	for (i = 0; i < A; i++) {
    	assert(scanf("%d %d", &airports[i].vertex, &airports[i].cost) == 2);
	}

	/* Number of roads. */
	assert(scanf("%d", &E) == 1);
	assert(E >= 0);
	
	/* Edges array. */
	edges = (edge*)malloc((E + A) * sizeof(edge));

	/* Reads weighted edges (Roads). */
	for (i = 0; i < E; i++) {
		int u, v, w;
    	assert(scanf("%d %d %d", &u, &v, &w) == 3);
    	edges[i].v1 = u;
		edges[i].v2 = v;
		edges[i].cost = w;
	}

	/* Auxiliary data holder. */ 
	data = (int**)malloc(2 * sizeof(int*));
	if (data != NULL) {
		data[0] = (int*)malloc(4 * sizeof(int));
		data[1] = (int*)malloc(4 * sizeof(int));
		if (!data[0] || !data[1]) {
			exit(EXIT_FAILURE);
		}
	}
	else {
		exit(EXIT_FAILURE);
	}

	/* Runs kruskal algorithm to the graph without airports. */
	kruskal(edges, V, E, data[0]);

	/* Adds airports to the graph with a dummy node (V + 1). */
	for (i = E,  j = 0; j < A; i++, j++) {
    	edges[i].v1 = airports[j].vertex;
		edges[i].v2 = V + 1;
		edges[i].cost = airports[j].cost;
	}

	/* Runs kruskal algorithm with roads and airports.  */
	kruskal(edges, V + 1, E + A, data[1]);
	
	/* Outputs Result. */
	/* If both are insuficient result is insuficient. */
	if (data[0][INSUFICIENT] == 0 && data[1][INSUFICIENT] == 0) {
		printf("Insuficiente\n");
	}
	else {
		/* If one is insuficient the result is the other MST. */
		if (data[0][INSUFICIENT] == 0) {
			printf("%d\n", data[1][TOTALCOST]);
			printf("%d %d\n", data[1][NUMAIRS], V - data[1][NUMAIRS]);
		}
		/* If one is insuficient the result is the other MST.
		else if (data[1][INSUFICIENT] == 0) {
			printf("%d\n", data[0][TOTALCOST]);
			printf("%d %d\n", data[0][NUMAIRS], V - data[0][NUMAIRS] - 1);
		}*/
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

	free(edges);
	free(airports);
	free(data[0]);
	free(data[1]);
	free(data);

	return EXIT_SUCCESS;
}


/* IMPROVE EFFICIENCY:
	1) CHANGE DISJOINT SET DATA STRUCTURE (DIFICULTY: HIGH)
	2) CHANGE ALGORITHM TO WORK WITH ONLY ONE SORT OF THE EDGES (DIFICULTY: MEDIUM)
	3) CHANGE SORT ALGORITHM (DIFICULTY: EASY)
*/