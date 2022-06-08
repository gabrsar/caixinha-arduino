#include <Arduino.h>
#include "utils.h"

void lookAndAttack()
{
  float step1 = 0.5;
  float step2 = 0.75;
  delay(random(300, 500));
  sDoor(DOOR_REST_ANGLE * 1.15);
  sArm(ARM_ATTACK_ANGLE * step1);
  delay(random(1000, 2000));
  Serial.println((String) "angle=" + ARM_ATTACK_ANGLE * step1);

  for (float i = step1; i < step2; i += 0.01)
  {
    int r = random(1, 20);
    if (r > 18)
    {
      i -= 0.05;
    }
    sArm(ARM_ATTACK_ANGLE * i);
    delay(50);
    if (r > 15)
    {
      delay(1000 * i);
    }
  }
  delay(random(500, 1000));
  sArm(ARM_ATTACK_ANGLE);
  delay(200);
  sArm(ARM_REST_ANGLE);
  delay(300);
  sDoor(DOOR_REST_ANGLE);
  delay(300);
}