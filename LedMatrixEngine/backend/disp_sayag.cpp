/********************************************************************************************************************
 * DISPLAY VERT
 * 
 * Desciption : 
 * Panneau de marque SAYAG ELECTRONIC, modèle BG 18 de 1989
 * Dimension physiques approx : 2m * 20cm
 * 
 * longeur  : 18 * 8 = 144 pixels
 * largeur  : 7 pixels
 * 
 * Principe :
 * Le circuit principal d'injection est un registre a decalage (CD4094)
 * Ils sont daisy-chainés. Pas de Enable trouvé ...(pas besoin en fait)
 * 
 * Des ULN viennent récupérer les donnée et les injecter en X
 * En Y, on se rebranche en entrée des transistors BDW44 motorola
 * 
 * On utilise un principe de balayage X/Y :
 * Pour chaque ligne on itère ...
 * 1)on affiche les données en X en les serialisant sur le mode 
 * STROBE ENABLE
 * BITBANG SUR DATA
 * CLOCK PULSE
 * 2)on affiche allume la ligne courante ou les points s'allument
 * 
 * CD4094 attaqué sur le panneau : (dans l'ordre sur le panneau, les pad d'étain haut->bas)
 * STROBE -> 4
 * CLOCK  -> 3
 * DATA   -> 2
 * 
 * LIGNE AFFICHEUR (en haut d'abord) repiquées en entrée des transistor sur la carte
 * L0 -> 12
 * ...
 * L7 -> 6
 * 
 * Cablage arduino :
 * 2  DATA
 * 3  CLOCK
 * 4  STROBE
 * 5
 * 6  L6
 * 7  L5
 * 8  L4
 * 9  L3              (-) GND
 * 10 L2
 * 11 L1
 * 12 L0
 ********************************************************************************************************************/


#include "disp_sayag.h"

#include <Arduino.h>
#include <digitalWriteFast.h>

SayagLEDDisplayBackend::SayagLEDDisplayBackend(uint8_t e, uint8_t c, uint8_t de, const uint8_t data[7], uint8_t delay) :
    pin_enable(e),
    pin_clock(c),
    pin_data_enable(de),
    refresh_delay(delay)
{
    memcpy(pin_data, data, 7);
}

// setup
void SayagLEDDisplayBackend::begin() {
    // set the digital pin as output:
    pinMode(pin_enable, OUTPUT);
    pinMode(pin_clock,  OUTPUT);
    pinMode(pin_data_enable,  OUTPUT);

    for(int i=0; i<8; ++i) {
        pinMode(pin_data[i], OUTPUT);
    }
}

void SayagLEDDisplayBackend::clock_pulse(uint8_t udelay) const {
    digitalWriteFast(pin_clock, HIGH);
    delayMicroseconds(udelay);
    digitalWriteFast(pin_clock, LOW);
    delayMicroseconds(udelay);
}

void SayagLEDDisplayBackend::disable() const {
    // TURN DISPLAY OFF
    digitalWriteFast( pin_enable, HIGH);
}

void SayagLEDDisplayBackend::enable() const {
    // TURN DISPLAY ON
    digitalWrite(pin_enable, LOW);
}

// run
void SayagLEDDisplayBackend::render() const {
    uint8_t line = 0;
    disable();
    for (uint16_t i=0; i<get_size(); ++i) {
        if ((i%get_width()) == 0) {
            digitalWriteFast(pin_data[line], LOW);
        }
        for (uint8_t b=0; b<8; ++b) {
            if ((display_buffer[i]&b)==b)
                digitalWrite(pin_data_enable, HIGH);
            else
                digitalWrite(pin_data_enable, LOW);
        }
        clock_pulse(1);
        if ((i%get_width()) == 0) {
            digitalWriteFast(pin_data[line], HIGH);
            ++line;
        }
    }
    enable();
}

void SayagLEDDisplayBackend::update_buffer(const char* newbuf) {
    memcpy(display_buffer, newbuf, get_size());
}

void SayagLEDDisplayBackend::change_byte(uint8_t x, uint8_t y, uint8_t v) {
    display_buffer[ x + y * get_width()] = v;
}

#if 0
// #ifdef HORIZONTAL_DISPLAY

#include <digitalWriteFast.h>

// DRIVER pins 
#define DEFAULT_PIN_ENABLE  4
#define DEFAULT_PIN_CLOCK   3
#define DEFAULT_PIN_DATA    2

#define DEFAULT_DATA_PINS { 12,10,11,9,8,6,7 };

#include "disp_sayag.h"

////////////////////////////////////////////////////////////////////////////////////

// PRIVATE API


// PUBLIC API

void SayagLEDDisplayBackend::set_bitplanes(uint8_t bp) {
    this->bitplanes = bp;
}

void SayagLEDDisplayBackend::set_refresh_delay(uint8_t d) {
    this->refresh_delay = d;
}

void SayagLEDDisplayBackend::begin() {
}


void SayagLEDDisplayBackend::render() {
    render( this->refresh_delay );
}

void SayagLEDDisplayBackend::render(int udelay) {
    if( udelay ==0 )
        return;
    /*
       for(int i=0; i<= 4; i++){

       if(i>3)   render7linesPORTgrey( udelay, 0 );
       if(i>2)   render7linesPORTgrey( udelay, 1 );
       if(i>1)   render7linesPORTgrey( udelay, 2 );
       if(i>0)   render7linesPORTgrey( udelay, 3 );    
       if(i>0)   render7linesPORTgrey( udelay, 3 ); 
       }
       */
    /*
       renderalllines( udelay, 0 );
       renderalllines( udelay, 1 );
       renderalllines( udelay, 1 );
       renderalllines( udelay, 2 );
       renderalllines( udelay, 2 );
       renderalllines( udelay, 2 );
       renderalllines( udelay, 3 );    
       renderalllines( udelay, 3 ); 
       renderalllines( udelay, 3 ); 
       renderalllines( udelay, 3 );
       */

        renderalllines( udelay, 0 );
        renderalllines( 2*udelay, 1 );
        renderalllines( 5*udelay, 2 );
        renderalllines( 10*udelay, 3 );

        /*
           renderalllines( udelay, 0 );
           renderalllines( udelay, 1 );
           renderalllines( udelay, 2 );
           renderalllines( udelay, 3 );
           */
}

// XXX non API function…
void SayagLEDDisplayBackend::rendermono() {
    int udelay = 1500;
    renderalllines( udelay, 0 );
}

// XXX higher level function, to be removed
void SayagLEDDisplayBackend::testdisplay() {
    setvirtualdisplay( 0 );
    for(int i=0; i< 8; i++){
        blockvirtual(i + 8, 10, 0);
        blockvirtual(i + 32, 10, 1);
        blockvirtual(i + 64, 10, 2);
    }
    render();
}

#endif
