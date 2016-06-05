# Vector Field Histogram

[![Build Status](https://travis-ci.org/agarie/vector-field-histogram.svg?branch=master)](https://travis-ci.org/agarie/vector-field-histogram)

This is an **incomplete** implementation of the [Vector Field Histogram](http://en.wikipedia.org/wiki/Vector_Field_Histogram) algorithm, developed by J. Borenstein and Y. Koren in 1990. Recently I got some motivation to study robotics once again and decided it was time to finally "finish" this code.

I originally used this library in a project for my real-time systems class at
[Embry-Riddle Aeronautical University](http://www.erau.edu) when I was studying
in the US.

Eventually, I'll add support to the VFH+ and VFH-star algorithms.

## How to install

Building the software should be as easy as:

```bash
git clone https://github.com/agarie/vector-field-histogram.git
cd vector-field-histogram
make
```

I'm not working on using autotools for the moment (I need to learn how to use
it, to be honest...). For now, it's possible to compile a program with the
object file `vfh.o`. The example `create_histogram_grid`(see Makefile) does
exactly that.

## The VFH algorithm

The VFH algorithm receives as inputs an array of rangefinder sensor readings
and generates control signals -- the "best" direction and a damping factor for
the max velocity of the robot.

The sensor readings are mapped into the Histogram Grid, a large matrix in which
each cell corresponds to an obstacle density in that area. Sonars and laser
rangefinders return a direction and a distance, so there must be a conversion
from polar to rectangular coordinates before processing them. The
correspondence between real world coordinates (i.e. `(x, y)`) and grid
coordinates (i.e. `(i, j)`) is given by a `resolution` parameter, which is the
size of the cells, such that `(x, y)` is in cell `(i, j)` if x is in [i *
resolution, (i + 1) * resolution] and j is in [j * resolution, (j + 1) *
resolution]. Each reading in a cell increases that cell's density by 1.

With the histogram grid in place, actual path planning can begin. A square
moving window centered around the robot is picked and each of its cells is
mapped to (m_ij, beta_ij); `m` is a function of the obstacle density of the
cell and its distance to the robot, and `beta` is the angular position of the
cell. The polar histogram separates the cells in `n = 360/alpha` sectors. Each
sector k has value M_k = sum(m_ij for (i, j) in sector_k). The moving window is
used to avoid computing on all cells (the histogram grid can be *huge*) and
because cells too far away probably won't contribute much to local planning.

A threshold is applied to the polar histogram, selecting only the sectors with
obstacle density low enough for safe passage. Finally, the sector with the
direction best matching the objective's is followed. The max velocity S_max is
decreased depending on the density of the chosen sector and the current angular
velocity.

## License

Copyright (c) 2012-2016 Carlos Agarie. See LICENSE for details.
