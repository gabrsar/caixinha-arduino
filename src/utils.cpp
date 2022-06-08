#include <Arduino.h>
#include <Servo.h>
#include "utils.h"

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
  delay(200);

  note(1);
  delay(500);

  note(3);
  delay(500);

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

void delayIfOff(int time)
{
  int steps = time / RACTION_DELAY_TIME;
  for (int i = 0; i < steps && !attacked(); i++)
  {
    delay(RACTION_DELAY_TIME);
  }
}

void slowCloseIfOff(int totalTime)
{
  int currentAngle = doorState();
  int dA = currentAngle - DOOR_REST_ANGLE;
  int steps = min(totalTime / MIN_SERVO_DELAY, dA);
  int dS = dA / steps;
  int angle = currentAngle;
  int usedDelay = totalTime / steps;

  Serial.println((String) "totalTime:" + totalTime + "; currentAngle:" + currentAngle + "; dA:" + dA + "; steps:" + steps + "; dS:" + dS + "; usedDelay:" + usedDelay);
  for (int s = 0; s < steps && !attacked(); s++)
  {
    angle = angle - dS;
    Serial.println(angle);
    sDoor(angle);
    delay(usedDelay);
  }
  sDoor(DOOR_REST_ANGLE);
}

void slowOpenDoorIfOn(int totalTime, int openAngle)
{
}
void slowRetractIfOff(int totalTime)
{
}
bool attacked()
{
  return digitalRead(PIN_SWITCH) == HIGH;
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