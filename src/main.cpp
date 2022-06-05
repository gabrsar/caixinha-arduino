#include <Arduino.h>

#include <Servo.h>

#define PIN_SWITCH 8
#define PIN_SERVO_SWITCH 9
#define PIN_SERVO_DOOR 10

#define SERVO_DOOR_REST_ANGLE 0
#define SERVO_DOOR_ATTACK_ANGLE 165
#define SERVO_SWITCH_REST_ANGLE 0
#define SERVO_SWITCH_ATTACK_ANGLE 120
#define REST_WAIT_TIME 2000

int defaultWaitTime = 100;
int rageLevel = 0;
int waitTime = defaultWaitTime;

Servo servoSwitch;
Servo servoDoor;

void setup()
{
  pinMode(PIN_SWITCH, INPUT);
  servoSwitch.attach(PIN_SERVO_SWITCH);
  servoDoor.attach(PIN_SERVO_DOOR);
  Serial.begin(9600);
}

void attackDefault()
{
  servoDoor.write(SERVO_DOOR_ATTACK_ANGLE);
  servoSwitch.write(SERVO_SWITCH_ATTACK_ANGLE);
}

void restDefault()
{
  servoSwitch.write(SERVO_SWITCH_REST_ANGLE);
  servoDoor.write(SERVO_DOOR_REST_ANGLE);
}

void loop()
{

  int switchState = digitalRead(PIN_SWITCH);
  Serial.println((String) "switchState=" + switchState + " , servoDoorState=" + servoDoor.read() + ", servoSwitchState=" + servoSwitch.read());
  if (switchState == HIGH){
    attackDefault();
  }else{
    restDefault();
  }

  delay(waitTime);
}