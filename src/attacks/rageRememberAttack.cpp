#include <Arduino.h>
#include "utils.h"

#define BASE_DELAY 3000
#define MIN_DELAY 100

static float RAGE = 1.0;

int rageTime()
{
  return max(BASE_DELAY / (1+RAGE), MIN_DELAY);
}

void rageRememberAttack()
{
  while (RAGE > 0)
  {
    if (attacked())
    {
      Serial.print("+");
      RAGE ++;
      sDoor(DOOR_ATTACK_ANGLE);
      sArm(ARM_ATTACK_ANGLE);
      delay(rageTime());
      slowRetractIfOff(rageTime());
      slowCloseIfOff(rageTime());
    }
    else{
      Serial.print("-");
      RAGE -= 0.1;
    }
    delay(rageTime());
  }
}