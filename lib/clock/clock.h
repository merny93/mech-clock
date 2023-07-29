#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>
#include <SyncDriver.h>
#include <MultiDriver.h>

#define X_STEP_PIN 2
#define X_DIR_PIN 5
#define X_LIMIT_PIN 10

#define A_STEP_PIN 4
#define A_DIR_PIN 7
#define A_LIMIT_PIN 11

#define MOTOR_TARGET_RPM 250
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 2000
#define MICROSTEPS 8

#define ENABLE_PIN 8



#define STEP_PER_REV 600 // 200*3
#define SCREW_PITCH 2 // mm/rev

class Clock {

    BasicStepperDriver stepperX, stepperA;
public:
    double _x_pos;
    double _a_pos;
    SyncDriver controller;
        
    Clock ();
    void setup();
    void go_pos(double x_pos, double a_pos, bool dir);
    void go_x(double x_pos);
    void go_a(double a_pos, bool dir);
    void go_rel(double x_rel, double a_rel);
    bool zero();
    
};


    
#endif //CLOCK_H
