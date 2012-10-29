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
** Struct definitions.
*/

/* Certainty grid. */
struct grid {
	int dimension;
	double resolution;
	int *cells;
};

/* A rangefinder measurement. */
struct range_measure {
	int direction; /* [degrees] */
	unsigned long distance; /* [cm] */
};

/* Control signal created by the algorithm. */
struct control_signal {
	int next_direction; /* [degrees] */
	double damping; /* adimentional */
};

/* Polar histogram. */
struct hist {
	int alpha;
	int sectors;
	double threshold;
	double velocity_reduction;
	double density_a;
	double density_b;
	int * densities;
};

/* Typedefs. */
typedef struct grid grid_t;
typedef struct range_measure range_measure_t;
typedef struct control_signal control_signal_t;
typedef struct hist hist_t;

/*
** Function prototypes.
*/

/* Helpers. */

/* modulo: Return x modulo m. */
int modulo(int x, int m);

/* modular_dist: Return the distance between a and b in modular arithmetic. */
int modular_dist(int a, int b, int modulo)

/* Certainty grid. */

/* grid_init: Return a pointer to an empty grid. NULL otherwise. */
grid_t * grid_init(int dimension, double resolution);

/* grid_update: Update grid's cells with an array of n sensor readings. */
void grid_update(grid_t * grid, int current_position_x, int current_position_y,
	range_measure_t * data, int n);

/* get_moving_window: Get a sub-grid of the grid centered in (x, y). */
grid_t * get_moving_window(grid_t * grid, int current_position_x,
	int current_position_y, int dim);

/* Polar Histogram. */

/* hist_init: Return a pointer to a new hist. NULL otherwise. */
hist_t * hist_init(int alpha, double threshold, double vel_reduction,
	double density_a, double density_b);

/* hist_update: Update hist with grid's information. Return 1 if success. */
void hist_update(hist_t * hist, grid_t * grid);

/* Control signals. */

/*
** calculate_direction: Return the sector in hist closest to the objective
** direction, given that its obstacle density is less than the threshold
** specified in hist.
*/
int calculate_direction(hist_t * hist, int objective_direction);

/*
** calculate_damping: Return the velocity damping factor, based on the obstacle
** density of the current sector and a damping constant.
*/
double calculate_damping(double obstacle_density, double damping_constant);

#endif