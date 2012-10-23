/*
** Certainty Grid
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

/* grid_update: Implement */

/*
** Polar Histogram
*/

/* hist: Stores a polar histogram. */
struct hist {
	short alpha;
	short sectors;
	int * densities;
};

typedef struct hist hist_t;

/* hist_init: Return a pointer to a new hist. NULL otherwise. */
hist_t * hist_init(short alpha);

/* hist_update: Update hist with grid's information. */
int hist_update(hist_t * hist, grid_t * grid);

/*
	
*/