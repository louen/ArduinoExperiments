#include "pitches.h"

#define MAX_PITCH NOTE_C6
#define MIN_PITCH NOTE_C3

// ============================================================================
// Ultrasonic sensor 
// ============================================================================
// Wiring : GND  -> GND
//          VCC  -> 5V
//          Trig -> Digital 6
//          Echo -> Digital 7
const int TrigPin = 6;
const int EchoPin = 7;

// Multiplicating factor for microsecond delay to centimeters distance
const float DistFactor = 0.0170145f; // = speed of sound / 1.000.000 x2


// ============================================================================
// Speaker
// ============================================================================
// Wiring : GND  -> GND
//          VCC  -> 100 ohm resistor -> Digital 8

const int SpeakerPin = 8;



void setup() {
    // Start serial port at 9600 Baud
    Serial.begin(9600);
    Serial.print("Serial initialized");
    Serial.println();

    // Enable onboard LED output
    pinMode(LED_BUILTIN, OUTPUT);  

    // Activate ultrasound pins    
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);


}

void loop() {
    // put your main code here, to run repeatedly:

    int pulseLength = 0 ; // microseconds
    float distance = 0.0f; // cm;

    // Send a square signal to the trigger of the rangefinder
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(20);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(TrigPin, LOW);

    pulseLength = pulseIn(EchoPin, HIGH);


    distance = DistFactor * pulseLength;
    Serial.print(distance);

    const float maxDist = 100;
    const float maxDistTolerance = 1.1*maxDist;
    const float minDist = 3;

    if (distance > maxDistTolerance) {
        noTone(SpeakerPin);
    }
    else {
        distance = min(max(minDist,distance),maxDist);
        const float factor = (MAX_PITCH - MIN_PITCH) * (maxDist * minDist) / (maxDist - minDist);
        const float offset = (MIN_PITCH * maxDist - MAX_PITCH * minDist)/ (maxDist - minDist);

        unsigned int pitch = (unsigned int) ( factor / distance + offset );  

        tone(SpeakerPin, pitch);
    }
}
