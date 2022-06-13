#include <Arduino.h>
#include <Servo.h>
#include <utils.h>

#include <attacks/lookAndAttack.h>
#include <attacks/letThemThinkTheyWinAttack.h>
#include <attacks/quickAttack.h>
#include <attacks/rageRememberAttack.h>
#include <attacks/atatataTack.h>

#define TESTING false

typedef void (*func_attack)(void);

func_attack attackFunctions[] = {
    &lookAndAttack,
    &letThemThinkTheyWinAttack,
    &rageRememberAttack,
    &quickAttack,
    &atatataTack,
    NULL};

int attackTypesCont = 0;

void setAttackTypeCount()
{
  for (attackTypesCont = 0; attackFunctions[attackTypesCont]; attackTypesCont++)
    ;
}

void setup()
{
  Serial.begin(9600);

  setupServos();
  setupSwitch();
  setAttackTypeCount();
}

void loop()
{
  delay(50);
  if (attacked())
  {
    if (TESTING)
    {
      // Put your attack here
      lookAndAttack();
      return;
    }

    int attackType = random(0, attackTypesCont);
    attackFunctions[attackType]();
  }
}
