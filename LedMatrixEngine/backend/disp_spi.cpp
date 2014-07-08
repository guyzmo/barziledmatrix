/********************************************************************************************************************
 * DISPLAY VERT MULTISEGMENTS (9) FULLSCREEN SPI (experimental)
 * GREEN DISPLAY
 *
 * height: 9*7 = 64 pixels
 * width: 2*48 = 96 pixels
 * 
 * pins :
 * clock  -> 4
 * d      -> 5
 * data   -> 6
 *
 * pin_load    6   RED <- WHITE <- Slave Select
 * pin_clock   5   WHITE <- BLUE <- SCK
 * pin_data    4   BLACK <- YELLOW <- MOSI
 *                 RED "flexible" <- GND
 
 * SPI Wiring of the arduino MEGA :
  ---------------------------------
 
 * ICSP : 
    3 -> clock (blue)
    5 -> data  (white)
 
        (1) O O
    clk --  O O -- data
            O O
 
 * Digital pin 6 :
    -> load   (grey)
 
 
 ********************************************************************************************************************/

#include "disp_spi.h"

#include <SPI.h>
#include <digitalWriteFast.h>

#include <Arduino.h>

// handle the display state machine

SPILEDDisplayBackend::SPILEDDisplayBackend(uint8_t l, uint8_t c, uint8_t d, uint8_t delay) :
                                            pin_load(l), 
                                            pin_clock(c),
                                            pin_data(d),
                                            refresh_delay(delay)
{ 
    memset(display_buffer, 0, sizeof(display_buffer));
}

void SPILEDDisplayBackend::begin() {
    begin(false);
}
void SPILEDDisplayBackend::begin(bool fast) {
    pinModeFast(pin_clock, OUTPUT);
    pinModeFast(pin_data, OUTPUT);
    pinModeFast(pin_load, OUTPUT);
    // MODE1 is active on LOW (CPOL) and 
    // trigger on rising edge (CPHA)
    SPI.setDataMode(SPI_MODE1);
    if (fast) {
        SPI.setClockDivider(SPI_CLOCK_DIV2);
    }
    SPI.begin();
}

void SPILEDDisplayBackend::clock_pulse(uint8_t udelay) const {
    digitalWriteFast(pin_clock, HIGH);
    delayMicroseconds(udelay);
    digitalWriteFast(pin_clock, LOW);
    delayMicroseconds(udelay);
}

void SPILEDDisplayBackend::render() const {
    cli();
    digitalWriteFast(pin_load, LOW); 
    for (uint16_t i=0; i<get_size(); ++i) {
        // shiftOut(pin_data, pin_clock, MSBFIRST, virtualdisplay[bitplane][i] ); 
        SPI.transfer( display_buffer[i]);
        clock_pulse(1);
    }
    digitalWriteFast(pin_load, HIGH);
    sei();
}

void SPILEDDisplayBackend::update_buffer(const char* newbuf) {
    memcpy(display_buffer, newbuf, get_size());
}

void SPILEDDisplayBackend::change_byte(uint8_t x, uint8_t y, uint8_t v) {
    display_buffer[ x + y * get_width()] = v;
}
