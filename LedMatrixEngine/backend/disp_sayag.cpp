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

void SayagLEDDisplayBackend::renderline(int linenb, int bitplane) {
    // TURN DISPLAY OFF
    digitalWriteFast( pin_enable, HIGH);

    // a line is made of 18 bytes
    for(int i=0; i < XMAX; i++) {
        if (virtualdisplay[bitplane][ XMAX - i - 1 ] & (1 << linenb)) {
            digitalWrite( pin_data, HIGH)
        } else {
            digitalWrite( pin_data, LOW)
        }
        clock_pulse();
    }
    // TURN DISPLAY ON
    digitalWrite(pin_enable, LOW);
}

void SayagLEDDisplayBackend::renderalllines(int delayms, int bitplane) {
    for(int i=0; i < YMAX ; i++) {  // a line is made of 18 bytes
        digitalWriteFast(pins[i], LOW);
        renderline( YMAX - i  , bitplane );
        digitalWriteFast(pins[i], HIGH);
        delayMicroseconds( delayms );

    }
}

// PUBLIC API

void SayagLEDDisplayBackend::set_bitplanes(uint8_t bp) {
    this->bitplanes = bp;
}

void SayagLEDDisplayBackend::set_refresh_delay(uint8_t d) {
    this->refresh_delay = d;
}

void SayagLEDDisplayBackend::begin() {
    // set the digital pin as output:
    pinMode(pin_enable, OUTPUT);
    pinMode(pin_clock,  OUTPUT);
    pinMode(pin_data,  OUTPUT);

    for(int i=0; i<8; i++) {
        pinMode(pin_data[i], OUTPUT);
    }
}


void SayagLEDDisplayBackend::clock_pulse(int udelay=0) {
    digitalWriteFast(pin_clock, HIGH);
    delayMicroseconds(udelay);
    digitalWriteFast(pin_clock, LOW);
    delayMicroseconds(udelay);
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

