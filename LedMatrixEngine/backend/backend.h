#ifndef _BACKEND_H_
#define _BACKEND_H_

class LedDisplayBackend {
    void begin();
    void set_bitplanes(uint8_t bp);
    void set_refresh_delay(uint8_t d);
    void clock_pulse();
    void render(int udelay=0, int option=0);
}

#endif
