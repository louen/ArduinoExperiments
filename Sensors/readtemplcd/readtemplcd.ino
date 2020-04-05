#include <LiquidCrystal.h>
#include <stdio.h>

// ============================================================================
// Temperature resistor LM35  
// ============================================================================
// Wiring : GND  -> GND
//          VCC  -> 5V
//          Vout -> A0

const int TemperaturePin = A0;

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

}

// ============================================================================
void loop() {

    // Counter for blinking led
    static int iter = 0;

    // Buffer to print temperature
    static char TemperatureBuffer [] = "Temp: XX.XX\'C";

    // Output of the ADC (temperature read)
    int AnalogTemp;

    // Value of temperature in Celcius
    float Temperature;

    // ---------------------

    // Read adc pin
    AnalogTemp = analogRead(TemperaturePin);

    // Convert voltage to temp (10 bit adc from 0 to 5 volt by 0.01 volts increments)
    Temperature = float(AnalogTemp)/1023.f * 500;
    

    // Print float value in buffer
    dtostrf(Temperature, 5, 2, TemperatureBuffer + 6);
    // Remove the '\0' added by dtostrf
    TemperatureBuffer[11] = '\'';


    //Send data on serial port
    Serial.print(TemperatureBuffer);
    Serial.println();

    // Display data on LCD
    LCDScreen.setCursor(0,0);
    LCDScreen.print(TemperatureBuffer);

    // Blink
    ++iter;
    digitalWrite(LED_BUILTIN, iter % 2 ? HIGH : LOW);
    
    // Wait 1s
    delay(1000);

}
