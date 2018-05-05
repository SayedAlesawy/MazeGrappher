
const int trigLeft = A0;
const int trigRight = A2;
const int trigFront = A4;
const int echoLeft = A1;
const int echoRight = A3;
const int echoFront = A5;

long distanceLeft, distanceRight, distanceFront;

void setup() {
	// put your setup code here, to run once:
	Serial.begin (9600);

	pinMode(trigLeft, OUTPUT);
	pinMode(echoLeft, INPUT);

	pinMode(trigFront, OUTPUT);
	pinMode(echoFront, INPUT);

	pinMode(trigRight, OUTPUT);
	pinMode(echoRight, INPUT);
}

void get_distanceFront(){
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

void get_distanceLeft(){
	digitalWrite(trigLeft, LOW);
	delayMicroseconds(5);
	digitalWrite(trigLeft, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigLeft, LOW);

	pinMode(echoLeft, INPUT);
	long duration = pulseIn(echoLeft, HIGH);

	distanceLeft = (duration/2) / 29.1;	
}

void get_distanceRight(){
	digitalWrite(trigRight, LOW);
	delayMicroseconds(5);
	digitalWrite(trigRight, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigRight, LOW);

	pinMode(echoRight, INPUT);
	long duration = pulseIn(echoRight, HIGH);

	distanceRight = (duration/2) / 29.1;	
}

void loop() {
	
	get_distanceLeft();
	get_distanceFront();
	get_distanceRight();

	Serial.print("DF: ");
	Serial.println(distanceFront);

	delay(250);

	Serial.print("DR: ");
	Serial.println(distanceRight);

	delay(250);

	Serial.print("DL: ");
	Serial.println(distanceLeft);

	delay(250);
}