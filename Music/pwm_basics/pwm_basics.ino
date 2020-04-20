const int SpeakerPwmPin1 = 3;
const int SpeakerPwmPin2 = 5;

void setup() {
    pinMode(SpeakerPwmPin1, OUTPUT);
    pinMode(SpeakerPwmPin2, OUTPUT);

    // Play 490 Hz square wave
    tone(SpeakerPwmPin1,490, 1000);
    delay(2000);

    // Play 980 Hz square wave
    tone(SpeakerPwmPin2, 980, 1000);
    delay(2000);

    // Play pwm 490 Hz square vave
    analogWrite(SpeakerPwmPin1, 127);
    delay(1000);
    analogWrite(SpeakerPwmPin1, 0);

    delay(1000);
    
    analogWrite(SpeakerPwmPin2, 127);
    delay(1000);
    analogWrite(SpeakerPwmPin2, 0);

    delay(1000);

    analogWrite(SpeakerPwmPin1, 127);
    analogWrite(SpeakerPwmPin2, 127);
    delay(1000);


    analogWrite(SpeakerPwmPin1, 0);
    analogWrite(SpeakerPwmPin2, 0);


}

void loop() {
}

