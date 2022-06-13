#include <Arduino.h>
#include "utils.h"

static int RAGE = 1;

void laugh()
{
  // I couldn't contain my emotions muahaha
  sDoor(DOOR_REST_ANGLE * 0.3); // ha
  delay(200);
  sDoor(DOOR_REST_ANGLE * 0.9); // ha
  delay(300);
  sDoor(DOOR_REST_ANGLE * 0.5); // ha
  delay(1500);
}

void letThemThinkTheyWinAttack()
{
  Serial.println("Let them Think they Win!");

  delay(1000);

  if (random(1, 10) > 8)
  {
    laugh();
  }

  sDoor(DOOR_ATTACK_ANGLE);
  sArm(ARM_ATTACK_ANGLE * 0.85);
  delay(random(500, 800));
  sArm(ARM_REST_ANGLE);
  sDoor(DOOR_REST_ANGLE);

  int foolTime;
  while (true)
  {
    // WTF, random is generating negative numbers. Some shit must be happening.
    foolTime = random(30, 60) * 1000;
    Serial.println((String) "foolTime:" + foolTime);
    if (foolTime > 0)
    {
      break;
    }
  }
  delayIfOn(foolTime);
  delay(500);
  if (attacked())
  {
    laugh();
    if (attacked())
    {
      sDoor(DOOR_ATTACK_ANGLE);
      sArm(ARM_ATTACK_ANGLE);
      delay(500);
      sArm(ARM_REST_ANGLE);
      sDoor(DOOR_REST_ANGLE);
    }

  }
  delay(500);
  laugh();
}