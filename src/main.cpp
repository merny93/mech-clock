#include <Arduino.h>
#include <clock.h>



// BasicStepperDriver stepperX(STEP_PER_REV, X_STEP_PIN, X_DIR_PIN);
// BasicStepperDriver stepperA(STEP_PER_REV, A_STEP_PIN, A_DIR_PIN);
// SyncDriver controller(stepperX, stepperA);

Clock clock;

void setup()
{
  //DEBUG
  Serial.begin(9600);

  clock.setup();
  bool failed = true;
  for (int n_tries = 0; n_tries < 3; n_tries++)
  {
    if (clock.zero()){
      failed = false;
      break;
    }
  }
  if (failed){
    Serial.println("Failed to zero, hanging");
    clock.controller.disable();
    while(true){};
  }
  clock.zero_display();
  Serial.println(clock._a_pos);
  Serial.println(clock._x_pos);

  // clock.go_x(5.0);
  // clock.go_x(0.0);
  // clock.go_a(180.0, true);
  // clock.go_a(0.0, false);
  // clock.go_pos(15.0, clock._a_pos, false);
  
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

 
