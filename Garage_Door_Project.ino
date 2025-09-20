#include <Servo.h>  // Library for controlling servo motors

// Variables for ultrasonic sensor readings
long duration;       // Time taken for ultrasonic pulse to return
float distanceCM;      // Calculated distance in cm
float distanceM;      // Calculated distance in m


// Pin definitions
const int trigPin = 10;   // Trigger pin for ultrasonic sensor
const int echoPin = 11;   // Echo pin for ultrasonic sensor
const int ServoPin = 12;  // Signal pin for servo motor
const int ledPin = 9;     // LED pin

// Create a servo object
Servo myServo;  

void setup() {
  // Configure ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  

  // Configure LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Start with LED off

  // Initialize serial communication
  Serial.begin(9600);     

  // Attach the servo to the defined pin
  myServo.attach(ServoPin); 
  
  // Start servo at 0° (garage closed)
  myServo.write(0);        
}

void loop() {
  // Ensure trigger pin starts LOW (clean signal)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send a 10 microsecond HIGH pulse to trigger ultrasonic burst
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure duration of the echo pulse in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Convert duration to distance (cm)
  distanceCM = duration * 0.034 / 2;
  distanceM = distanceCM/100;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distanceCM);
  Serial.println("CM |");
  Serial.print(distanceM);
  Serial.println(" M");

  // Garage only reacts if object is between 5 cm and 30 cm
if (distanceCM >= 5 && distanceCM <= 20) {
  // Slowly open servo
  for (int pos = 0; pos <= 100; pos++) {
    myServo.write(pos);
    delay(20);  // Adjust speed (higher = slower)
  }

  digitalWrite(ledPin, HIGH); // Turn LED ON
  delay(6000);                // Keep open + LED ON for 6 seconds

  // Slowly close servo
  for (int pos = 100; pos >= 0; pos--) {
    myServo.write(pos);
    delay(20);  // Adjust speed
  }

  digitalWrite(ledPin, LOW);  // Turn LED OFF
}



  delay(500); // Small delay for stability
}