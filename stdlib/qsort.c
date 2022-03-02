#include <stdlib.h>

#include <string.h>

void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)) {
	if (nitems <= 1) {
		return;
	}
	
	void *pivot = base;
	void *left = base + size;
	void *right = base + (nitems - 1) * size;
	
	while (left < right) {
		while (compar(left, pivot) <= 0) {
			left += size;
		}
		
		while (compar(right, pivot) > 0) {
			right -= size;
		}
		
		if (left < right) {
			void *tmp = malloc(size);
			memcpy(tmp, left, size);
			memcpy(left, right, size);
			memcpy(right, tmp, size);
			free(tmp);
		}
	}
	
	qsort(base, (left - base) / size, size, compar);
	qsort(left + size, (base + (nitems - 1) * size - left) / size, size, compar);
}