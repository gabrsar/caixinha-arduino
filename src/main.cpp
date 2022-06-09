#include <Arduino.h>
#include <Servo.h>
#include <utils.h>

#include <attacks/lookAndAttack.h>
#include <attacks/letThemThinkTheyWinAttack.h>

#include <attacks/rageRememberAttack.h>

void setup()
{
  Serial.begin(9600);

  setupServos();
  setupSwitch();

}

void loop()
{
  delay(100);
  if(attacked()){
    rageRememberAttack();
  }
}
