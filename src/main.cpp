#include <Arduino.h>
#include <Servo.h>
#include <utils.h>

void setup()
{
  Serial.begin(9600);

  setupServos();
  setupSwitch();

}

void loop()
{
  delay(1000);

  if(attacked()){
    sDoor(DOOR_MAX_ATTACK_ANGLE);
  }else{
    slowCloseIfOff(1000);
  }

}
