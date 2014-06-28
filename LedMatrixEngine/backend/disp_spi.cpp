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

#define REFRESH_DELAY_DEFAULT 3

// #if (defined MULTI_SEGMENT_DISPLAY_FULLSCREEN && defined OUTPUT_SPI)


// handle the display state machine
void SPILEDDisplayBackend::handleDisplay() {
        const int pause_delay=1;
        // disable interrupts
        noInterrupts();

        if (dispState == 0)
                render_all_lines( pause_delay, 0 );
        else if (bitplanes >=2 && dispState == 2)
                render_all_lines( pause_delay, 0 );
        else if (bitplanes >=3 && dispState == 5)
                render_all_lines( pause_delay, 0 );
        else if (bitplanes >=4 && dispState == 12)
                render_all_lines( pause_delay, 0 );
        }
        delayMicroseconds( pause_delay );

        if( dispState >= 19) {
            dispState = 0;
            //VBLANK = true;
        }
        else  {   
            dispState++;
            //VBLANK = false;
        }

        // reenable interrupts
        interrupts();
}

void SPILEDDisplayBackend::render_all_lines(int delayms, int bitplane) {  // non testé
    digitalWriteFast(pin_load, LOW); 
    for( int j=SEGMENTS_MINUS ; j >= 0 ; j-- ) {
        digitalWrite(pin_load, LOW);
        for( int i=XMAX_MINUS ; i >= 0 ; i-- ) {
            // shiftOut(pin_data, pin_clock, MSBFIRST, virtualdisplay[bitplane][i] ); 
            SPI.transfer( virtualdisplay[currfb_disp][j][bitplane][i] );
        }
    }
    digitalWriteFast(pin_load, HIGH);
    // WAIT FOR THE EYE TO SEE !
    //delayMicroseconds( delayms );
}

void SPILEDDisplayBackend::set_bitplanes(uint8_t bp) {
    this->bitplanes = bp;
}

void SPILEDDisplayBackend::set_refresh_delay(uint8_t d) {
    this->refresh_delay = d;
}

void SPILEDDisplayBackend::begin(bool fast=false) {
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
    Timer1.initialize(1200);
    Timer1.attachInterrupt(handleDisplay);

    // XXX WTF: pretty sure it has nothing to do at this level
    //currfb = 0;
    //currfb_disp = 1;
}

void SPILEDDisplayBackend::clock_pulse(int udelay=0) const {
    digitalWriteFast(pin_clock, HIGH);
    delayMicroseconds(udelay);
    digitalWriteFast(pin_clock, LOW);
    delayMicroseconds(udelay);
}

void SPILEDDisplayBackend::render() {
    render( refresh_delay, 1 );
}

// XXX why keep this if left unimplemented?
void SPILEDDisplayBackend::render(int PAUSE) {
    //render( PAUSE, 4);
    //render( PAUSE, 4);
    //render_all_lines(0, 9);
    //render_all_lines(0, BITPLANES);   // GOOD OR BUG ?
    //render_all_lines(0, BITPLANES-1); 

    //renderall();
}

// XXX WTF is the logic here?
void SPILEDDisplayBackend::render(int PAUSE, int option) {
    switch( option ) {
        case 1 : 
            {
                render_all_lines(   PAUSE, 0 );
                render_all_lines( 4*PAUSE, 1 );
                render_all_lines( 7*PAUSE, 2 );
                render_all_lines( 8*PAUSE, 3 ); 
                break;
            }
        case 2 : 
            {
                render_all_lines( PAUSE, 0 );
                render_all_lines( PAUSE, 1 );
                render_all_lines( PAUSE, 1 );
                render_all_lines( PAUSE, 2 );
                render_all_lines( PAUSE, 2 );
                render_all_lines( PAUSE, 2 );
                render_all_lines( PAUSE, 3 );    
                render_all_lines( PAUSE, 3 ); 
                render_all_lines( PAUSE, 3 ); 
                render_all_lines( PAUSE, 3 );
                break;
            }
        case 3 : 
            {
                render_all_lines(   PAUSE, 0 );
                render_all_lines( 3*PAUSE, 1 );
                render_all_lines( 8*PAUSE, 2 );
                render_all_lines( 17*PAUSE, 3 );
                break;
            }
        case 4 : 
            {
                render_all_lines(   PAUSE, 0 );
                render_all_lines( 2*PAUSE, 1 );
                render_all_lines( 4*PAUSE, 2 );
                render_all_lines( 8*PAUSE, 3 ); 
                break;
            }

        case 5 : 
            {
                render_all_lines( PAUSE, 3 ); 
                render_all_lines( PAUSE, 0 );
                render_all_lines( PAUSE, 3 ); 
                render_all_lines( PAUSE, 2 );
                render_all_lines( PAUSE, 3 ); 
                render_all_lines( PAUSE, 1 );
                render_all_lines( PAUSE, 3 ); 
                render_all_lines( PAUSE, 2 );
                render_all_lines( PAUSE, 3 ); 
                render_all_lines( PAUSE, 1 );
                render_all_lines( PAUSE, 3 ); 
                render_all_lines( PAUSE, 2 );
                render_all_lines( PAUSE, 3 ); 
                render_all_lines( PAUSE, 2 );
                render_all_lines( PAUSE, 3 ); 
                break;
            }
    }
}


#endif
