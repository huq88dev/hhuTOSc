/*****************************************************************************
 *                                                                           *
 *                        K E Y B O A R D D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#include "kernel/Globals.h"


void keyboard_demo() {
    int x, y;
    while(1) {
        kout.getpos(x, y);
        while(y >= kout.ROWS || x >= kout.COLUMNS) {
            kout.scrollup();
            kout.getpos(x, y);
        }
        Key input = kb.key_hit();
        if(input != NULL) {
            kout << input.ascii();
            kout.flush();
        }
    }

}
