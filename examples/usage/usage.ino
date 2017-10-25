// Example usage for SimpleDmx library by André Hanak <impressum@a-hanak.de>.

#include "SimpleDmx.h"

// Initialize objects from the lib
SimpleDmx simpleDmx;

void setup() {
    // Call functions on initialized library objects that require hardware
    simpleDmx.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    simpleDmx.process();
}
