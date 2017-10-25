// Example usage for SimpleDmx library by André Hanak <impressum@a-hanak.de>.
// This program shows a rainbow on a connected dmx device.

#include "SimpleDmx.h"

SimpleDmx dmx;

// Define the DMX-Channels to use
const uint8_t CHANNEL_RED = 0;
const uint8_t CHANNEL_GREEN = 1;
const uint8_t CHANNEL_BLUE = 2;
const uint8_t CHANNEL_MASTER = 6;


void setup() {
    // Set master channel to on
    dmx.setChannel(CHANNEL_MASTER,255);

    // start the dmx output
    dmx.start();
}

void loop() {
    delay(100);

    // draw the next rainbow step
    rainbow();
}

void rainbow() {
    // initialize cur_step one time (static variable)
    static float cur_step = 0.0f;

    // increment cur_step value
    cur_step += 0.01;
    if(cur_step > 3.0f) {
        cur_step = 0.0f;
    }

    if (cur_step < 1.0f){
        // red -> green
        float partial = cur_step;
        dmx.setChannel(CHANNEL_RED, (1-partial)*255);
        dmx.setChannel(CHANNEL_GREEN, (partial)*255);
        dmx.setChannel(CHANNEL_BLUE, 0);
    } else if(cur_step < 2.0f) {
        // green -> blue
        float partial = cur_step - 1.0f;
        dmx.setChannel(CHANNEL_RED, 0);
        dmx.setChannel(CHANNEL_GREEN, (1-partial)*255);
        dmx.setChannel(CHANNEL_BLUE, (partial)*255);
    } else {
        // blue -> red
        float partial = cur_step - 2.0f;
        dmx.setChannel(CHANNEL_RED, (partial)*255);
        dmx.setChannel(CHANNEL_GREEN, 0);
        dmx.setChannel(CHANNEL_BLUE, (1-partial)*255);
    }
}