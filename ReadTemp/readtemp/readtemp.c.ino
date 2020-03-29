

// Wiring : GND -> LM35-GND
//          5V  -> LM35-VCC
//          A0  -> LM35-Vout

int TemperaturePin = A0;

void setup() {
    // Start serial port at 9600 Baud
    Serial.begin(9600);
  
    Serial.print("Serial initialized");
}

void loop() {
    int AnalogTemp;
    float Temperature;

    // Read adc pin
    AnalogTemp = analogRead(TemperaturePin);

    // Convert voltage to temp (10 bit adc from 0 to 5 volt by 0.01 volts increments)
    Temperature = float(AnalogTemp)/1023.f * 500;
    
    //Send data on serial port

    Serial.print("Temp: ");
    Serial.print(Temperature);
    Serial.print("C");
    Serial.println();

    // Wait 1s
    delay(1000);

}
