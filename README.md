# Vector Field Histogram

This is an implementation of the [Vector Field Histogram](http://en.wikipedia.org/wiki/Vector_Field_Histogram) algorithm, developed by J. Borenstein and Y.Koren in 1990.

I used this in a project for my real-time systems class at Embry-Riddle Aeronautical University.

Eventually, I'll add support to the VFH+ and VFH-star algorithms.
## To do

+ Complete the parameter list with descriptions.
+ Include drawings showing the referentials used for the sensors and the robot.
+ Introduce some examples and test data.
+ UNIT TESTS. The [cmockery](http://code.google.com/p/cmockery/) library appears to be good.
+ Create libvfh to make reusability easier.

## How to install

Wait.

It should be as easy as:

```bash
git clone <url for this repo>
cd vector-field-histogram
make
```

## How to use

Basically, this algorithm receives as inputs a lot of rangefinder sensor readings and generates control signals - the "best" direction and a damping factor for the max velocity.

The rangefinder readings are passed to the certainty grid as an array of `rangefinder_data_t` (a struct with fields `distance` and `direction`) via the function `grid_update()`.

Also, there are a lot of necessary parameters:

+ Certainty grid dimension (if it's even, it'll be incremented by 1)
+ Certainty grid resolution [cm]
+ Moving window dimension (same as certainty grid dimension)
+ Histogram alpha (must be a divisor of 360) [degrees]
+ Density_A (experimental)
+ Density_B (experimental)
+ Obstacle density threshold (experimental)
+ Objective position X (per-project)
+ Objective position Y (per-project)

## License

Copyright (c) 2012 Carlos Agarie. See LICENSE for details.
