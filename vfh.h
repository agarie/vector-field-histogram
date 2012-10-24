/*
** Virtual Field Histogram
**
** vfh.h
**
** Author: Carlos Agarie Junior
**
** This is an implementation of the Virtual Field Histogram algorithm,
** developed by J. Borenstein and Y.Koren in 1990.
*/

#ifndef VFH_H
#define VFH_H

/*
** Certainty Grid.
*/

/* grid: Stores a histogram (certainty) grid. */
struct grid {
	int dimension;
	double resolution;
	int *cells;
};

typedef struct grid grid_t;

/* rangefinder_data: Stores the distance/direction of a rangefinder reading. */
struct rangefinder_data {
	double distance;
	double direction;
};

typedef struct rangefinder_data rangefinder_data_t;

/* grid_init: Return a pointer to an empty grid. NULL otherwise. */
grid_t * grid_init(int dimension, double resolution);

/* grid_update: Update grid's cells with an array of n sensor readings. */
void grid_update(grid_t * grid, int current_position_x, int current_position_y,
	rangefinder_data_t * data, int n);

/* get_moving_window: Get a sub-grid of the grid centered in (x, y). */
grid_t * get_moving_window(grid_t * grid, int current_position_x,
	int current_position_y, int dim);

/*
** Polar Histogram.
*/

/* hist: Stores a polar histogram. */
struct hist {
	int alpha;
	int sectors;
	double threshold;
	double velocity_reduction;
	double density_a;
	double density_b;
	int * densities;
};

typedef struct hist hist_t;

/* hist_init: Return a pointer to a new hist. NULL otherwise. */
hist_t * hist_init(int alpha, double threshold, double vel_reduction,
	double density_a, double density_b);

/* hist_update: Update hist with grid's information. Return 1 if success. */
void hist_update(hist_t * hist, grid_t * grid);

/*
** Control signals.
*/

/*
** control_signals: Calculate the direction theta and the velocity multiplier
** based on hist.
*/
void control_signals(int * theta, double * vel_multiplier,
	hist_t * hist, int obj_direction);

/*
** calculate_direction: Return the sector in hist closest to the objective
** direction, given that it's obstacle density is less than the threshold of
** hist.
*/
int calculate_direction(hist_t * hist, int objective_direction);

/*
** calculate_vel_damping: Return the velocity damping factor, based on the
** obstacle density of the current sector and a .
*/
double calculate_vel_damping(double obstacle_density, double vel_reduction);

#endif