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
    allocator.alloc(150);
    allocator.dump_free_memory();
    allocator.alloc(50);
    allocator.dump_free_memory();
    /*
    allocator.alloc(1500000);
    allocator.alloc(597152);
    allocator.dump_free_memory();
    allocator.alloc(597152);
    */
}
