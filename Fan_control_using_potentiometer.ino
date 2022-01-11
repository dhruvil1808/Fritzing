// Motor controller connections
int enA = 5;
int in1 = 6;
int in2 = 4;

//Potentiometer connections
int pot = A0; // assigns analog input A0 to variable pot
int c1 = 0;   // declares variable c1

//ultrasonic Sensor connections
#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

void setup()
{
    // Set all the motor control pins to outputs
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    //set the potentiometer pin as input
    pinMode(pot, INPUT);
    //set Trig as output and echo as input
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    //set all pins 7-13 as output for 7 segment display
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    //set all the pins 7-13 as Low initially
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
}

void loop()
{
    int duration, distance;
    // Output pulse with 1ms width on trigPin
    digitalWrite(trigPin, HIGH);
    delay(1);
    digitalWrite(trigPin, LOW);
    // Measure the pulse input in echo pin
    duration = pulseIn(echoPin, HIGH);
    // Distance is half the duration devided by 29.1 (from datasheet)
    distance = (duration / 2) / 29.1;
    // if distance less than 0.2 meter and more than 0
    if (distance <= 50 && distance >= 0)
    {
        Serial.println("Obstacle Detected!!! Remove It");
    }
    else
    {
        directionControl();
    }
}

// This function lets you control spinning direction of motor and
void directionControl()
{
    c1 = analogRead(pot);
    //display speed as per the potentiometer input
    display(c1);
    //set speed of motor as per the potentiometer input
    analogWrite(enA, c1);
    // Turn on the motor
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(2000);

    // Now change motor direction
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(2000);

    // Turn off the motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
}

void display(int c1)
{
    //to display 1
    if (c1 < 500)
    {
        digitalWrite(7, LOW);
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
    }
    //to display 2
    else if (c1 >= 500 && c1 < 1000)
    {
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
    }
    //to display 3
    else
    {
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
    }
}
