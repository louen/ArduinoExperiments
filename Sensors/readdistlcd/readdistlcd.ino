#include <LiquidCrystal.h>
#include <stdio.h>

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
// LCD screen in 4 bit mode
// ============================================================================
// Wiring : VSS -> GND
//          VDD -> 5V
//          V0  -> 10k potentiometer output for brightness control
//          RS  -> Digital 12
//          RW  -> NC
//          E   -> Digital 11
//          D0-3-> NC
//          D4  -> Digital 5
//          D5  -> Digital 4
//          D6  -> Digital 3
//          D7  -> Digital 2
//          A   -> 330 ohm resistor -> 5V
//          K   -> GND

const int LCDRsPin =  12;
const int LCDEPin  =  11;
const int LCD4Pin  =  5;
const int LCD5Pin  =  4;
const int LCD6Pin  =  3;
const int LCD7Pin  =  2;


LiquidCrystal  LCDScreen(LCDRsPin, LCDEPin, LCD4Pin, LCD5Pin, LCD6Pin, LCD7Pin);

// ============================================================================
void setup() {

    // Start serial port at 9600 Baud
    Serial.begin(9600);
    Serial.print("Serial initialized");
    Serial.println();

    // Start LCD
    LCDScreen.begin(16,2);
    LCDScreen.print("hello world");

    // Enable onboard LED output
    pinMode(LED_BUILTIN, OUTPUT);  

    // Activate ultrasound pins
    pinMode(EchoPin, INPUT);
    pinMode(TrigPin, OUTPUT);
}

// ============================================================================
void loop() {

    // Counter for blinking led
    static int iter = 0;

    // Buffer to print temperature
    static char DistBuffer [] = "XXXXXXXXXXXX";

    int PulseLength = 0; // in microseconds

    float Distance = 0.f; // in cm
    // ---------------------

    // Send a square signal to the trigger of the rangefinder
    digitalWrite(TrigPin, LOW);
    delayMicroseconds(20);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(TrigPin, LOW);

    // Wait for the reply
    PulseLength = pulseIn(EchoPin, HIGH);

    // The delay is the time it takes for sound to travel the distance twice
    Distance = DistFactor * PulseLength;

    // Print float value in buffer
    dtostrf(Distance, 6, 2, DistBuffer);
    // Remove the '\0' added by dtostrf
    DistBuffer[11] = ' ';


    //Send data on serial port
    Serial.print(Distance);
    Serial.println();
    Serial.print(DistBuffer);
    Serial.println();
    Serial.println();

    // Display data on LCD
    LCDScreen.setCursor(0,0);
    LCDScreen.print("Dist: ");
    LCDScreen.print(DistBuffer);
    LCDScreen.print(" cm");

    // Blink
    ++iter;
    digitalWrite(LED_BUILTIN, iter % 2 ? HIGH : LOW);
    
    // Wait 1s
    delay(1000);

}
