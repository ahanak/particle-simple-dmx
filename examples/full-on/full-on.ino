// Example usage for SimpleDmx library by André Hanak <impressum@a-hanak.de>.
// This sets all DMX channels to full on

#include "SimpleDmx.h"

// Initialize driver object
SimpleDmx simpleDmx;

void setup() {
    // start the dmx output
    simpleDmx.start();

    // Turn all channels full on
    for(size_t channel = 0; channel < simpleDmx.getChannelCount(); channel++) {
        simpleDmx.setChannel(channel, 255);
    }
}

void loop() {
    // nothing to do here - dmx output is done with timers
}
