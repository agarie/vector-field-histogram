// create_histogram_grid.c -- Grid creation test.
//
// This file creates a Histogram Grid with random obstacle densities and prints
// it as a map of 'o' (high density), 'x' (medium density) and ' ' (low density).
//
// The executable accepts a command-line argument for the seed of the RNG,
// which must be an integer. For example:
//
//   ./create_histogram_grid 11
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/histogram_grid.h"

#define DIMENSION 33 // Number of cells.
#define RESOLUTION 10 // Size of the cell in centimeters.

void mprint(grid_t * grid) {
  int dim = grid->dimension;

  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; ++j) {
      if (grid->cells[i * dim + j] >= 8) {
        printf("o");
      } else if (grid->cells[i * dim + j] >= 4) {
        printf("x");
      } else {
        printf(" ");
      }
    }

    printf("\n");
  }
}

int main(int argc, char* argv[]) {
  grid_t * grid = grid_init(DIMENSION, RESOLUTION);

  if (argc > 1) {
    int seed = atoi(argv[1]);
    srand(seed);
  }

  for (int i = 0; i < DIMENSION; ++i) {
    for (int j = 0; j < DIMENSION; ++j) {
      grid->cells[i * DIMENSION + j] = (int) floor((rand() * 10.0) / RAND_MAX);
    }
  }

  mprint(grid);
}
