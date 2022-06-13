#include <Servo.h>

#define PIN_SWITCH 8
#define PIN_ARM 9
#define PIN_DOOR 10

#define DOOR_REST_ANGLE 95
#define DOOR_ATTACK_ANGLE 130
#define DOOR_MAX_ATTACK_ANGLE 180
#define ARM_REST_ANGLE 0
#define ARM_ATTACK_ANGLE 105
#define ARM_LOOKING_ANGLE 55

#define RACTION_DELAY_TIME 10
#define MIN_SERVO_DELAY 20

Servo setupServos();
void setupSwitch();

void randomRant();
void delayIfOff(int time);
void delayIfOn(int time);

void slowCloseIfOff(int totalTime);

void slowOpenDoorIfOn(int totalTime);
void slowRetractIfOff(int totalTime);
bool attacked();
bool isOff();

void forceOff(int waitTime);
int armState();
int doorState();
void sArm(int angle);
void sDoor(int angle);

void tatatatataTaTa();

void note();
void moveIf(bool (*conditionPtr)(), Servo s, int startAngle, int finalAngle, int duration);
void moveArmIf(bool (*conditionPtr)(), int startAngle, int finalAngle, int duration);
void moveDoorIf(bool (*conditionPtr)(), int startAngle, int finalAngle, int duration);