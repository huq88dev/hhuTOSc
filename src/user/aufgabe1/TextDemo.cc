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

    kout << "\nTeste Attributfunktion: " << endl;
    unsigned char attr = kout.attribute(CGA::color::GREEN, CGA::color::MAGENTA, false);
    kout.print("Kein Blinken ", 13, attr);
    attr = kout.attribute(CGA::color::GREEN, CGA::color::MAGENTA, true);
    kout.print("Fake Blinken\n", 13, attr);
}
