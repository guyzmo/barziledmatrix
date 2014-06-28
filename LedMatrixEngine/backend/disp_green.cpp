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

#include "disp_green.h"

// PRIVATE API

void GreenLEDDisplayBackend::render_all_lines(int delayms, int bitplane) {
/* XXX What was it for?
    byte seg = virtualdisplay[bitplane][i];
     for(int j=7; j>=0 ; j--) {
     digitalWrite( pin_data, bitRead( seg, j) );
     PulseClock();
     }
*/
  // DISPLAY OFF
  digitalWrite(pin_load, LOW);
  
  for( int i=XMAX-1 ; i >= 0 ; i-- ) {
    shiftOut(pin_data, pin_clock, MSBFIRST, virtualdisplay[bitplane][i] ); //shiftOut(dataPin, clockPin, bitOrder, value)
  }

  // DIPLAY ON
  digitalWrite(pin_load, HIGH);

  // WAIT FOR THE EYE TO SEE !
  // delayMicroseconds( delayms );
  // digitalWrite(pin_load, LOW); 
}


// PUBLIC API

void SayagLEDDisplayBackend::set_bitplanes(uint8_t bp) {
    this->bitplanes = bp;
}

void SayagLEDDisplayBackend::set_refresh_delay(uint8_t d) {
    this->refresh_delay = d;
}

void GreenLEDDisplayBackend::begin() {
    pinMode(pin_enable, OUTPUT); 
    pinMode(pin_clock,  OUTPUT);
    pinMode(pin_data,   OUTPUT); 
}

void GreenLEDDisplayBackend::clock_pulse(uint8_t udelay=1) {
  digitalWrite(pin_clock, HIGH);
  delayMicroseconds( udelay );
  digitalWrite(pin_clock, LOW);
  delayMicroseconds( udelay );
}

void GreenLEDDisplayBackend::render() {
  render( this->refresh_delay );
}


void GreenLEDDisplayBackend::render(int udelay) {
  render( udelay, 4);
}

void GreenLEDDisplayBackend::render(int udelay, int option) {
  switch( option ) {
  case 1 : 
    {
      /*
      for(int i=0; i<= 4; i++){
       if(i>3)   render7linesPORTgrey( udelay, 0 );
       if(i>2)   render7linesPORTgrey( udelay, 1 );
       if(i>1)   render7linesPORTgrey( udelay, 2 );
       if(i>0)   render7linesPORTgrey( udelay, 3 );    
       if(i>0)   render7linesPORTgrey( udelay, 3 ); 
       }
       */
      break;
    }
  case 2 : 
    {
      render_all_lines( udelay, 0 );
      render_all_lines( udelay, 1 );
      render_all_lines( udelay, 1 );
      render_all_lines( udelay, 2 );
      render_all_lines( udelay, 2 );
      render_all_lines( udelay, 2 );
      render_all_lines( udelay, 3 );    
      render_all_lines( udelay, 3 ); 
      render_all_lines( udelay, 3 ); 
      render_all_lines( udelay, 3 );
      break;
    }
  case 3 : 
    {
      render_all_lines(   udelay, 0 );
      render_all_lines( 3*udelay, 1 );
      render_all_lines( 8*udelay, 2 );
      render_all_lines( 17*udelay, 3 );
      break;
    }
  case 4 : 
    {
      render_all_lines(   udelay, 0 );
      render_all_lines( 2*udelay, 1 );
      render_all_lines( 4*udelay, 2 );
      render_all_lines( 8*udelay, 3 ); 
      break;
    }

  case 5 : 
    {
      render_all_lines( udelay, 3 ); 
      render_all_lines( udelay, 0 );
      render_all_lines( udelay, 3 ); 
      render_all_lines( udelay, 2 );
      render_all_lines( udelay, 3 ); 
      render_all_lines( udelay, 1 );
      render_all_lines( udelay, 3 ); 
      render_all_lines( udelay, 2 );
      render_all_lines( udelay, 3 ); 
      render_all_lines( udelay, 1 );
      render_all_lines( udelay, 3 ); 
      render_all_lines( udelay, 2 );
      render_all_lines( udelay, 3 ); 
      render_all_lines( udelay, 2 );
      render_all_lines( udelay, 3 ); 
      break;
    }
  }
}

void rendermono() {
  render_all_lines( 3000, 0 );
}

