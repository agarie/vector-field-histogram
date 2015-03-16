#ifndef HISTOGRAM_GRID_H
#define HISTOGRAM_GRID_H

/* Certainty grid. */
struct grid {
	int dimension;
	int resolution;
	int *cells;
};

/* A rangefinder measurement. */
struct range_measure {
	int direction; /* [degrees] */
	unsigned long distance; /* [cm] */
};

typedef struct grid grid_t;
typedef struct range_measure range_measure_t;

/* Certainty grid. */

/* grid_init: Return a pointer to an empty grid. NULL otherwise. */
grid_t * grid_init(int dimension, int resolution);

/* grid_update: Update grid's cells with an array of sensor readings. */
int grid_update(grid_t * grid, int pos_x, int pos_y, range_measure_t data);

/* get_moving_window: Get a sub-grid of the grid centered in (x, y). */
grid_t * get_moving_window(grid_t * grid, int pos_x, int pos_y, int dim);
#endif
