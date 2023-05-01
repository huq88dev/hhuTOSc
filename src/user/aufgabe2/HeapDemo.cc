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
    kout << "Allocating 150 Byte..." << endl;
    uint64_t *mem = reinterpret_cast<uint64_t *>(allocator.alloc(150));
    kout << "Allocated " << *(mem - 1) << " Byte at " << mem << endl;
    allocator.dump_free_memory();
    kout << "Allocating 50 Byte..." << endl;
    mem = reinterpret_cast<uint64_t *>(allocator.alloc(50));
    kout << "Allocated " << *(mem - 1) <<  " Byte at " << mem << endl;
    allocator.dump_free_memory();
    kout << "Allocating 2096860 Byte..." << endl;
    mem = reinterpret_cast<uint64_t *>(allocator.alloc(2096860));
    if(mem == nullptr) {
        kout << "Couldn't allocate 2096860 Byte. Not enough space for metadata." << endl;
    }
    allocator.dump_free_memory();
    /*
    allocator.alloc(1500000);
    allocator.alloc(597152);
    allocator.dump_free_memory();
    allocator.alloc(597152);
    */
}
