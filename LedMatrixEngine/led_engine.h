#ifndef _LED_ENGINE_H_
#define _LED_ENGINE_H_

#include <backend/backend.h>

class LedEngine {
    LedDisplayBackend* backend;

    public:
        LedEngine(LedDisplayBackend* b);

        void begin();

        void test_display();
        void show_splash();
        void load_game();

};

#endif
