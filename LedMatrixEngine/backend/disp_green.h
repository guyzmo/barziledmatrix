#ifndef _DISP_GREEN_H_
#define _DISP_GREEN_H_

/********************************************************************************************************************
 * DISPLAY VERT MULTISEGMENTS (9)
 * 
 * longeur  : 2 * 48 = 96 pixels
 * largeur  : 9 * 7 pixels
 * 
 * pins :
 * clock  -> 4
 * d      -> 5
 * data   -> 6
 * 
 * #TODO ##### ## Mapping de ports arduino :
 * #--------------------------
 * #PORTD maps to Arduino digital pins 0 to 7
 * #PORTD - The Port D Data Register - read/write
 * #
 * #PORTB maps to Arduino digital pins 8 to 13 The two high bits (6 & 7) map to the crystal pins and are not usable
 * #PORTB - The Port B Data Register - read/write
 * 
 * #PORTD = B10101000; // sets digital pins 7,5,3 HIGH
 ********************************************************************************************************************/

#define DEFAULT_PIN_LOAD    6
#define DEFAULT_PIN_CLOCK   5
#define DEFAULT_PIN_DATA    4

#include "backend.h"

#define SCREEN_HEIGHT 144 // pixels
#define SCREEN_WIDTH 64 // pixels

#define BUFFER_SIZE SCREEN_WIDTH*SCREEN_HEIGHT/8

class GreenLEDDisplayBackend : public LedDisplayBackend {
    uint8_t pin_enable;
    uint8_t pin_clock;
    uint8_t pin_data;

    uint8_t refresh_delay;

    uint8_t display_buffer[BUFFER_SIZE];

    void clock_pulse(uint8_t udelay=0) const;
    void disable() const;
    void enable() const;

    public:
        GreenLEDDisplayBackend(uint8_t e, uint8_t c, uint8_t d, uint8_t delay);

        // setup
        void begin();

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
