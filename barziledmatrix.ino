// first draft of implementation

#if DISPLAY=SPI
#include <backend/spi_disp.h>
LedDisplayBackend backend = SPILEDDisplayBackend(4,5,6)
#elif DISPLAY=SAYAG
#include <backend/sayag_disp.h>
LedDisplayBackend backend = SayagLEDDisplayBackend(/* TODO */)
#elif DISPLAY=GREEN
LedDisplayBackend backend = GreenLEDDisplayBackend(/* TODO */)
#endif

#include <led_engine.h>

LedEngine LedMatrix(&backend);

void setup() {
    LedMatrix.begin();
}

void loop() {
    ;
}

