#include <Arduino.h>
#include <Servo.h>
#include <utils.h>

#include <attacks/lookAndAttack.h>

void setup()
{
  Serial.begin(9600);

  setupServos();
  setupSwitch();

}

void loop()
{
  delay(200);
  if(attacked()){
    lookAndAttack();
  }
}
