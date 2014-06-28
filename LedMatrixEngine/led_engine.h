
#include "backend/backend.h"

class LedEngine {
    LedDisplayBackend* backend;
    public:
        LedEngine(LedDisplayBackend* b) {
            backend = b;
        }

        void begin();

        void test_display();
        void show_splash();
        void load_game();

};

