#include <Arduino.h>

#include <Servo.h>

#define PIN_SWITCH 8
#define PIN_ARM 9
#define PIN_DOOR 10

#define DOOR_REST_ANGLE 95
#define DOOR_ATTACK_ANGLE 130
#define ARM_REST_ANGLE 0
#define ARM_ATTACK_ANGLE 120
#define REST_WAIT_TIME 2000

int debugVar = 0;

int defaultWaitTime = 100;
int rageLevel = 0;
int waitTime = defaultWaitTime;

int currentSwitchState = -1;
int lastSwitchState = -1;
bool running = false;

Servo sArm;
Servo sDoor;

void setup()
{
  pinMode(PIN_SWITCH, INPUT);
  sArm.attach(PIN_ARM);
  sDoor.attach(PIN_DOOR);
  Serial.begin(9600);

  sArm.write(ARM_REST_ANGLE);
  sDoor.write(DOOR_REST_ANGLE);
}

void randomRant()
{
  int shouldRant = random(0, 100) > 85;

  if (shouldRant)
  {
    delay(1500);

    int rantLenght = random(1, 5) * random(1, 5);

    for (int i = 0; i < rantLenght && digitalRead(PIN_SWITCH) == HIGH; i++)
    {
      delay(random(10, 500));
      sDoor.write(random(10, 95));
    }
    delay(1500);
  }
}

void attackCalmly()
{
  int armSpeed = random(1, 20);
  int doorSpeed = random(1, 10);
  randomRant();
  for (int i = DOOR_REST_ANGLE; i < DOOR_ATTACK_ANGLE; i += doorSpeed)
  {
    sDoor.write(i);
    delay(20);
  }
  sDoor.write(DOOR_ATTACK_ANGLE);

  delay(500);

  int endWalkAngle = ARM_ATTACK_ANGLE * 0.7;

  int rageCount = 0;

  while (digitalRead(PIN_SWITCH) == HIGH)
  {

    armSpeed = random(1 * min(rageCount + 1, 20), 30);

    for (int i = rageCount > 0 ? ARM_REST_ANGLE : endWalkAngle * 0.8; i < endWalkAngle; i += armSpeed)
    {
      sArm.write(i);
      delay(20);
    }

    if(random(1,20)>18){
      delay(random(1000,2000));
      sArm.write(ARM_ATTACK_ANGLE*0.7);
      delay(100);
    }

    sArm.write(ARM_ATTACK_ANGLE);
    delay(200);
    sArm.write(endWalkAngle);

    delay(random(100, 1000));
  }
  for (int i = endWalkAngle; i >= ARM_REST_ANGLE; i -= armSpeed)
  {
    sArm.write(i);
    delay(20);
  }
  sArm.write(ARM_REST_ANGLE);
  doorSpeed = random(3, 20);

  for (int i = DOOR_ATTACK_ANGLE; i >= DOOR_REST_ANGLE; i -= doorSpeed)
  {
    sDoor.write(i);
    delay(20);
  }
  sDoor.write(DOOR_REST_ANGLE);
  randomRant();

  bool shouldCheckAgain = random(1, 20) > 18;
  if (shouldCheckAgain)
  {
    delay(random(500, 1000));

    sDoor.write(DOOR_ATTACK_ANGLE * 0.8);
    delay(random(1000, 200));
    sDoor.write(DOOR_REST_ANGLE);
  }

  running = false;
}

void attackQuickly()
{
  sDoor.write(DOOR_REST_ANGLE);
  sArm.write(ARM_REST_ANGLE);
  delay(500);
  sDoor.write(DOOR_ATTACK_ANGLE);
  sArm.write(ARM_ATTACK_ANGLE);
  delay(500);
}

void loop()
{

  int switchState = digitalRead(PIN_SWITCH);

  Serial.println((String) "SWITCH=" + switchState + "; DOOR=" + sDoor.read() + "; ARM=" + sArm.read());

  if (switchState == HIGH && !running)
  {
    attackCalmly();
  }

  delay(waitTime);
}
