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
	
	/* Create a grid pointer and allocate memory to it. */
	grid_t * grid;
	grid = (grid_t *)malloc(sizeof(grid_t));
	
	if (NULL == grid) return NULL;

	/* Initialize grid's parameters. */
	grid->dimension = dimension;
	grid->resolution = resolution;
	
	/*
	** Allocate enough memory for the grid (dimension x dimension shorts).
	**
	** Making this a single allocation is simpler. Also, This *IS* a performance
	** hack.
	*/
	grid->cells = (short *)malloc(dimension * dimension * sizeof(short));
	
	if (NULL == grid->cells) return NULL;
	
	/* Initialize all elements to 0. */
	for (i = 0; i < dimension; ++i) {
		for (j = 0; j < dimension; ++j) {
			grid->cells[i * dimension + j] = 0;
		}
	}
	
	return grid;
}

hist_t * hist_init(short alpha, double density_a, double density_b) {
	int i;
	
	/* Create a histogram pointer and allocate memory to it. */
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

int hist_update(hist_t * hist, grid_t * grid) {
	int i, j;
	int dim; /* grid's dimension. */
	float dens_a, dens_b; /* parameters 'a' and 'b' for density calculation. */
	float beta, density;
	
	dim = grid->dimension;
		
	if (hist->density_a >= 0 || hist->density_b >= 0) {
		return 0;
	} else {
		dens_a = hist->density_a;
		dens_b = hist->density_b;
	}
	
	/* Calculate densities based on grid. */
	for (i = 0; i < dim; ++i) {
		for (j = 0; j < dim; ++j) {

			/* Calculate the angular position beta of this cell. */
			beta = atan2((double)(j - dim/2), (double)(i - dim/2));
			
			/* Calculate the obstacle density of this cell. */
			density = pow(grid->cells[i * dim + j], 2);
			density *= dens_a - dens_b * sqrt(pow(i - dim/2, 2) + pow(j - dim/2, 2));
			
			/* Add density to respective point in the histogram. */
			hist->densities[(int) floor(beta / hist->alpha)] += density;
		}
	}
	
	return 1;
}