#include <stdio.h>
#include <stdlib.h>

#include "kruskal.h"
#include "mergesort.h"

void merge(ItemToSort a, int low, int mid, int high) {

    int i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high) {
        if(less_sort(a[i],a[j]))
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }
    while (i <= mid)
        b[k++] = a[i++];
  
    while (j <= high)
        b[k++] = a[j++];
  
    k--;
    while (k >= 0) {
        a[low + k] = b[k];
        k--;
    }
}

void mergesort(ItemToSort a, int l, int r) {
 	int m = (r+l)/2;
 	if (r <= l) return;
 	mergesort(a, l, m); 	
 	mergesort(a, m+1, r); 	
 	merge(a, l, m, r);
}

void Sort(ItemToSort a, int r, int l) {
	if(l <= r) return;

	b = (ItemToSort)malloc(sizeof(Item)*(l-r+1));

	mergesort(a, r, l);

	free(b);
}