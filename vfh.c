#include <stdlib.h>
#include <math.h>

#include "vfh.h"

/*
** I'm not done implementing the algorith.
**
** These parameters are there to help me remember them, basically.
*/

/* Parameters to the algorithm. */
#define DIM 10
#define CERTAINTY_GRID_RESOLUTION 0.1
#define ALPHA 5

/* Parameter for density calculation. */
#define DENSITY_A 10
#define DENSITY_B 5

grid_t * grid_init(short dimension, float resolution) {
	int i, j;
	
	/* Create a grid pointer and allocate memory for it. */
	grid_t * grid;
	grid = (grid_t *)malloc(sizeof(grid_t));
	
	if (NULL == grid) return NULL;
	
	grid->dimension = dimension;
	grid->resolution = resolution;
	
	/*
	** Allocate enough memory for the grid (dimension x dimension short ints).
	**
	** Making this a single allocation is simpler and, as it's an internal data
	** structure, it's not so problematic to iterate over it. This *IS* a
	** performance hack, too. 
	*/
	grid->cells = (short *)malloc(grid->dimension * grid->dimension * sizeof(short));
	
	if (NULL == grid->cells) return NULL;
	
	/* Initialize all elements to 0. */
	for (i = 0; i < grid->dimension; ++i) {
		for (j = 0; j < grid->dimension; ++j) {
			grid->cells[i * grid->dimension + j] = 0;
		}
	}
	
	return grid;
}

hist_t * hist_init(short alpha) {
	int i;
	
	/* Create a histogram pointer and allocate memory for it. */
	hist_t * hist;
	hist = (hist_t *)malloc(sizeof(hist_t));
	
	if (NULL == hist) return NULL;
	
	/* Initialize the histogram parameters. */
	hist->alpha = alpha;
	hist->sectors = 360 / alpha;
	
	/* Allocate the array to hold the obstacle density of each sector. */
	hist->densities = (int *)malloc(hist->sectors * sizeof(int));
	
	if (NULL == hist->densities) return NULL;
	
	/* Initialize all densities to 0. */
	for (i = 0; i < hist->sectors; ++i) {
		hist->densities[i] = 0;
	}
	
	return hist;
}

int hist_update(hist_t * hist, short * cells) {
	int i, j;
	float beta, density;
	
	/* Calculate densities based on grid. */
	for (i = 0; i < grid->dimension; ++i) {
		for (j = 0; j < grid->dimension; ++j) {
			/* Calculate the beta and obstacle density of this cell. */
			beta = atan2((double)(j - grid->dimension/2), (double)(i - grid->dimension/2));
			density = pow(grid->cells[i * grid->dimension + j], 2);
			density *= DENSITY_A - DENSITY_B * sqrt(pow(i - grid->dimension/2, 2) + pow(j - grid->dimension/2, 2));
			
			/* Add density to respective point in the histogram. */
			hist->densities[(int) beta / hist->alpha] += density;
		}
	}
}