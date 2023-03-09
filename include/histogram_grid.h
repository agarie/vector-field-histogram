/**
 * @file histogram_grid.h
 * @brief Define what a Histogram Grid is and how to manipulate it.
 */

#ifndef HISTOGRAM_GRID_H
#define HISTOGRAM_GRID_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Histogram grid.
 *
 * Use `i * dimension + j` to iterate over the `cells`.
 * */
typedef struct {
  int dimension; /* Dimension in number of cells. */
  int resolution; /* Centimeters per cell. */
  int *cells; /* The obstacle density in each cell. */
} grid_t;

/* A rangefinder measurement.
 *
 */
typedef struct {
  int direction; /* [degrees] */
  unsigned long distance; /* [cm] */
} range_measure_t;

/* grid_init: Return a pointer to an empty (all zeros) grid. NULL otherwise. */
grid_t * grid_init(int dimension, int resolution);

/* get_moving_window: Get a sub-grid of the grid centered in (x, y). */
grid_t * get_moving_window(grid_t * grid, int pos_x, int pos_y, int dimension);

/* grid_update: Update grid's cells with an array of sensor readings. */
int grid_update(grid_t * grid, int pos_x, int pos_y, range_measure_t data);

#endif
