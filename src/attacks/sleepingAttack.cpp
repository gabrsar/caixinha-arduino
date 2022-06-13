#include <Arduino.h>
#include "utils.h"
#include <Thread.h>

// data structure of the thread
typedef struct data_type
{
  String title;
  long pause;
} data_type;

// state structure of the thread
typedef struct state_type
{
  char stack[500];
  data_type data;
} state_type;

// static allocate the state variables
state_type state1, state2;

void pipipi(void)
{
  while (attacked())
  {
    for (int i = 0; i < 3; i++)
    {
      sDoor(DOOR_REST_ANGLE);
      delay(300);
      sDoor(DOOR_REST_ANGLE + 5);
      delay(100);
    }
    delay(500);
  }
}

void turnItOff(void){
  moveArmIf(&attacked,ARM_REST_ANGLE,ARM_ATTACK_ANGLE,4000);
  delay(500);
  sArm(ARM_REST_ANGLE);
}

void sleepingAttack()
{
  schedule();
  state1.data.title = "alarm clock";
  state1.data.pause = 500;
  spawn(&state1.data, &pipipi);

  state2.data.title = "arm";
  state2.data.pause = 510;
  spawn(&state2.data, &turnItOff);

  delay(1000);
}