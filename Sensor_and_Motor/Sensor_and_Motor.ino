#define enA 5
#define enB 6
#define inA1 9 //IN1
#define inA2 10 //IN2
#define inB1 7 //IN3
#define inB2 8 //IN4

const int trigLeft = A0;
const int trigRight = A2;
const int trigFront = A4;
const int echoLeft = A1;
const int echoRight = A3;
const int echoFront = A5;

long distanceLeft, distanceRight, distanceFront;

int pwmSignalA = 85;
int pwmSignalB = 100;
 
void get_distanceFront() {
	// put your main code here, to run repeatedly:
	// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
	digitalWrite(trigFront, LOW);
	delayMicroseconds(5);
	digitalWrite(trigFront, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigFront, LOW);

	// Read the signal from the sensor: a HIGH pulse whose
	// duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object.
	pinMode(echoFront, INPUT);
	long duration = pulseIn(echoFront, HIGH);

	// convert the time into a distance
	distanceFront = (duration/2) / 29.1;  
}

void get_distanceLeft() {
	digitalWrite(trigLeft, LOW);
	delayMicroseconds(5);
	digitalWrite(trigLeft, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigLeft, LOW);

	pinMode(echoLeft, INPUT);
	long duration = pulseIn(echoLeft, HIGH);

	distanceLeft = (duration/2) / 29.1; 
}

void get_distanceRight() {
	digitalWrite(trigRight, LOW);
	delayMicroseconds(5);
	digitalWrite(trigRight, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigRight, LOW);

	pinMode(echoRight, INPUT);
	long duration = pulseIn(echoRight, HIGH);

	distanceRight = (duration/2) / 29.1;  
}

void left() {
	analogWrite(enA, pwmSignalA); 
	analogWrite(enB, pwmSignalB);
	digitalWrite(inA1, LOW);
	digitalWrite(inA2, HIGH);
	digitalWrite(inB1, HIGH);
	digitalWrite(inB2, LOW);
}

void right() {
	analogWrite(enA, pwmSignalA);
	analogWrite(enB, pwmSignalB);
	digitalWrite(inA1, HIGH);
	digitalWrite(inA2, LOW);
	digitalWrite(inB1, LOW);
	digitalWrite(inB2, HIGH);
}

void forward() {
	analogWrite(enA, pwmSignalA);
	analogWrite(enB, pwmSignalB);

	digitalWrite(inA1, LOW);
	digitalWrite(inA2, HIGH);
	digitalWrite(inB1, LOW);
	digitalWrite(inB2, HIGH);
}

void stoop() {
	analogWrite(enA, 0);
	analogWrite(enB, 0);

	digitalWrite(inA1, LOW);
	digitalWrite(inA2, LOW);
	digitalWrite(inB1, LOW);
	digitalWrite(inB2, LOW);
}

void setup() {
	// put your setup code here, to run once:
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(inA1, OUTPUT);
	pinMode(inA2, OUTPUT);
	pinMode(inB1, OUTPUT);
	pinMode(inB2, OUTPUT);

	Serial.begin(9600);

	pinMode(trigLeft, OUTPUT);
	pinMode(echoLeft, INPUT);

	pinMode(trigFront, OUTPUT);
	pinMode(echoFront, INPUT);

	pinMode(trigRight, OUTPUT);
	pinMode(echoRight, INPUT);

}

char dist_empty() {
	int d = 9;
  int df = 10;
	if( distanceLeft > df )
	{
		return 'l';
	}
	if( distanceFront > d )
	{
		return 'f';
	}
  return 'r';
}

void loop() {
	// put your main code here, to run repeatedly:   
	get_distanceLeft();
	get_distanceFront();
	get_distanceRight();

	char cd = dist_empty();

	switch(cd)
	{ 
		case 'l':
		{ 
			left();
			delay(600);
			stoop();
			delay(100);
			break;
		}
		case 'r': 
		{
			right();
			delay(600);
			stoop();
			delay(100);
			break;
		}
		case 'f': 
		{
			forward();
			delay(300);
			stoop();
			delay(100);
			break;
		}
		default: stoop();
	}

/*  Serial.print("DF: ");
  Serial.println(distanceFront);

  delay(250);
  
  Serial.print("DR: ");
  Serial.println(distanceRight);
  
  delay(250);

  Serial.print("DL: ");
  Serial.println(distanceLeft);

  delay(250);
*/
	Serial.println(cd);
}
