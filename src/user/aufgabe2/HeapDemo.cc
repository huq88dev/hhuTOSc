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


/*// Hilfsfunktion: Auf Return-Taste warten
void waitForReturn() {

    *//* hier muss Code eingefuegt werden *//*

}*/


void heap_demo() {
    allocator.dump_free_memory();
    kout << "Allocating 150 Byte..." << endl;
    uint64_t *mem_1 = reinterpret_cast<uint64_t *>(allocator.alloc(150));
    kout << "Allocated " << *(mem_1 - 1) << " Byte at " << mem_1 << endl;
    allocator.dump_free_memory();
    kout << "Allocating 50 Byte..." << endl;
    uint64_t *mem_2 = reinterpret_cast<uint64_t *>(allocator.alloc(50));
    kout << "Allocated " << *(mem_2 - 1) <<  " Byte at " << mem_2 << endl;
    allocator.dump_free_memory();
    kout << "Freeing " << mem_1 << endl;
    allocator.free(mem_1);
    allocator.dump_free_memory();
    kout << "Allocating 140 Byte..." << endl;
    mem_1 = reinterpret_cast<uint64_t *>(allocator.alloc(140));
    kout << "Allocated " << *(mem_1 - 1) << " Byte at " << mem_1 << endl;
    allocator.dump_free_memory();
    kout << "Allocating 1000 Byte..." << endl;
    uint64_t *mem_3 = reinterpret_cast<uint64_t *>(allocator.alloc(1000));
    kout << "Allocated " << *(mem_3 - 1) <<  " Byte at " << mem_3 << endl;
    allocator.dump_free_memory();
    kout << "Freeing " << mem_3 << endl;
    allocator.free(mem_3);
    allocator.dump_free_memory();
    kout << "Freeing " << mem_1 << endl;
    allocator.free(mem_1);
    allocator.dump_free_memory();
    kout << "Freeing " << mem_2 << endl;
    allocator.free(mem_2);
    allocator.dump_free_memory();
}