#include <Arduino.h>
#include <avr/pgmspace.h>
#include <SoftwareSerial.h>

#define MIDI_BAUDRATE 31250
#define TICKS_PER_BEAT 4
#define TICK_INTERVAL_MS 125
#define MAX_ACTIVE_NOTES 16

#define CH_BASS   0  // Channel 1
#define CH_GUITAR 1  // Channel 2
#define CH_DRUMS  9  // Channel 10 (General MIDI drums)

#define BUTTON_PIN 2
bool lastButtonState = HIGH;

SoftwareSerial drumSerial(7, 255); // TX on pin 7, no RX

typedef struct {
    uint8_t note;
    uint8_t velocity;
    uint8_t channel;
    uint8_t time;
    uint8_t duration;
} MidiNote;

typedef struct {
    const MidiNote *notes;
    uint8_t noteCount;
} Pattern;

typedef struct {
    const Pattern * const *patterns;
    uint8_t patternCount;
} Block;

typedef struct {
    const Block * const *blocks;
    uint8_t blockCount;
} Song;

typedef struct {
    const Song * const *songs;
    uint8_t songCount;
} Set;

typedef struct {
    uint8_t note;
    uint8_t channel;
    uint32_t offTick;
    bool active;
} ActiveNote;

ActiveNote activeNotes[MAX_ACTIVE_NOTES];

// --- Pattern Data ---
const MidiNote drumNotes[] PROGMEM = {
    {36, 127, CH_DRUMS, 0, 2},
    {38, 100, CH_DRUMS, 4, 2},
    {36, 127, CH_DRUMS, 8, 2},
    {38, 100, CH_DRUMS, 12, 2},
};

const MidiNote bassNotes[] PROGMEM = {
    {40, 100, CH_BASS, 0, 4},
    {47, 100, CH_BASS, 8, 4},
};

const MidiNote guitarNotes[] PROGMEM = {
    {52, 100, CH_GUITAR, 2, 2},
    {52, 100, CH_GUITAR, 6, 2},
    {52, 100, CH_GUITAR, 10, 2},
    {52, 100, CH_GUITAR, 14, 2},
};

const Pattern drumPattern PROGMEM = { drumNotes, 4 };
const Pattern bassPattern PROGMEM = { bassNotes, 2 };
const Pattern guitarPattern PROGMEM = { guitarNotes, 4 };

const Pattern * const block_patterns[] PROGMEM = {
    &drumPattern,
    &bassPattern,
    &guitarPattern
};

const Block commonBlock PROGMEM = { block_patterns, 3 };

const Block * const song_blocks[] PROGMEM = {
    &commonBlock, &commonBlock, &commonBlock
};

const Song song_ImIntoCB PROGMEM = { song_blocks, 3 };
const Song song_JohnnyBeGoode PROGMEM = { song_blocks, 3 };
const Song song_EverybodyNeedsSomebody PROGMEM = { song_blocks, 3 };
const Song song_Roadrunner PROGMEM = { song_blocks, 3 };

const Song * const mySetSongs[] PROGMEM = {
    &song_ImIntoCB,
    &song_JohnnyBeGoode,
    &song_EverybodyNeedsSomebody,
    &song_Roadrunner
};

const Set mySet PROGMEM = { mySetSongs, 4 };
uint8_t currentSongIndex = 0;

// --- MIDI Output Routing ---
void sendMidiByte(uint8_t byte, uint8_t channel) {
    if (channel == CH_DRUMS) {
        drumSerial.write(byte);
    } else {
        Serial.write(byte);
    }
}

void sendMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    sendMidiByte(0x90 | (channel & 0x0F), channel);
    sendMidiByte(note, channel);
    sendMidiByte(velocity, channel);
}

void sendMidiNoteOff(uint8_t channel, uint8_t note) {
    sendMidiByte(0x80 | (channel & 0x0F), channel);
    sendMidiByte(note, channel);
    sendMidiByte(0, channel);
}

// --- Note Off Tracker ---
void scheduleNoteOff(uint8_t channel, uint8_t note, uint32_t offTick) {
    for (uint8_t i = 0; i < MAX_ACTIVE_NOTES; i++) {
        if (!activeNotes[i].active) {
            activeNotes[i] = {note, channel, offTick, true};
            break;
        }
    }
}

void processNoteOffs(uint32_t currentTick) {
    for (uint8_t i = 0; i < MAX_ACTIVE_NOTES; i++) {
        if (activeNotes[i].active && currentTick >= activeNotes[i].offTick) {
            sendMidiNoteOff(activeNotes[i].channel, activeNotes[i].note);
            activeNotes[i].active = false;
        }
    }
}

const Song* getCurrentSong() {
    return (const Song *)pgm_read_word(&mySet.songs[currentSongIndex]);
}

void playPattern(const Pattern *p, uint32_t tick) {
    Pattern pattern;
    memcpy_P(&pattern, p, sizeof(Pattern));

    for (uint8_t i = 0; i < pattern.noteCount; i++) {
        MidiNote note;
        memcpy_P(&note, &pattern.notes[i], sizeof(MidiNote));

        if (note.time == (tick % 16)) {
            sendMidiNoteOn(note.channel, note.note, note.velocity);
            scheduleNoteOff(note.channel, note.note, tick + note.duration);
        }
    }
}

void playSong(const Song *s, uint32_t tick) {
    Song songCopy;
    memcpy_P(&songCopy, s, sizeof(Song));

    uint8_t blockIndex = (tick / 16) % songCopy.blockCount;
    const Block *block = (const Block *)pgm_read_word(&songCopy.blocks[blockIndex]);

    Block blockCopy;
    memcpy_P(&blockCopy, block, sizeof(Block));

    for (uint8_t i = 0; i < blockCopy.patternCount; i++) {
        const Pattern *pattern = (const Pattern *)pgm_read_word(&blockCopy.patterns[i]);
        playPattern(pattern, tick);
    }
}

// --- Timing ---
uint32_t lastTickTime = 0;
uint32_t tickCount = 0;

void setup() {
    Serial.begin(MIDI_BAUDRATE);
    drumSerial.begin(MIDI_BAUDRATE);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    memset(activeNotes, 0, sizeof(activeNotes));
}

void loop() {
    uint32_t now = millis();

    // Handle song switch
    bool buttonState = digitalRead(BUTTON_PIN);
    if (buttonState == LOW && lastButtonState == HIGH) {
        currentSongIndex = (currentSongIndex + 1) % mySet.songCount;
    }
    lastButtonState = buttonState;

    // Timing tick
    if (now - lastTickTime >= TICK_INTERVAL_MS) {
        lastTickTime = now;
        processNoteOffs(tickCount);
        playSong(getCurrentSong(), tickCount);
        tickCount++;
    }
}