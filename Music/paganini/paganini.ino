#include "pitches.h"

// Speaker
// 
// Wiring : Wire 1 -> GND
//          Wire 2 -> 100 Ohm Resistor -> Digital 8

const int SpeakerPin = 8;

struct Note {
    unsigned int pitch; // how high
    unsigned int value; // Duration (whole note, white note, quarter note, etc) 
    int dot; // Boolean : if 1 then put a dot on the note (stacatto)
};

// Nicolo Paganini, Caprice 24 Op. 1
Note PaganiniNotes1[] =
{
    {NOTE_A4, 8, 0},
    {NOTE_REST, 16, 0},
    {NOTE_A4, 16, 1},

    {NOTE_A4, 16, 0},
    {NOTE_C5, 16, 0},
    {NOTE_B4, 16, 0},
    {NOTE_A4, 16, 0},
    // --
    {NOTE_E5, 8, 0},
    {NOTE_REST, 16, 0},
    {NOTE_E4, 16, 1},

    {NOTE_E4, 16, 0},
    {NOTE_GS4, 16, 0},
    {NOTE_FS4, 16, 0},
    {NOTE_E4, 16, 0},
    //--
    {NOTE_A4, 8, 0},
    {NOTE_REST, 16, 0},
    {NOTE_A4, 16, 1},

    {NOTE_A4, 16, 0},
    {NOTE_C5, 16, 0},
    {NOTE_B4, 16, 0},
    {NOTE_A4, 16, 1},
    // --
    {NOTE_E5, 4,0},
    {NOTE_E4, 8,0},
    {NOTE_REST,8,0}
};

Note PaganiniNotes2[] =
{
    {NOTE_A5, 8, 0},
    {NOTE_REST, 16, 0},
    {NOTE_A5, 16, 1},

    {NOTE_A5, 16, 0},
    {NOTE_BB5, 16, 0},
    {NOTE_A5, 16, 0},
    {NOTE_G5, 16, 0},
    // --
    {NOTE_F5, 8, 0},
    {NOTE_REST, 16, 0},
    {NOTE_D5, 16, 1},

    {NOTE_D5, 16, 0},
    {NOTE_F5, 16, 0},
    {NOTE_E5, 16, 0},
    {NOTE_D5, 16, 0},
    //--
    {NOTE_G5, 8, 0},
    {NOTE_REST, 16, 0},
    {NOTE_G5, 16, 1},

    {NOTE_G5, 16, 0},
    {NOTE_A5, 16, 0},
    {NOTE_G5, 16, 0},
    {NOTE_F5, 16, 1},
    // --
    {NOTE_E5, 8, 0},
    {NOTE_REST, 16, 0},
    {NOTE_C5, 16, 1},

    {NOTE_C5, 16, 0},
    {NOTE_E5, 16, 0},
    {NOTE_D5, 16, 0},
    {NOTE_C5, 16, 0},
    // --
    {NOTE_F5, 8, 0},
    {NOTE_REST, 16, 0},
    {NOTE_B4, 16, 1},

    {NOTE_B4, 16, 0},
    {NOTE_D5, 16, 0},
    {NOTE_C5, 16, 0},
    {NOTE_B4, 16, 0},
    //--
    {NOTE_E5, 8, 0},
    {NOTE_REST, 16, 0},
    {NOTE_A4, 16, 1},

    {NOTE_A4, 16, 0},
    {NOTE_C5, 16, 0},
    {NOTE_B4, 16, 0},
    {NOTE_A4, 16, 0},
    //--
    {NOTE_F4, 8, 0},
    {NOTE_REST, 16, 0},
    {NOTE_DS5, 16, 1},

    {NOTE_E4, 16, 0},
    {NOTE_E5, 16, 0},
    {NOTE_D5, 16, 0},
    {NOTE_B4, 16, 0},
    //--
    {NOTE_A4,4,0},
    {NOTE_A3,8,0},
    {NOTE_REST,8,0}
};


#define NUM_NOTES(X) (sizeof(X) / sizeof(X[0]))

// Play a note at a given tempo in bpm
void playNote(Note note, unsigned int bpm)
{
    const unsigned int duration = 1500 / note.value;

    if ( note.pitch == NOTE_REST) {
        noTone(SpeakerPin);
        delay(duration);
    } 
    else { // Actual note being played

        if (note.dot == 0) { // Normal note (legato)
            tone(SpeakerPin, note.pitch, duration);
            delay(duration);
        } 
        else { // Play stacatto : remove a bit at the begining and end of note

            static const float Stacatto  = 0.05; // proportion removed bedore and after 
            
            const unsigned int restDuration = Stacatto * duration; // Removed duration
            const unsigned int noteDuration = duration - 2 * restDuration; // Leftover

            noTone(SpeakerPin);
            delay(restDuration);
            
            tone(SpeakerPin, note.pitch, noteDuration);
            delay(noteDuration);
            
            noTone(SpeakerPin);
            delay(restDuration);
        }
    }
}


void setup() {

    // Start serial port at 9600 Baud
    Serial.begin(9600);
    Serial.print("Serial initialized");
    Serial.println();

    // Enable onboard LED output
    pinMode(LED_BUILTIN, OUTPUT);  
}

void loop() {

    digitalWrite(LED_BUILTIN, HIGH);

    const unsigned int NumNotes1 = NUM_NOTES(PaganiniNotes1); 
    const unsigned int NumNotes2 = NUM_NOTES(PaganiniNotes2); 

    // Play sequence 1 twice
    for (unsigned int i = 0; i < NumNotes1; ++i) {
        playNote(PaganiniNotes1[i]);
    }
    for (unsigned int i = 0; i < NumNotes1; ++i) {
        playNote(PaganiniNotes1[i]);
    }

    // Play sequence 2
    for (unsigned int i = 0; i < NumNotes2; ++i) {
        playNote(PaganiniNotes2[i]);
    }

    digitalWrite(LED_BUILTIN,LOW);
    delay(2000);
}
