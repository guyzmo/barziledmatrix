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

//#ifdef VERTICAL_DISPLAY
//#if (defined MULTI_SEGMENT_DISPLAY)

// DRIVER  1 pins 
#define DEFAULT_PIN_LOAD    6
#define DEFAULT_PIN_CLOCK   5
#define DEFAULT_PIN_DATA    4

#include "backend.h"

class GreenLEDDisplayBackend : Backend {
    uint8_t pin_enable;
    uint8_t pin_clock;
    uint8_t pin_data;

    uint8_t bitplanes=0;
    uint8_t refresh_delay=REFRESH_DELAY_DEFAULT;

    uint8_t dispState=0;

    void render_all_lines(int delayms, int bitplane);
    public:
        static const int XMAX = 144;
        static const int YMAX = 7;
        static const int DMAXSIZE = 144;
        static const int REFRESH_DELAY_DEFAULT 20;

        GreenLEDDisplayBackend(uint8_t e, uint8_t c, uint8_t d) : pin_enable(e),
                                                                  pin_clock(c),
                                                                  pin_data(d) { }

        void set_bitplanes(uint8_t bp);
        void set_refresh_delay(uint8_t d);

        void begin(bool fast=false);
        void clock_pulse(int udelay=0) const;
        void render();
        void render(int udelay, int option);

        // XXX not in the others
        void render(int udelay);

        // XXX higher level function, to be removed
        testdisplay();
};

#endif
