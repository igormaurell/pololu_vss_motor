#include <TimerOne.h>

#define PWM_M1 5
#define IN1_M1 3
#define IN2_M1 4
 
#define PWM_M2 6
#define IN1_M2 7
#define IN2_M2 8

#define ENC_M1_A A7 
#define ENC_M1_B A6

#define ENC_M2_A A5
#define ENC_M2_B A4

#define TIME 100000

double velocity_m1;
double velocity_m2;

void interruptFunction();
void velocityCalculate();

void setup() {
  // put your setup code here, to run once:

  Timer1.initialize(TIME);
  Timer1.attachInterrupt(interruptFunction);
}

void loop() {
  digitalWrite(IN1_M1, HIGH);
  digitalWrite(IN2_M1, LOW);
  analogWrite(PWM_M1, 120);
}

void velocityCalculate()
{
  
}

void interruptFunction()
{
  
}
