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

/* Control signal created by the algorithm. */
typedef struct {
  int direction; /* [degrees] */
} control_signal_t;

/* Helpers. */

/* modulo: Return x modulo m. */
int modulo(int x, int m);

/* modular_dist: Return the distance between a and b in modular arithmetic. */
int modular_dist(int a, int b, int m);

/* Control signals. */

/*
** calculate_direction: Return the sector in hist closest to the objective
** direction, given that its obstacle density is less than the threshold
** specified in hist. The objective_direction is given in DEGREES.
*/
int calculate_direction(hist_t * hist, int objective_direction);

#endif
