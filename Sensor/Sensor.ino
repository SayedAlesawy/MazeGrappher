#include<NewPing.h>

const int trigLeft = A0;
const int trigRight = A2;
const int trigFront = A4;
const int echoLeft = A1;
const int echoRight = A3;
const int echoFront = A5;

 
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

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int distanceLeft = getDistance(0);
  int distanceRight = getDistance(1);
  int distanceFront = getDistance(2);

  Serial.print("DF: ");
  Serial.println(distanceFront);

  delay(1000);
  
  Serial.print("DR: ");
  Serial.println(distanceRight);
  
  delay(1000);

  Serial.print("DL: ");
  Serial.println(distanceLeft);

  delay(1000);
  
}

