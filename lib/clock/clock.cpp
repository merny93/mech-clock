#include <clock.h>

Clock::Clock()
:   stepperX(STEP_PER_REV, X_DIR_PIN,  X_STEP_PIN, ENABLE_PIN), 
    stepperA(STEP_PER_REV, A_DIR_PIN,  A_STEP_PIN, ENABLE_PIN),
    controller(stepperX, stepperA)
    {
        
    
    };

void Clock::setup(){
    stepperX.begin(MOTOR_TARGET_RPM, MICROSTEPS);
    stepperA.begin(MOTOR_TARGET_RPM, MICROSTEPS);

    stepperA.setSpeedProfile(stepperA.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
    stepperX.setSpeedProfile(stepperX.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

    stepperX.setEnableActiveState(LOW);
    stepperA.setEnableActiveState(LOW);

    pinMode(A_LIMIT_PIN, INPUT_PULLUP);
    pinMode(X_LIMIT_PIN, INPUT_PULLUP);

    _x_pos = 0.0;
    _a_pos = 0.0;

}

void Clock::go_pos(double x_pos, double a_pos, bool dir){

    /*
        Just a dumb go to position.
        blocking!
    */
    double x_offset = (x_pos - _x_pos)/SCREW_PITCH*360;
    double a_offset = a_pos - _a_pos;
    if (dir){
        if (a_offset < 0){
            a_offset += 360;
        }
    } else {
        if (a_offset > 0){
            a_offset -= 360;
        }
    }
    controller.enable();
    controller.rotate(-x_offset + a_offset, a_offset);
    controller.disable();
    //set the new position
    _x_pos = x_pos;
    _a_pos = a_pos;

}

void Clock::go_rel(double x_rel, double a_rel){
    double x_rel_d = x_rel/SCREW_PITCH * 360.0;
    controller.enable();
    controller.rotate(-x_rel_d + a_rel, a_rel);
    controller.disable();
    _x_pos += x_rel_d;
    _a_pos = fmod(_a_pos + a_rel + 360, 360);
    
}

void Clock::go_a(double a_pos, bool dir){
    go_pos(_x_pos, a_pos, dir);
}

void Clock::go_x(double x_pos){
    go_pos(x_pos, _a_pos, true);
}


bool Clock::zero(){
    /* Function to zero out the clock*/
    
    //set to slow for zeroing
    stepperX.begin(MOTOR_TARGET_RPM/10, MICROSTEPS);
    stepperA.begin(MOTOR_TARGET_RPM/10, MICROSTEPS);

    stepperA.setSpeedProfile(stepperA.LINEAR_SPEED, MOTOR_ACCEL, 0);
    stepperX.setSpeedProfile(stepperX.LINEAR_SPEED, MOTOR_ACCEL, 0);

    //init
    controller.enable();
    bool fail = true;

    //if already touching move out a little
    if (digitalRead(A_LIMIT_PIN) == LOW){
        controller.rotate(-15.0, -15.0);
        delay(100);
        //if its still touching it failed 
        if (digitalRead(A_LIMIT_PIN) == LOW){
            return false;
        }
    }

    //a axis good to go
    unsigned wait_time_micros = 1;
    controller.startRotate(370.0, 370.0);
    while (wait_time_micros != 0){
        if (digitalRead(A_LIMIT_PIN) == LOW){
            controller.startBrake();
            fail = false;
        }
        wait_time_micros = controller.nextAction();
    }
    if (fail){
        return false;
    }

    //jam into the end stops
    controller.rotate(5.0,5.0);
    delay(100);

    //now for the x axis
    fail = true;

    //check if already touching
    if (digitalRead(X_LIMIT_PIN) == LOW){
        controller.rotate(-10.0,0.0);
        delay(100);
        //if its still touching it failed 
        if (digitalRead(X_LIMIT_PIN) == LOW){
            return false;
        }
    }
 
    //ready for x axis
    wait_time_micros = 1;
    controller.startRotate(10000.0, 0.0);
    while (wait_time_micros != 0){
        if (digitalRead(X_LIMIT_PIN) == LOW){
            //endstop pin got hit
            controller.startBrake();
            fail = false;
        }
        if (digitalRead(A_LIMIT_PIN) == HIGH){
            //other pin got unhit
            controller.startBrake();
        }
        wait_time_micros = controller.nextAction();
    }
    if (fail){
        return false;
    }

    controller.disable();

    setup();

    go_rel(5.0,25.0);

    return true;    
}

