#ifndef _BACKEND_H_
#define _BACKEND_H_

#include <inttypes.h>

class LedDisplayBackend {
    public:
        // setup
        virtual void begin() = 0;

        // run
        virtual void render() = 0;

        // getters
        virtual uint8_t get_width() = 0;
        virtual uint8_t get_height() = 0;
        virtual uint8_t get_size() = 0;

        // operations
        virtual void update_buffer(const char* buffer) = 0;
        virtual void change_byte(uint8_t x, uint8_t y, uint8_t v) = 0;
};

#endif
