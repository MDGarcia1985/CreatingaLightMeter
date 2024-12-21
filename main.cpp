#include <Arduino.h>

// Define Arduino pins independently
#define LED1_PIN 6  // PWM-capable pin for fading (PD6)
#define LED2_PIN 5  // PWM-capable pin for fading (PD5)
#define LED3_PIN 4  // Software PWM (PD4)
#define LED4_PIN 3  // Software PWM (PD3)
#define LED5_PIN 2  // Software PWM (PD2)
#define LED6_PIN 7  // Software PWM (PD7)
#define LEDB1_PIN 8 // Blinking LED (PB0)
#define LEDB2_PIN 9 // Blinking LED (PB1)
#define PHOTO_PIN A0 // Photoresistor input

// Variables for fading
int brightness = 0;         // Current brightness
unsigned long previousMillis = 0; // Timing for fading

// Variables for blinking
volatile bool blinkState = false; // State of blinking LED
unsigned long blinkPreviousMillis = 0; // Timing for blinking
const int blinkInterval = 1000;  // Blinking interval in milliseconds

// Variables for UART monitoring
int photoValue = 0;        // Holds the current photoresistor value
int minPhotoValue = 1023;  // Initialize to maximum ADC value
int maxPhotoValue = 0;     // Initialize to minimum ADC value

void setup() {
    // Set up pins as OUTPUT
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);
    pinMode(LED5_PIN, OUTPUT);
    pinMode(LED6_PIN, OUTPUT);
    pinMode(LEDB1_PIN, OUTPUT);
    pinMode(LEDB2_PIN, OUTPUT);

    // Set up the photoresistor pin
    pinMode(PHOTO_PIN, INPUT);

    // Set up Serial communication
    Serial.begin(9600);
    Serial.println("Photoresistor Test Started");

    // Set up timer interrupt for blinking LED
    cli(); // Disable global interrupts
    TCCR1A = 0; // Clear Timer/Counter Control Registers
    TCCR1B = 0;
    TCNT1 = 0;  // Initialize counter value
    OCR1A = 15624;  // Compare Match Register for 1 Hz
    TCCR1B |= (1 << WGM12); // CTC mode
    TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
    TIMSK1 |= (1 << OCIE1A); // Enable timer compare interrupt
    sei(); // Enable global interrupts
}

void loop() {
    // Handle fading LEDs
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= 30) {
        previousMillis = currentMillis;

        // Read photoresistor value and map to brightness range
        photoValue = analogRead(PHOTO_PIN);
        brightness = map(photoValue, 0, 1023, 0, 255);

        // Update min and max photoresistor values
        if (photoValue < minPhotoValue) {
            minPhotoValue = photoValue;
        }
        if (photoValue > maxPhotoValue) {
            maxPhotoValue = photoValue;
        }

        // Write brightness to LEDs
        analogWrite(LED1_PIN, brightness);
        analogWrite(LED2_PIN, brightness);

        // Software PWM for non-PWM pins
        softwarePWM(LED3_PIN, brightness);
        softwarePWM(LED4_PIN, brightness);
        softwarePWM(LED5_PIN, brightness);
        softwarePWM(LED6_PIN, brightness);

        // Print photoresistor value to Serial Monitor
        Serial.print("Current Value: ");
        Serial.print(photoValue);
        Serial.print(" | Min: ");
        Serial.print(minPhotoValue);
        Serial.print(" | Max: ");
        Serial.println(maxPhotoValue);
    }

    // Handle blinking LEDs in ISR
    if (blinkState) {
        digitalWrite(LEDB1_PIN, HIGH);
        digitalWrite(LEDB2_PIN, HIGH);
    } else {
        digitalWrite(LEDB1_PIN, LOW);
        digitalWrite(LEDB2_PIN, LOW);
    }
}

// Interrupt Service Routine for blinking LEDs
ISR(TIMER1_COMPA_vect) {
    blinkState = !blinkState; // Toggle blink state
}

// Software PWM function for non-PWM pins
void softwarePWM(int pin, int brightness) {
    for (int i = 0; i < 256; i++) {
        if (i < brightness) {
            digitalWrite(pin, HIGH);
        } else {
            digitalWrite(pin, LOW);
        }
    }
}
