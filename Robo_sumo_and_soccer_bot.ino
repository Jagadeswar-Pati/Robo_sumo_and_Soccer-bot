// Define BTS7960 Motor Driver Pins for Left Side
#define RPWM1 14 // D5 - Left Motor Forward
#define LPWM1 12 // D6 - Left Motor Reverse
#define REN1  13 // D7 - Enable Left Motor
#define LEN1  15 // D8 - Enable Left Motor

// Define BTS7960 Motor Driver Pins for Right Side
#define RPWM2 5  // D1 - Right Motor Forward
#define LPWM2 4  // D2 - Right Motor Reverse
#define REN2  16 // D0 - Enable Right Motor
#define LEN2  1  // TX - Enable Right Motor

// Define FlySky Receiver Pins
#define CH3 0  // D3 - Left Side Control
#define CH4 2  // D4 - Right Side Control

void setup() {
    // Set Motor Driver Pins as Outputs
    pinMode(RPWM1, OUTPUT);
    pinMode(LPWM1, OUTPUT);
    pinMode(REN1, OUTPUT);
    pinMode(LEN1, OUTPUT);

    pinMode(RPWM2, OUTPUT);
    pinMode(LPWM2, OUTPUT);
    pinMode(REN2, OUTPUT);
    pinMode(LEN2, OUTPUT);

    // Set FlySky Receiver Pins as Inputs
    pinMode(CH3, INPUT);
    pinMode(CH4, INPUT);

    // Enable both motor drivers
    digitalWrite(REN1, HIGH);
    digitalWrite(LEN1, HIGH);
    digitalWrite(REN2, HIGH);
    digitalWrite(LEN2, HIGH);

    Serial.begin(115200);
}

void loop() {
    // Read PWM signals from FlySky receiver
    int leftInput = pulseIn(CH3, HIGH); // Read CH3 (Left Side)
    int rightInput = pulseIn(CH4, HIGH); // Read CH4 (Right Side)

    // Convert PWM range (1000-2000µs) to (-255 to 255)
    int leftMotorSpeed = map(leftInput, 1000, 2000, -255, 255);
    int rightMotorSpeed = map(rightInput, 1000, 2000, -255, 255);

    // Constrain values within the valid PWM range
    leftMotorSpeed = constrain(leftMotorSpeed, -255, 255);
    rightMotorSpeed = constrain(rightMotorSpeed, -255, 255);

    // Control left motor independently (REVERSED)
    if (leftMotorSpeed > 0) {
        analogWrite(RPWM1, 0);  // Reverse direction
        analogWrite(LPWM1, leftMotorSpeed);
    } else {
        analogWrite(RPWM1, -leftMotorSpeed);
        analogWrite(LPWM1, 0);
    }

    // Control right motor independently (UNCHANGED)
    if (rightMotorSpeed > 0) {
        analogWrite(RPWM2, rightMotorSpeed);
        analogWrite(LPWM2, 0);
    } else {
        analogWrite(RPWM2, 0);
        analogWrite(LPWM2, -rightMotorSpeed);
    }

    // Print values for debugging (remove if using TX pin)
    Serial.print("Left Speed: "); Serial.print(leftMotorSpeed);
    Serial.print(" Right Speed: "); Serial.println(rightMotorSpeed);

    delay(20); // Small delay to improve signal stability
}
