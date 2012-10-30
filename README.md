# Vector Field Histogram

This is an implementation of the [Vector Field Histogram](http://en.wikipedia.org/wiki/Vector_Field_Histogram) algorithm, developed by J. Borenstein and Y.Koren in 1990.

I'm going to use this in a project for my real-time systems class at Embry-Riddle Aeronautical University, where we're using ARM microcontrollers. That explains why this is a C implementation (I also don't like C++).

## To do

+ Complete the parameter list with descriptions.
+ Include drawings showing the referentials used for the sensors and the robot.
+ Introduce some examples and test data.
+ UNIT TESTS. The [cmockery](http://code.google.com/p/cmockery/) library appears to be good.
+ Create libvfh to make reusability easier.

## How to install

Wait.

## How to use

Basically, this algorithm receives as inputs a lot of rangefinder sensor readings and generates control signals - the "best" direction and a damping factor for the max velocity.

The rangefinder readings are passed to the certainty grid as an array of `rangefinder_data_t` (a struct with fields `distance` and `direction`) via the function `grid_update()`.

Also, there are a lot of necessary parameters:

+ Certainty grid dimension (must be odd)
+ Certainty grid resolution [m]
+ Moving window dimension (must be odd)
+ Histogram alpha (must be a divisor of 360) [degrees]
+ Density_A (experimental)
+ Density_B (experimental)
+ Obstacle density threshold (experimental)
+ Objective position X (per-project)
+ Objective position Y (per-project)

## License

Copyright (c) 2012 Carlos Agarie. See LICENSE for details.