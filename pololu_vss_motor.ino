#include <TimerOne.h>

#define PWM_M1 5
#define IN1_M1 9
#define IN2_M1 4
 
#define PWM_M2 6
#define IN1_M2 7
#define IN2_M2 8

#define ENC_M1_A 3 
#define ENC_M1_B 2

#define ENC_M2_A A5
#define ENC_M2_B A4

#define TIME 10000

float ROT_RATIO = 12*51.45;

double velocity_m1;
int state_enc_m1;
int last_state_enc_m1;
int count_pulses_m1;
int last_count_pulses_m1;
int rotation_sense_m1;

double velocity_m2;

long long last_time;

int pulses_m1;

void velocityCalculate();
void interruptFunction();


void setup() {
  pinMode(ENC_M1_A, INPUT);
  pinMode(ENC_M1_B, INPUT);
  pinMode(ENC_M2_A, INPUT);
  pinMode(ENC_M2_B, INPUT);

  Timer1.initialize(TIME);
  Timer1.attachInterrupt(interruptFunction);
  Serial.begin(9600);

  last_time = millis();

  last_state_enc_m1 = (digitalRead(ENC_M1_A) << 1) | digitalRead(ENC_M1_B);

  attachInterrupt(digitalPinToInterrupt(ENC_M1_A), doEncM1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_M1_B), doEncM1, CHANGE);
  
}

void doEncM1()
{
  state_enc_m1 = (digitalRead(ENC_M1_A)<<1) | digitalRead(ENC_M1_B);

  switch(state_enc_m1) {
    case 0:
      if(last_state_enc_m1 == 1) count_pulses_m1++;
      else count_pulses_m1--;
    break;
    case 1:
      if(last_state_enc_m1 == 3) count_pulses_m1++;
      else count_pulses_m1--;
    break;
    case 3:
      if(last_state_enc_m1 == 2) count_pulses_m1++;
      else count_pulses_m1--;
    break;
    case 2:
      if(last_state_enc_m1 == 0) count_pulses_m1++;
      else count_pulses_m1--;
    break;
  }
  last_state_enc_m1 = state_enc_m1;
}

void loop() {
  if(millis() - last_time >= 2000){
    digitalWrite(IN1_M1, HIGH);
    digitalWrite(IN2_M1, LOW);
    analogWrite(PWM_M1, 150);
  }

  Serial.println(velocity_m1);
}

void velocityCalculate()
{
  int pulses_m1 = count_pulses_m1 - last_count_pulses_m1;

  velocity_m1 = ((pulses_m1/ROT_RATIO) * 2*PI)/(TIME/1000000.0);

  last_count_pulses_m1 = count_pulses_m1;
  
}

void interruptFunction()
{
  velocityCalculate();
}
