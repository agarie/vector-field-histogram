#include <stdlib.h>

#include "histogram_grid.h"

void histogramGridInit(histogramGrid_t * hg, short cells, float resolution) {
	int i, j;
	
	/* Store the number of cells and their resolution. */
	hg->cells = cells;
	hg->resolution = resolution;
	
	/*
	** Allocate enough memory for the grid (cells x cells short ints).
	**
	** Making this a single allocation is simpler and, as it's an internal data
	** structure, it's not so problematic to iterate over it. This *IS* a
	** performance hack, too. 
	*/
	hg->grid = (short *)malloc(hg->cells * hg->cells * sizeof(short));
	
	/* Initialize all elements to 0. */
	for (i = 0; i < hg->cells; ++i) {
		for (j = 0; j < hg->cells; ++j) {
			hg->grid[i * hg->cells + j] = 0;
		}
	}
}