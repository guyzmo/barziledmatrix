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

#define SCREEN_HEIGHT 96 // pixels
#define SCREEN_WIDTH 64 // pixels

#define BUFFER_SIZE SCREEN_WIDTH*SCREEN_HEIGHT/8

class SPILEDDisplayBackend : public LedDisplayBackend {
    uint8_t pin_load;
    uint8_t pin_clock;
    uint8_t pin_data;

    uint8_t bitplanes;
    uint8_t refresh_delay;

    bool fast;

    uint8_t display_buffer[BUFFER_SIZE];

    void clock_pulse(uint8_t udelay=0) const;
    void disable() const;
    void enable() const;

    public:
        SPILEDDisplayBackend(uint8_t l, uint8_t c, uint8_t d, uint8_t delay);

        // setup
        void begin();
        void begin(bool fast);

        // run
        void render() const;

        // getters
        uint8_t get_width() const {
            return SCREEN_WIDTH;
        }
        uint8_t get_height() const {
            return SCREEN_HEIGHT;
        }
        uint16_t get_size() const {
            return BUFFER_SIZE;
        }

        // operations
        void update_buffer(const char* buffer);
        void change_byte(uint8_t x, uint8_t y, uint8_t v);
};

#undef SCREEN_HEIGHT
#undef SCREEN_WIDTH
#undef BUFFER_SIZE

#endif
