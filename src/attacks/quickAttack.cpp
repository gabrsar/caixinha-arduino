#include <Arduino.h>
#include "utils.h"

void quickAttack(){
  int angleSpread = 20;
  int doorAngle = random(DOOR_ATTACK_ANGLE-angleSpread/2, DOOR_MAX_ATTACK_ANGLE+angleSpread/2);
  sDoor(doorAngle);
  sArm(ARM_ATTACK_ANGLE);
  delay(600);
  sArm(ARM_REST_ANGLE);
  delay(200);
  sDoor(DOOR_REST_ANGLE);
  delay(300);
}