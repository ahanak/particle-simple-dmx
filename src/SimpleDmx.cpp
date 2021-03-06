#include "SimpleDmx.h"

SimpleDmx::SimpleDmx(USARTSerial& serial, uint16_t tx_pin, unsigned int period)
        : channels(), serial(serial), tx_pin(tx_pin), sendPacketTimer(period, &SimpleDmx::sendPacket, *this) {
    pinMode(D0, OUTPUT);
}

void SimpleDmx::start() {
    serial.begin(BAUD_RATE, SERIAL_8N2);
    sendPacketTimer.start();
}

void SimpleDmx::setChannel(size_t channel, uint8_t value) {
    if(channel < CHANNEL_COUNT) {
        channels[channel] = value;
    }
}

void SimpleDmx::clear() {
    for(size_t i = 0; i < CHANNEL_COUNT; i++) {
        channels[i] = 0;
    }
}

size_t SimpleDmx::getChannelCount() {
    return CHANNEL_COUNT;
}

uint8_t SimpleDmx::readChannel(size_t channel) {
    return (channel < CHANNEL_COUNT ? channels[channel] : 0);
}

/* --- Private methods below --- */

void SimpleDmx::sendPacket() {
    // Using the high level functions serial.begin(), serial.end() and pinMode() costs extra CPU time but works.

    // BREAK/RESET: LOW
    serial.end();
    pinMode(TX, OUTPUT);
    digitalWriteFast(TX, LOW);
    delayMicroseconds(DURATION_BREAK_MIN);

    // MARK: HIGH
    serial.begin(BAUD_RATE, SERIAL_8N2); // this will pull the pin up
    delayMicroseconds(DURATION_MARK_MIN);

    // Start Byte
    serial.write(0);

    // DATA
    for(size_t i = 0; i < CHANNEL_COUNT; i++) {
        serial.write(channels[i]);
    }

    // Pause
}