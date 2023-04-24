/*****************************************************************************
 *                                                                           *
 *                           T E X T D E M O                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                       *
 *****************************************************************************/

#include "kernel/Globals.h"


void text_demo() {

    // Bildschirm loeschen.
    kout.clear();

    // Startmeldung ausgeben
    kout << "Test der Zahlenausgabefunktion:" << endl << endl << " | dec | hex | bin   |" << endl << " ---------------------" << endl;
    for(int i = 0; i <= 16; i++) {
        kout << " | " << dec << i << " | " << hex << i << " | " << bin << i << " | " << endl;
    }
}
