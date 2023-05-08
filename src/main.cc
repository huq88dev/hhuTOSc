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
#include "user/aufgabe2/HeapDemo.h"
#include "user/aufgabe2/SoundDemo.h"

extern "C" void init_interrupts();


void aufgabe01() {
   // Bildschirmausgabe testen
   text_demo();

   // Tastatur testen
   keyboard_demo();
}


void aufgabe02() {
    // Memory testen
    heap_demo();

    // Soundausgabe testen
    sound_demo();
}


void aufgabe03() {
    // Keyboard & Interrupts testen
    keyboard_demo();
}


/*****************************************************************************
 * Funktion:        main                                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    C-Einstiegsfunktion fuer hhuTOS.                         *
 *****************************************************************************/
int main() {
    // Heapverwaltung initialisieren
    allocator.init();

    // IDT & PIC initialisieren
    // init_interrupts();     // in 'interrupts.asm'

    // Tastatur-Unterbrechungsroutine 'einstoepseln'

    // Interrupt-Verarbeitung durch CPU erlauben

    // Bildschirm loeschen.
    kout.clear();

    // Startmeldung ausgeben
    kout << "Starting..." << endl;

    //aufgabe01();

    aufgabe02();

    //aufgabe03();

    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
 }
