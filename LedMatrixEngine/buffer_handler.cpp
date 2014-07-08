#include "buffer_handler.h"

#include <util/delay.h>
#include <avr/interrupt.h>


namespace BufferHandler {
namespace Timer1A {

LedDisplayBackend* display;

void setup(LedDisplayBackend* disp) {
    display = disp;
    OCR1A = 2000; // 1ms wait
    TCCR1B = (TCCR1B & ~(0x07<<CS10)) | (2<<CS10);

    OCR1A = 0x4000;
    TCNT1 = 0;
}

void start() {
    TIMSK1 |= (1<<OCIE1A);
}
void stop() {
    TIMSK1 &= ~(1<<OCIE1A);
}

}
}

ISR(TIMER1_COMPA_vect) {
    cli();
    BufferHandler::Timer1A::display->render();
    sei();
}

