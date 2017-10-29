/* simple-dmx library by André Hanak <impressum@a-hanak.de> */

#pragma once

#include "Particle.h"

/**
 * Send DMX frames using a mix of UART and GPIO.
 *
 * Don't use this library for professional applications as it might not work properly.
 *
 * Only the particle library functions are used.
 * The library might not work properly if the timer callback is interrupted.
 *
 * Timings and frame structure is taken from http://mc.mikrocontroller.com/de/dmx512.php
 *
 * @example simple usage
 *   SimpleDmx dmx;
 *
 *   void setup() {
 *     dmx.start();
 *
 *     // If RGB Lamp is connected to DMX channels 1-3, make it violet
 *     dmx.setChannel(0, 255); // red channel
 *     dmx.setChannel(2, 100); // blue channel
 *   }
 *
 */
class SimpleDmx {
public:
    /**
     * Create a new DMX instance for the given serial instance.
     * @param serial is the serial object used, default is the serial on the board (Serial1).
     * @param tx_pin is the TX-pin of the serial interface.
     * @param period is the time in milliseconds between two packet starts. Fastest possible value is not determined, spec allows up to 1250ms.
     */
    SimpleDmx(USARTSerial& serial = Serial1, uint16_t tx_pin = TX, unsigned int period = 40);

    /** Start transmitting packets periodically. */
    void start();

    /**
     * Set the value of a single dmx channel.
     * @param channel is the number of the dmx channel starting at 0. The value must be lower than what #getChannelCount returns.
     * @param value is the value for that channel between 0 and 255.
     */
    void setChannel(size_t channel, uint8_t value);

    /** Set all channels to zero. */
    void clear();

    /** @return the number of available dmx channels. */
    size_t getChannelCount();

    /**
     * Read the value of the specified dmx channel.
     * @param channel is the number of the dmx channel starting at 0. The value must be lower than what #getChannelCount returns.
     * @return the dmx value of that channel.
     */
    uint8_t readChannel(size_t channel);


private:
    /** The number of DMX channels to send in a packet. */
    static const size_t CHANNEL_COUNT = 512;

    /** The boudrate for the dmx bytes to be transmitted */
    static const unsigned long BAUD_RATE = 250000;

    /**
     * The minimum time in microseconds of the break (also called reset) with LOW output.
     * Higher values might result in better compatibility.
     *
     * As we are using possible slow library functions, the break will actually be longer.
     * This should not be a problem, because the spec allows breaks up to 1 second.
     */
    static const unsigned int DURATION_BREAK_MIN = 88;

    /**
     * The minimum time in microseconds of a MARK with HIGH output.
     *
     * As we are using possible slow library functions, the mark will actually be longer.
     * This should not be a problem, because the spec allows a duration up to 1 second.
     * SPEC: 8 microseconds up to 1 second allowed.
     */
    static const unsigned int DURATION_MARK_MIN = 8;

    /** The buffer of the channel values. */
    uint8_t channels[CHANNEL_COUNT];

    /** The hardware serial that is used. */
    USARTSerial& serial;

    /** The tx pin of the serial used. */
    uint16_t tx_pin;

    /** The timer that triggers paket transmission. */
    Timer sendPacketTimer;

    /** Called by the Timer to send a dmx packet with the values stored in channels.  */
    void sendPacket();
};
