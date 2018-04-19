#define enA 5
#define enB 6
#define inA1 9
#define inA2 10
#define inB1 7
#define inB2 8

void setup() {
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
}

void loop() {
    int pwmOutput = 150;
    analogWrite(enA, pwmOutput); // Send PWM signal to L298N Enable pin
    analogWrite(enB, pwmOutput); // Send PWM signal to L298N Enable pin
}
