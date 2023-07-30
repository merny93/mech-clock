#include <Arduino.h>
#include <clock.h>

//all the magic is in there
Clock clock;

void setup()
{
  // DEBUG
  Serial.begin(9600);

  clock.setup();
  bool failed = true;
  for (int n_tries = 0; n_tries < 3; n_tries++)
  {
    if (clock.zero())
    {
      failed = false;
      break;
    }
  }
  if (failed)
  {
    Serial.println("Failed to zero, hanging");
    clock.controller.disable();
    while (true)
    {
    };
  }

  // zero the wheel positions
  clock.zero_display();
}
void loop()
{
  int arr1[4] = {0, 0, 0, 0};
  int arr2[4] = {0, 0, 0, 0};

  int *current_time = arr1;
  int *previous_time = arr2;

  for (int i = 0; i < 9999; i++)
  {
    //write the loop index into current time
    int t = i;
    for (int c = 0; c < 4; c++)
    {
      current_time[c] = t % 10;
      t /= 10;
    }
    
    //do the update
    Serial.print("Printing time: ");
    Serial.println(i);
    clock.set_display(current_time, previous_time);

    //ping pong the buffers
    int *tmp = previous_time;
    previous_time = current_time;
    current_time = tmp;
  }
}
