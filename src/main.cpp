#include <Arduino.h>
#include <clock.h>



// BasicStepperDriver stepperX(STEP_PER_REV, X_STEP_PIN, X_DIR_PIN);
// BasicStepperDriver stepperA(STEP_PER_REV, A_STEP_PIN, A_DIR_PIN);
// SyncDriver controller(stepperX, stepperA);

Clock clock;

void setup() {
  Serial.begin(9600);
    // stepperX.begin(MOTOR_TARGET_RPM, MICROSTEPS);
    // stepperA.begin(MOTOR_TARGET_RPM, MICROSTEPS);

    // stepperA.setSpeedProfile(stepperA.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
    // stepperX.setSpeedProfile(stepperX.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
    clock.setup();
    clock.zero();
    // clock.go_rel(0.0, 10.0);
    // clock.go_pos(0.0,20.0, true );
}
int i = 0;
void loop() {
  
  // if (!digitalRead(X_LIMIT_PIN)){
  //   Serial.println("X limit");
  // }else if (!digitalRead(A_LIMIT_PIN)){
  //   Serial.println("A limit");
  // }

  // Serial.println("Moving");
  // clock.controller.enable();
  // // clock.controller.rotate(360, 360);
  // i+=40;
  // clock.go_pos(i/20, i%360, false);
  // delay(1000);
  // controller.rotate(-90*5, -30*15);
  // delay(1000);
  // controller.rotate(0, -30*15);
  // delay(30000);
}

 
