/*****************************************************************************
 *                                                                           *
 *                            H E A P D E M O                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demonstration der dynamischen Speicherverwaltung.        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 27.12.2016                      *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/Allocator.h"
#include "user/aufgabe2/HeapDemo.h"
//#include "user/aufgabe2/MyObj.h"


// Hilfsfunktion: Auf Return-Taste warten
void waitForReturn() {

    /* hier muss Code eingefuegt werden */

}


void heap_demo() {
    allocator.dump_free_memory();
    void *mem = allocator.alloc(150);
    kout << "Allocated 150 Byte at " << mem << endl;
    allocator.dump_free_memory();
    mem = allocator.alloc(50);
    kout << "Allocated 50 Byte at " << mem << endl;
    allocator.dump_free_memory();
    mem = allocator.alloc(2096870);
    if(mem == nullptr) {
        kout << "Couldn't allocate 2096870 Byte. Not enough space for metadata." << endl;
    }
    allocator.dump_free_memory();
    /*
    allocator.alloc(1500000);
    allocator.alloc(597152);
    allocator.dump_free_memory();
    allocator.alloc(597152);
    */
}
