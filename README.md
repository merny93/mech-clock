# mech-clock
Electro-mechanical 7 segment display clock

`src/main.cpp` contains high level (ish, its `c`) routines regarding the clock. 
Similar things one might imagine a `main` file containing when building a clock with a digital 7 segment display.

`lib/clock` contains the hardware abstraction layer (HAL) for the clock I built. 
It is based around the [StepperDriver](https://github.com/laurb9/StepperDriver) library which seems to be acceptable for my applications.

## TODO

It currently does not work: The software is waiting for hardware to be completed to test more fully
