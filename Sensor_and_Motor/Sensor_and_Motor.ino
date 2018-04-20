#include<NewPing.h>

#define enA 5
#define enB 6
#define inA1 9 //IN1
#define inA2 10 //IN2
#define inB1 7 //IN3
#define inB2 8 //IN4

//TO DO :
//1- Refactor Motor functions
//2- Refactor dist-empty function
//3- check main loop 

const int trigLeft = A0;
const int trigRight = A2;
const int trigFront = A4;
const int echoLeft = A1;
const int echoRight = A3;
const int echoFront = A5;

//Motor pwm
int pwmOutput1 = 150;
int pwmOutput2 = 150;

int distanceLeft = 0;
int distanceRight = 0;
int distanceFront = 0;
 
NewPing sonarLeft(trigLeft, echoLeft, 100);
NewPing sonarRight(trigRight, echoRight, 100);
NewPing sonarFront(trigFront, echoFront, 100);

// 0: left, 1: right, 2: front
int getDistance(int code)
{
  int numOfIterations =0, sensorReadings[3], idx=0, distance=0;
  
  while(idx<3 && numOfIterations<=6){
      numOfIterations++;
    
     if(code == 0)
        distance = sonarLeft.ping_cm();
     else if(code == 1)
        distance = sonarRight.ping_cm();
     else
        distance = sonarFront.ping_cm(); 
        
     delayMicroseconds(2);
     if(distance<4) continue;
     sensorReadings[idx++] = distance;
  }

  for(int i=0;i<idx;i++){
    for(int j=i+1;j<idx;j++){
      if(abs(sensorReadings[i]-sensorReadings[j])<2){
        distance = (sensorReadings[i] + sensorReadings[j])/2;
      }
    }
  }

  return distance;
}

void left(void) {
  analogWrite(enA, 180); //speed 0 - 255
  analogWrite(enB, 180); //speed 0 - 255
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
}

void right(void) {
  analogWrite(enA, 180); //speed 0 - 255
  analogWrite(enB, 180); //speed 0 - 255
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
}

void forward(void) {
  analogWrite(enA, 254); //speed 0 - 255
  analogWrite(enB, 255); //speed 0 - 255
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
}
/*
void stoop()
{
  digitalWrite(brake2,HIGH);
  digitalWrite(d1,LOW);
  digitalWrite(d2,LOW);
  digitalWrite(brake1,HIGH);
  digitalWrite(op1,LOW);
  digitalWrite(op2,LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
*/
void setup() {
  // put your setup code here, to run once:
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(inA1, OUTPUT);
    pinMode(inA2, OUTPUT);
    pinMode(inB1, OUTPUT);
    pinMode(inB2, OUTPUT);
   
    // Set initial rotation direction
    digitalWrite(inA1, LOW);
    digitalWrite(inA2, HIGH);

    digitalWrite(inB1, LOW);
    digitalWrite(inB2, HIGH);
    
    Serial.begin(9600);
}

char dist_empty()
{
  td=18;
  if(dis1<td&&dis1!=0)
  {
    if(dis2>td||dis2==0)
    return 'l';
    else if(dis3>td||dis3==0)
    return 'r';
    else
    return 's';
  }
  return 'f';
}

void loop() {
  // put your main code here, to run repeatedly:   
    distanceLeft = getDistance(0);
    distanceRight = getDistance(1);
    distanceFront = getDistance(2);

    char cd='f';
    cd= dist_empty();
    switch(cd)
    { 
      case 'l':
      { 
        left();
        delay(420);
        stoop();
        delay(100);
        break;
      }
      case 'r': 
      {
        right();
        delay(420);
        stoop();
        delay(100);
        break;
      }
      case 'f': 
      {
        forward();
        delay(150);
        stoop();
        delay(100);
        break;
      }
      default: stoop();
    }
    
    Serial.println(cd);
    delay(100);
}
