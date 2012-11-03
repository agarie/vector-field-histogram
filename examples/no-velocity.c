/*
** no-velocity.c
**
** Author: Carlos Agarie Junior
**
** This is an example file used to show how to setup basic usage of the Virtual
** Field Histogram.
*/

#include <stdio.h>
#include <stdlib.h>

#include "../vfh.h"

#define MEASUREMENTS 10000
#define OBJECTIVE_DIRECTION 90 /* [degrees] */

int main(void) {
	int i, position_x, position_y;
	
	/* Declaration of the needed data structures. */
	grid_t * certainty_grid;
	range_measure_t measure[MEASUREMENTS];
	hist_t * polar_histogram;
	control_signal_t control_signal;
	
	/*
	** Initialization of the grid and the histogram.
	*/

	certainty_grid = grid_init(50, 10);
	polar_histogram = hist_init(2, 20, 10, 5);
	
	/* Are the initializations ok? */
	if (certainty_grid == NULL) return -1;
	if (certainty_grid->cells == NULL) return -1;
	if (polar_histogram == NULL) return -1;
	if (polar_histogram->densities == NULL) return -1;
	
	/*
	** Fake measures.
	*/

	printf("Measures\n");
		
	for (i = 0; i < MEASUREMENTS; ++i) {
		measure[i].direction = (int) ((360.0 * rand()) / RAND_MAX); /* [degrees] */
		measure[i].distance = (int) (((130.0 * rand()) / RAND_MAX) + 20); /* [cm] */
		
		if (i < 50)
			printf("\t%2d: %3d [cm], %3d [degrees]\n", i, (int) measure[i].distance,
				measure[i].direction);
	}
	
	if (i > 50) printf("\t...\n");

	/* Let's assume the 'robot' is in the middle of the grid. */
	position_x = position_y = (certainty_grid->dimension + 1) / 2;

	printf("\nPosition of the robot: (%d, %d)\n", position_x, position_y);

	/* Add the information from the measures to the grid. */
	printf("\nUpdating the certainty grid...\n");
	for (i = 0; i < MEASUREMENTS; ++i) {
		grid_update(certainty_grid, position_x, position_y, measure[i]);
	}
		
	/*
	** Calculating the control signals.
	*/
	
	/* Generate the histogram for the current grid. */
	printf("\nUpdating the polar histogram...\n");
	hist_update(polar_histogram, certainty_grid);
	
	/* What's the next direction? */
	control_signal.direction = calculate_direction(polar_histogram, OBJECTIVE_DIRECTION);
	
	printf("\nNext direction: %d [degrees]\n", control_signal.direction);

	free(certainty_grid);
	free(polar_histogram);
	
	certainty_grid = NULL;
	polar_histogram = NULL;

	return 0;
}