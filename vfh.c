#include <stdlib.h>
#include <math.h>

#include "vfh.h"

/* Guarantee that this is the MIN macro used. */
#undef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/*
** These parameters are there to help me remember them, basically.
*/

/* Parameters to the algorithm. */
#define DIM 10
#define CERTAINTY_GRID_RESOLUTION 0.1
#define ALPHA 5

/* Parameters for density calculation. */
#define DENSITY_A 10
#define DENSITY_B 5

/* Parameters for direction and velocity calculations. */
#define OBSTACLE_DENSITY_THRESHOLD 10
#define VELOCITY_REDUCTION 30
	
/* Where we want to go. */
#define OBJECTIVE_X 87
#define OBJECTIVE_Y 87	

/*
** Certainty grid.
*/

grid_t * grid_init(short dimension, double resolution) {
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

/*
** Polar histogram.
*/

hist_t * hist_init(short alpha, double threshold, double velocity_reduction, double density_a, double density_b) {
	int i;
	
	/* Create a histogram pointer and allocate memory to it. */
	hist_t * hist;
	hist = (hist_t *)malloc(sizeof(hist_t));
	
	
	if (NULL == hist) return NULL;
	
	/* Initialize the histogram parameters. */
	hist->alpha = alpha;
	hist->sectors = 360 / alpha;
	hist->threshold = threshold;
	hist->velocity_reduction = velocity_reduction;
	
	/* Allocate the array to hold the obstacle density of each sector. */
	hist->densities = (int *)malloc(hist->sectors * sizeof(int));
	
	if (NULL == hist->densities) return NULL;
	
	/* Initialize all densities to 0. */
	for (i = 0; i < hist->sectors; ++i) {
		hist->densities[i] = 0;
	}
	
	return hist;
}

void hist_update(hist_t * hist, grid_t * grid) {
	int i, j;
	int dim; /* grid's dimension. */
	double dens_a, dens_b; /* parameters 'a' and 'b' for density calculation. */
	double beta, density;
	
	dim = grid->dimension;		
	dens_a = hist->density_a;
	dens_b = hist->density_b;
	
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
}

/*
** Control signals.
*/

void control_signals(short * theta, double * velocity_multiplier, hist_t * hist, short objective_direction) {
	*theta = calculate_direction(hist, objective_direction);
	
	*velocity_multiplier = calculate_vel_multiplier(hist->densities[*theta], hist->velocity_reduction);
}

short calculate_direction(hist_t * hist, short obj_direction) {
	short sector, best_direction = -1;
	
	/*
	** Search the densities array and return the most similar to the objective
	** direction that is below the threshold.
	*/
	for (sector = 0; sector < hist->sectors; ++sector) {
		if (hist->densities[sector] < hist->threshold) {
			if (-1 == best_direction) {
				best_direction = sector;
			} else {
				best_direction = MIN(abs(best_direction - obj_direction),
														abs(sector - obj_direction));
			}
		}
	}
	
	return best_direction;
}

double calculate_vel_multiplier(double obstacle_density, double velocity_reduction) {
	return 1 - MIN(obstacle_density, velocity_reduction) / velocity_reduction;
}