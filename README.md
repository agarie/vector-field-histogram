# Vector Field Histogram

[![Build Status](https://travis-ci.org/agarie/vector-field-histogram.svg?branch=master)](https://travis-ci.org/agarie/vector-field-histogram)

This is an **incomplete** implementation of the [Vector Field Histogram](http://en.wikipedia.org/wiki/Vector_Field_Histogram) algorithm, developed by J. Borenstein and Y. Koren in 1990. Recently I got some motivation to study robotics once again and decided it was time to finally "finish" this code.

I originally used this library in a project for my real-time systems class at [Embry-Riddle Aeronautical University](http://www.erau.edu) when I was studying in the US.

Eventually, I'll add support to the VFH+ and VFH-star algorithms.

## How to install

It should be as easy as:

```bash
git clone https://github.com/agarie/vector-field-histogram.git
cd vector-field-histogram
make
```

I'm not working on using autotools for the moment (I need to learn how to use it, to be honest...). For now, it's possible to compile a program with the object file `vfh.o`. The example `create_histogram_grid`(see Makefile) does exactly that.

## How to use

The VFH algorithm receives as inputs an array of rangefinder sensor readings and generates control signals -- the "best" direction and a damping factor for the max velocity of the robot. The parameters:

+ Certainty grid dimension (in cells)
+ Certainty grid resolution [cm]
+ Moving window dimension (same as certainty grid dimension)
+ Histogram alpha (must be a divisor of 360) [degrees]
+ Density_A (experimental)
+ Density_B (experimental)
+ Obstacle density threshold (experimental)
+ Objective position X (per-project)
+ Objective position Y (per-project)

## License

Copyright (c) 2012-2015 Carlos Agarie. See LICENSE for details.
