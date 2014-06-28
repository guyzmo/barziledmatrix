#ifndef _DISP_SPI_H_
#define _DISP_SPI_H_

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

#include "backend.h"

#include <SPI.h>
#include <digitalWriteFast.h>

// #if (defined MULTI_SEGMENT_DISPLAY_FULLSCREEN && defined OUTPUT_SPI)

class SPILEDDisplayBackend : Backend {
    uint8_t pin_load;
    uint8_t pin_clock;
    uint8_t pin_data;

    uint8_t bitplanes=0;
    uint8_t refresh_delay=REFRESH_DELAY_DEFAULT;

    uint8_t dispState=0;

    void handleDisplay();
    void render_all_lines(int delayms, int bitplane);
    public:
        SPILEDDisplayBackend(uint8_t l, uint8_t c, uint8_t d) :
            pin_load(l), pin_clock(c), pin_data(d) { }

        void set_bitplanes(uint8_t bp);
        void set_refresh_delay(uint8_t d);

        void begin(bool fast=false);
        void clock_pulse(int udelay=0) const;
        void render();
        void render(int PAUSE, int option);
};

#endif
