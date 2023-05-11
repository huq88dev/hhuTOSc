/*****************************************************************************
 *                                                                           *
 *                         K E Y I R Q D E M O                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo zu Interrupts.                                      *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#include "kernel/Globals.h"


void key_irq_demo() {

   while(true) {
       for (int i = 0; i < 10; i++) {
           pic.forbid(pic.keyboard);
           kout.setpos(0, i + 5);
           kout << i << endl;
           pic.allow(pic.keyboard);
       }
   }
}
