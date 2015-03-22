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

#include "histogram_grid.h"
#include "polar_histogram.h"

#include "vfh.h"

/* Helpers. */

int modulo(int x, int m) {
  /* Source: http://crsouza.blogspot.com/2009/09/modulo-and-modular-distance-in-c.html */
  int r;

  if (m < 0) m = -m;

  r = x % m;
  return r < 0 ? r + m : r;
}

int modular_dist(int a, int b, int m) {
  int dist_a = modulo(a - b, m);
  int dist_b = modulo(b - a, m);

  return dist_a < dist_b? dist_a : dist_b;
}


//
// Control signals.
//

/* TODO: Improve the direction calculation. Re-read the paper. */
int calculate_direction(hist_t * hist, int objective_direction) {
  int sector, best_direction = -1;
  int dist_best_and_obj, dist_sector_and_obj; /* Just to improve readability. */

  // The objective_direction is given in DEGREES and mapped to a sector.
  objective_direction = (int) floor(objective_direction / hist->alpha);


  // Search the densities array and return the most similar to the objective
  // direction that is below the threshold.

  for (sector = 0; sector < hist->sectors; ++sector) {

    if (hist->densities[sector] < hist->threshold) {

      dist_best_and_obj = modular_dist(best_direction, objective_direction, hist->sectors);
      dist_sector_and_obj = modular_dist(sector, objective_direction, hist->sectors);

      /* If dist_a < dist_sector_and_obj, we maintain the current best_direction. */
      if (-1 == best_direction || dist_sector_and_obj < dist_best_and_obj) {
        /* This serves as initialization. */
        best_direction = sector;
      }
    }
  }

  /* Map the best_direction into degrees. */
  return (int) floor(best_direction * hist->alpha);
}
