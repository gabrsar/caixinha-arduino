#include <Arduino.h>
#include "utils.h"

void ta(int n)
{
  sDoor(DOOR_MAX_ATTACK_ANGLE - n * 5);
  delay(300 + 50 * n);
  if(n==5){
      sArm(ARM_ATTACK_ANGLE);
  }
  sDoor(DOOR_ATTACK_ANGLE);
  
  delay(500);
}

void atatataTack()
{
  Serial.println("atatataTack! Professor Linguiça!");

  sDoor(DOOR_ATTACK_ANGLE);
  delay(1000);
  moveArmIf(&attacked, ARM_REST_ANGLE, ARM_LOOKING_ANGLE, 1000);

  ta(1);
  ta(2);
  ta(3);
  ta(4);
  ta(5);

  sArm(ARM_REST_ANGLE);
  delay(500);
  sDoor(DOOR_REST_ANGLE);

  delay(1000);

  Serial.println("O senhor não gostaria de entrar para tomar uma chícara de café?");
}