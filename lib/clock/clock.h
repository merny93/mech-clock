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

#define MOTOR_TARGET_RPM 100
#define MOTOR_ACCEL 2000
#define MOTOR_DECEL 2000
#define MICROSTEPS 8

#define ENABLE_PIN 8



#define STEP_PER_REV 600 // 200*3
#define SCREW_PITCH 4 // mm/rev

#define A_RESTING_POS 10.0
#define X_RESTING_POS 5.0

#define WHEELS_N 12 // 3 per digit for a total of 12
#define WHEELS_PER_DIGIT 3

#define BUMP_OFFSET 1.0// degrees offset 

extern const float WHEELS_POS[WHEELS_N];
extern const float DIGIT_MAP[10][3];

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
    void zero_display();
    void set_display(int* new_display, int* prev_display);
    
};


    
#endif //CLOCK_H
