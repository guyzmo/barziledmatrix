#ifndef _DISP_SAYAG_H_
#define _DISP_SAYAG_H_

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

#include "backend.h"

#define SCREEN_HEIGHT 144 // pixels
#define SCREEN_WIDTH 64 // pixels

#define BUFFER_SIZE SCREEN_WIDTH*SCREEN_HEIGHT/8

class SayagLEDDisplayBackend : public LedDisplayBackend {
    uint8_t pin_enable;
    uint8_t pin_clock;
    uint8_t pin_data_enable;
    uint8_t pin_data[7];

    uint8_t refresh_delay;

    uint8_t display_buffer[BUFFER_SIZE];

    void clock_pulse(uint8_t udelay=0) const;
    void disable() const;
    void enable() const;

    public:
        SayagLEDDisplayBackend(uint8_t e, uint8_t c, uint8_t de, const uint8_t data[7], uint8_t delay);

        // setup
        void begin();

        // run
        void render() const;

        // getters
        uint8_t get_width() const {
            return SCREEN_WIDTH;
        }
        uint8_t get_height() const {
            return SCREEN_HEIGHT;
        }
        uint16_t get_size() const {
            return BUFFER_SIZE;
        }

        // operations
        void update_buffer(const char* buffer);
        void change_byte(uint8_t x, uint8_t y, uint8_t v);
};

#undef SCREEN_HEIGHT
#undef SCREEN_WIDTH
#undef BUFFER_SIZE

#endif
