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
#include "user/aufgabe3/KeyIRQDemo.h"

extern "C" void _init_interrupts();


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
    key_irq_demo();
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
    _init_interrupts();     // in 'interrupts.asm'

    // Tastatur-Unterbrechungsroutine 'einstoepseln'
    kb.plugin();

    // Interrupt-Verarbeitung durch CPU erlauben
    cpu.enable_int();

    // Bildschirm loeschen.
    kout.clear();

    // Startmeldung ausgeben
    kout << "Awesome OS!\n==========================\n\nUnterstuetze Funktionen:" << endl;
    kout << "   - Bildschirmausgaben" << endl;
    kout << "   - Sound ueber den PC-Lautsprecher" << endl;
    kout << "   - Einfache Heap-Verwaltung" << endl;
    kout << "   - Tastatureingaben" << endl;
    kout << "   - Interrupts" << endl;

    //aufgabe01();

    //aufgabe02();

    aufgabe03();

    while (1) ; // wir kehren nicht zum Bootlader zurueck
    return 0;
 }
