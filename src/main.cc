/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Startroutine, wird direkt vom Bootlader angesprungen,    *
 *                  nachdem dieser in den Protected Mode geschaltet hat und  *
 *                  die GDT und IDT initalisiert hat.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/aufgabe1/TextDemo.h"
#include "user/aufgabe1/KeyboardDemo.h"


void aufgabe01() { 
   // Bildschirmausgabe testen
   text_demo();
    
   // Tastatur testen
   keyboard_demo();
}

int main() {
    // Bildschirm loeschen.
    kout.clear();
    
    // Startmeldung ausgeben
    kout << "Starting..." << endl;

    aufgabe01();

    while (1);
    return 0;
 }
