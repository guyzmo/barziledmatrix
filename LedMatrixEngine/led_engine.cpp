#include "led_engine.h"

#include <buffer_handler.h>

#include <inttypes.h>

LedEngine::LedEngine(LedDisplayBackend* b) : backend(b) { 
}

void LedEngine::begin() {
    volatile uint8_t i, j;
    BufferHandler::Timer1A::setup(backend);
    backend->begin();
    BufferHandler::Timer1A::start();
}

void LedEngine::test_display() {
    static int x=0, y=0;
    backend->change_byte(++x, ++y, 0xff);
}

void LedEngine::show_splash() {
}

void LedEngine::load_game() {
}

