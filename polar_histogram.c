#include <stdlib.h>
#include <math.h>

#include "histogram_grid.h"
#include "polar_histogram.h"

//
// Polar histogram-related functions.
//

hist_t * hist_init(int alpha, double threshold, double density_a,
		double density_b) {

	/* Create a histogram pointer and allocate memory to it. */
	hist_t * hist;
	hist = (hist_t *)malloc(sizeof(hist_t));

	/* Is there enough memory for the histogram? */
	if (NULL == hist) return NULL;

  // TODO: `assert` that alpha is a divider of 360.

	/* Initialize the histogram parameters. */
	hist->alpha = alpha;
	hist->sectors = 360 / alpha;
	hist->threshold = threshold;

	/* Allocate the array to hold the obstacle density of each sector. */
	hist->densities = (int *)malloc(hist->sectors * sizeof(int));

	/* And is there enough memory for the densities array? */
	if (NULL == hist->densities) return NULL;

	/* Initialize all densities to 0. */
	for (int i = 0; i < hist->sectors; ++i) {
		hist->densities[i] = 0;
	}

	return hist;
}

void hist_update(hist_t * hist, grid_t * grid) {
	int dim; /* grid's dimension. */
	double dens_a, dens_b; /* parameters 'a' and 'b' for density calculation. */
	double beta, density;

	dim = grid->dimension;
	dens_a = hist->density_a;
	dens_b = hist->density_b;

	/* Calculate densities based on grid. */
	for (int i = 0; i < dim; ++i) {
		for (int j = 0; j < dim; ++j) {

			/* Calculate the angular position (beta) of this cell. */
			beta = atan2((double)(j - dim/2), (double)(i - dim/2));

			/* Calculate the obstacle density of this cell. */
			density = pow(grid->cells[i * dim + j], 2);
			density *= dens_a - dens_b * sqrt(pow(i - dim/2, 2) + pow(j - dim/2, 2));

			/* Add density to respective point in the histogram. */
			hist->densities[(int) floor(beta / hist->alpha)] += density;
		}
	}
}
