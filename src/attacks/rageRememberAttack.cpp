#include <Arduino.h>
#include "utils.h"

#define BASE_DELAY 500
#define DELAY_INCR 100

static float RAGE = 1.0;
float SUPER_RAGE_TRIGGER = 5;
static float SUPER_RAGE = 0;

void rageRememberAttack()
{
  Serial.println("Oh you son of a ... You again?");

  RAGE = 1;
  while (RAGE > 0)
  {
    Serial.println((String) "RAGE:" + RAGE);
    if (attacked())
    {
      if (RAGE < SUPER_RAGE_TRIGGER)
      {
        RAGE++;
      }
      else
      {
        SUPER_RAGE++;
      }

      int lookAngle = ARM_LOOKING_ANGLE + min(RAGE, 35);

      sDoor(DOOR_ATTACK_ANGLE);
      delay(max(200 - RAGE * 2, 1));

      if (SUPER_RAGE > 0 && SUPER_RAGE < 5)
      {
        delay(1000);
        for (int i = 0; i < SUPER_RAGE * 5; i++)
        {
          sArm(ARM_LOOKING_ANGLE + random(-2, 2));
          delay(random(5, 100));
        }
        delay(500);
      }
      else if (SUPER_RAGE >= 6)
      {
        int baseAngle = ARM_LOOKING_ANGLE + random(-10, 10);
        sArm(baseAngle);
        delay(1000);
        moveArmIf(&attacked, baseAngle, ARM_ATTACK_ANGLE * 0.85, 2000);
        sArm(ARM_ATTACK_ANGLE);
        forceOff(3000 + SUPER_RAGE*500);
      }
      else if (SUPER_RAGE >= 5)
      {
        sArm(ARM_LOOKING_ANGLE + random(-10, 10));
        delay(100);
        sArm(ARM_ATTACK_ANGLE);
        delay(1000);

        for (int i = 0; i < SUPER_RAGE; i++)
        {
          sArm(ARM_LOOKING_ANGLE + random(-10, 10));
          delay(100);
          sArm(ARM_ATTACK_ANGLE);
          delay(500);
        }
      }
      sArm(ARM_ATTACK_ANGLE);
      delay(400);

      sArm(lookAngle);

      delayIfOff(random(BASE_DELAY, BASE_DELAY + DELAY_INCR * (RAGE + SUPER_RAGE)));

      moveArmIf(&isOff, lookAngle, ARM_REST_ANGLE, random(BASE_DELAY / RAGE, BASE_DELAY + DELAY_INCR * (RAGE + SUPER_RAGE)));
      moveDoorIf(&isOff, DOOR_ATTACK_ANGLE, DOOR_REST_ANGLE, random(BASE_DELAY / RAGE, BASE_DELAY));
    }
    else
    {
      if (SUPER_RAGE > 0)
      {
        SUPER_RAGE -= 1;
      }
      if (RAGE > 0)
      {
        delay(100);
        RAGE -= 0.1;
      }
    }
  }
}