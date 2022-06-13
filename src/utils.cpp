#include <Arduino.h>
#include <Servo.h>
#include "utils.h"

typedef unsigned long ulong;

Servo S_ARM;
Servo S_DOOR;

void setupSwitch()
{
  pinMode(PIN_SWITCH, INPUT);
}

Servo setupServos()
{
  S_ARM.attach(PIN_ARM);
  S_DOOR.attach(PIN_DOOR);

  sArm(ARM_REST_ANGLE);
  sDoor(DOOR_REST_ANGLE);
}

void note(int intensity)
{
  int hitDoor = 53;
  int rest = hitDoor - 6;
  sArm(hitDoor + intensity);
  delay(50);
  sArm(rest);
}

void tatatatataTaTa()
{
  delay(1000);

  note(2);
  delay(400);

  note(1);
  delay(150);

  note(1);
  delay(100);

  note(1);
  delay(150);

  note(2);
  delay(500);

  note(3);
  delay(200);

  note(3);
}

void randomRant()
{
  int words = random(1, 5);

  for (int w = 0; w < words; w++)
  {
    int phonemes = random(1, 10);
    for (int p = 0; p < phonemes; p++)
    {
      sDoor(random(0, DOOR_REST_ANGLE));
      delay(random(50, 100));
    }
    delay(random(100, 300));
  }

  delay(400);
}

void delayIfOn(int timeLenght)
{
  int steps = timeLenght / RACTION_DELAY_TIME;
  for (int i = 0; i < steps && attacked(); i++)
  {
    delay(RACTION_DELAY_TIME);
  }
}

void delayIfOff(int timeLenght)
{
  int steps = timeLenght / RACTION_DELAY_TIME;
  for (int i = 0; i < steps && !attacked(); i++)
  {
    delay(RACTION_DELAY_TIME);
  }
}

void slowCloseIfOff(int totalTime)
{
  Serial.print('FECHA SA PORRA');
  if (totalTime > 200)
  {
    int currentAngle = doorState();
    int dA = currentAngle - DOOR_REST_ANGLE;
    int usedDelay = (totalTime / dA);
    int left = dA;
    Serial.println((String) "ANGULO PORTA:" + (currentAngle) + " delay=" + usedDelay + " dA=" + dA);

    for (int s = 0; s < dA && !attacked(); s++, left--)
    {
      Serial.println((String) "ANGULO PORTA:" + (currentAngle - s));
      sDoor(currentAngle - s);
      delay(usedDelay);
    }
    Serial.println(left);
    if (left == 0)
    {
      sDoor(DOOR_REST_ANGLE);
    }
  }
  else
  {
    sDoor(DOOR_REST_ANGLE);
  }
}

void slowOpenDoorIfOn(int totalTime)
{
  if (totalTime > 200)
  {
    int currentAngle = doorState();
    int dA = DOOR_ATTACK_ANGLE - currentAngle;
    int usedDelay = (totalTime / dA);
    int left = dA;
    for (int s = 0; s < dA && attacked(); s++, left--)
    {
      Serial.println(currentAngle + s);
      sDoor(currentAngle + s);
      delay(usedDelay);
    }
    Serial.println(left);
    if (left == 0)
    {
      sDoor(DOOR_ATTACK_ANGLE);
    }
  }
  else
  {
    sDoor(DOOR_ATTACK_ANGLE);
  }
}

void forceOff(int waitTime){
  ulong endTime = millis()+waitTime;
  while(millis() < endTime){
    if(attacked()){
      sArm(ARM_ATTACK_ANGLE*0.8);
      delay(200);
      sArm(ARM_ATTACK_ANGLE);
      delay(200);
    }
  }
}

void moveArmIf(bool (*conditionPtr)(), int startAngle, int finalAngle, int duration)
{
  moveIf(conditionPtr, S_ARM, startAngle, finalAngle, duration);
}
void moveDoorIf(bool (*conditionPtr)(), int startAngle, int finalAngle, int duration)
{
  moveIf(conditionPtr, S_DOOR, startAngle, finalAngle, duration);
}

void moveIf(bool (*conditionPtr)(), Servo s, int startAngle, int finalAngle, int duration)
{
  bool shouldMove = (*conditionPtr)();
  if (!shouldMove)
  {
    return;
  }

  int totalDeltaAngle = finalAngle - startAngle;
  int currentAngle = s.read();
  int waitPerMove = max(duration / abs(totalDeltaAngle), 1);
  int signalToMove = finalAngle > startAngle ? 1 : -1;

  for (; currentAngle != (finalAngle + signalToMove) && (*conditionPtr)(); currentAngle += signalToMove)
  {

    s.write(currentAngle);
    delay(waitPerMove);
  }
}

void slowRetractIfOff(int totalTime)
{
  if (totalTime > 200)
  {
    int currentAngle = armState();
    int dA = currentAngle - ARM_REST_ANGLE;
    int usedDelay = (totalTime / dA);
    int left = dA;
    for (int s = 0; s > dA && !attacked(); s--, left--)
    {
      sArm(currentAngle + s);
      delay(usedDelay);
    }
    Serial.println(left);
    if (left == 0)
    {
      sArm(ARM_REST_ANGLE);
    }
  }
  else
  {
    sArm(ARM_REST_ANGLE);
  }
}

bool attacked()
{
  return digitalRead(PIN_SWITCH) == HIGH;
}

bool isOff()
{
  return !attacked();
}

int armState()
{
  return S_ARM.read();
}
int doorState()
{
  return S_DOOR.read();
}
void sArm(int angle)
{
  S_ARM.write(angle);
}
void sDoor(int angle)
{
  S_DOOR.write(angle);
}