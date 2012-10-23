#include <stdlib.h>
#include <math.h>

#include "vfh.h"

/* Parameters to the algorithm. */
#define CELLS 10
#define CERTAINTY_GRID_RESOLUTION 0.1
#define ALPHA 5

/* Parameter for density calculation. */
#define DENSITY_A 10
#define DENSITY_B 5

void histogramGridInit(histogramGrid_t * hg, short cells, float resolution) {
	int i, j;
	
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

void polarHistogramInit(polarHistogram_t * ph, histogramGrid_t * hg, short alpha) {
	int i, j;
	
	ph->alpha = alpha;
	ph->sectors = 360 / alpha;
	
	/* Allocate the array to hold the obstacle density of each sector. */
	ph->obstacleDensities = (int *)malloc(ph->sectors * sizeof(int));
	
	/* Initialize all densities to 0. */
	for (i = 0; i < ph->sectors; ++i) {
		ph->obstacleDensities[i] = 0;
	}
}

void polarHistogramUpdate(polarHistogram_t * ph, histogramGrid_t * hg) {
	int i, j;
	float beta, density;
	
	/* Calculate densities based on hg. */
	for (i = 0; i < hg->cells; ++i) {
		for (j = 0; j < hg->cells; ++j) {
			/* Calculate the beta and obstacle density of this cell. */
			beta = atan2((double)(j - hg->cells/2), (double)(i - hg->cells/2));
			density = pow(hg->grid[i * hg->cells + j], 2);
			density *= DENSITY_A - DENSITY_B * sqrt(pow(i - hg->cells/2, 2) + pow(j - hg->cells/2, 2));
			
			/* Add density to respective point in the histogram. */
			ph->obstacleDensities[(int) beta / ph->alpha] += density;
		}
	}
}