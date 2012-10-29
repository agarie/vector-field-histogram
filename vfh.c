/*
** Virtual Field Histogram
**
** vfh.c
**
** Author: Carlos Agarie Junior
**
** This is an implementation of the Virtual Field Histogram algorithm, developed
** by J. Borenstein and Y.Koren in 1990.
*/

#include <stdlib.h>
#include <math.h>

#include "vfh.h"

/* Guarantee that this is the MIN macro used. */
#undef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/*
** These parameters are there to help me remember them, basically.
*/

/* Parameters for the grid. */
#define DIM 11 /* Must be an odd number. */
#define CERTAINTY_GRID_RESOLUTION 0.1

/* Parameters for the moving window. */
#define WINDOW_DIM 5

/* Parameters for histogram calculation. */
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

/* Helper functions. */

int modulo(int x, int modulo) {
	/* Source: http://crsouza.blogspot.com/2009/09/modulo-and-modular-distance-in-c.html */
	int r;
	
	if (modulo < 0) modulo = -modulo;
	
	r = x % m;
	return r < 0 ? r + m : r;
}

int modular_dist(int a, int b, int modulo) {
	int dist_a, dist_b;
	
	dist_a = modulo(a - b, modulo);
	dist_b = modulo(b - a, modulo);
	
	return dist_a < dist_b? dist_a : dist_b;
}	

/*
** Certainty grid-related functions.
*/

grid_t * grid_init(int dimension, double resolution) {
	int i, j;
	
	/* Create a grid pointer and allocate memory to it. */
	grid_t * grid;
	grid = (grid_t *)malloc(sizeof(grid_t));
	
	/* Is there enough memory for the grid? */
	if (NULL == grid) return NULL;

	/* Initialize grid's parameters. */
	grid->dimension = dimension;
	grid->resolution = resolution;
	
	/*
	** Allocate enough memory for the grid (dimension x dimension ints).
	**
	** Making this a single allocation is simpler. Also, This *IS* a performance
	** hack. Use [i * dim + j] to iterate over it.
	*/
	grid->cells = (int *)malloc(dimension * dimension * sizeof(int));
	
	/* Is there enough memory for the cells?*/
	if (NULL == grid->cells) return NULL;
	
	/* Initialize all elements to 0. */
	for (i = 0; i < dimension; ++i) {
		for (j = 0; j < dimension; ++j) {
			grid->cells[i * dimension + j] = 0;
		}
	}
	
	return grid;
}

void grid_update(grid_t * grid, int current_position_x, int current_position_y,
								range_measure_t * data, int n) {

	int i, dim, x_cartesian, y_cartesian;

	dim = grid->dimension;
	
	/*
	** Transform each sensor reading into cartesian coordinates and increase the
	** corresponding cell's obstacle density.
	**
	** Polar to cartesian:
	** (r, o) -> (r * cos(x), r * sin(y))
	*/
	for (i = 0; i < n; ++i) {
		x_cartesian = (int) floor(data[i].distance * cos(data[i].direction));
		x_cartesian += current_position_x;
		
		y_cartesian = (int) floor(data[i].distance * sin(data[i].direction));
		y_cartesian += current_position_y;

		/* Is this position inside the grid? (to avoid overflows) */
		if (x_cartesian < dim && y_cartesian < dim) {
			grid->cells[x_cartesian * dim + y_cartesian] += 1;			
		}
	}
}

/* TODO */
grid_t * get_moving_window(grid_t * grid, int current_position_x,
													int current_position_y, int dim) {

	int i, j; /* Indexes for the moving window. */
	int grid_i, grid_j; /* Indexes for the grid. */
	grid_t * moving_window;
	
	/*
	** Create a window with dimension dim and the same resolution as grid.
	**
	** If grid_init returns NULL, exit the function.
	*/
	moving_window = grid_init(dim, grid->resolution);
		
	if (NULL != moving_window) {
		
		/* Populate moving_window's cells with the values of the ones in grid. */
		for (i = 0; i < dim; ++i) {
			for (j = 0; j < dim; ++j) {
				
				/* x and y are the center coordinates of the body with sensors. */
				grid_i = i + current_position_x + (dim - 1) / 2;
				grid_j = j + current_position_y + (dim - 1) / 2;
				
				/* Copy the information from the grid to the moving window. */
				if (grid_i < grid->dimension && grid_j < grid->dimension) {
					moving_window->cells[i * dim + j] = grid->cells[grid_i *
						grid->dimension + grid_j];					
				}
			}
		}
	}
	
	return moving_window;
}

/*
** Polar histogram-related functions.
*/

hist_t * hist_init(int alpha, double threshold, double velocity_reduction,
									double density_a, double density_b) {

	int i;
	
	/* Create a histogram pointer and allocate memory to it. */
	hist_t * hist;
	hist = (hist_t *)malloc(sizeof(hist_t));
	
	/* Is there enough memory for the histogram? */
	if (NULL == hist) return NULL;
	
	/* Initialize the histogram parameters. */
	hist->alpha = alpha;
	hist->sectors = 360 / alpha;
	hist->threshold = threshold;
	hist->velocity_reduction = velocity_reduction;
	
	/* Allocate the array to hold the obstacle density of each sector. */
	hist->densities = (int *)malloc(hist->sectors * sizeof(int));
	
	/* And is there enough memory for the densities array? */
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

/*
** Control signals-related functions.
*/

int calculate_direction(hist_t * hist, int objective_direction) {
	int sector, best_direction = -1;
	int dist_a, dist_b; /* Just to improve readability. TODO: better names. */
	
	/*
	** Search the densities array and return the most similar to the objective
	** direction that is below the threshold.
	*/
	for (sector = 0; sector < hist->sectors; ++sector) {
		
		if (hist->densities[sector] < hist->threshold) {
			
			dist_a = modular_dist(best_direction*, objective_direction, hist->sectors);
			dist_b = modular_dist(sector, objective_direction, hist->sectors);
			
			/* If dist_a < dist_b, we maintain the current best_direction. */
			if (-1 == best_direction || dist_b < dist_a) {
				/* This serves as initialization. */
				best_direction = sector;
			}
		}
	}
	
	return best_direction;
}

double calculate_damping(double obstacle_density, double damping_constant) {
	return 1.0 - (MIN(obstacle_density, damping_constant) / damping_constant);
}