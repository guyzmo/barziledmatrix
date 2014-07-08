// first draft of implementation

#include <led_engine.h>
#include <LedMatrixEngine/backend/disp_spi.h>

SPILEDDisplayBackend backend(4,5,6,1/*ms*/);

LedEngine LedMatrix(&backend);

void setup() {
    LedMatrix.begin();
}

void loop() {
    LedMatrix.test_display();
    delay(1000);
}

