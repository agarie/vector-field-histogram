/*
** Certainty Grid.
*/

/* grid: Stores a histogram (certainty) grid. */
struct grid {
	short dimension;
	float resolution;
	short *cells;
};

typedef struct grid grid_t;

/* grid_init: Return a pointer to an empty grid. NULL otherwise. */
grid_t * grid_init(short dimension, float resolution);

/* grid_update: Update grid's cells with sensor's readings. */

/* get_local_map_of: Get a sub-grid of the grid. */

/*
** Polar Histogram.
*/

/* hist: Stores a polar histogram. */
struct hist {
	short alpha;
	short sectors;
	float density_a;
	float density_b;
	int * densities;
};

typedef struct hist hist_t;

/* hist_init: Return a pointer to a new hist. NULL otherwise. */
hist_t * hist_init(short alpha, double density_a, double density_b);

/* hist_update: Update hist with grid's information. Return 1 if success. */
int hist_update(hist_t * hist, grid_t * grid);

/*
** Control signals.
*/