/*
** Certainty Grid.
*/

/* grid: Stores a histogram (certainty) grid. */
struct grid {
	short dimension;
	double resolution;
	short *cells;
};

typedef struct grid grid_t;

/* grid_init: Return a pointer to an empty grid. NULL otherwise. */
grid_t * grid_init(short dimension, double resolution);

/* grid_update: Update grid's cells with sensor's readings. */

/* get_local_map_of: Get a sub-grid of the grid centered in (x, y). */

/*
** Polar Histogram.
*/

/* hist: Stores a polar histogram. */
struct hist {
	short alpha;
	short sectors;
	double threshold;
	double velocity_reduction;
	double density_a;
	double density_b;
	int * densities;
};

typedef struct hist hist_t;

/* hist_init: Return a pointer to a new hist. NULL otherwise. */
hist_t * hist_init(short alpha, double threshold, double velocity_reduction,
	double density_a, double density_b);

/* hist_update: Update hist with grid's information. Return 1 if success. */
void hist_update(hist_t * hist, grid_t * grid);

/*
** Control signals.
*/

/* control_signals: Calculate the direction theta and the velocity multiplier based on hist. */
void control_signals(short * theta, double * velocity_multiplier,
	hist_t * hist, short obj_direction);

/* calculate_direction: */
short calculate_direction(hist_t * hist, short objective_direction);

/* calculate_vel_multiplier: */
double calculate_vel_multiplier(double obstacle_density, double vel_reduction);