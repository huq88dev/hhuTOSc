/*****************************************************************************
 *                                                                           *
 *                        B U M P A L L O C A T O R                          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Eine sehr einfache Heap-Verwaltung, welche freigegebenen *
 *                  Speicher nicht mehr nutzen kann.                         *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 3.3.2022                        *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/allocator/LinkedListAllocator.h"


/*****************************************************************************
 * Methode:         BumpAllocator::init                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    BumpAllokartor intitialisieren.                          *
 *****************************************************************************/
void BumpAllocator::init() {

     next = reinterpret_cast<unsigned char *>(Allocator::heap_start);
     // TODO: Fragen, was die Variable allocations machen soll.

}


/*****************************************************************************
 * Methode:         BumpAllocator::dump_free_memory                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherinfos. Zu Debuggingzwecken.      *
 *****************************************************************************/
void BumpAllocator::dump_free_memory() {
    uint64_t free_memory = reinterpret_cast<unsigned char *>(Allocator::heap_end) - next;
    kout << "Free Memory in BumpAllocator: " << free_memory << " Byte." << endl;
}


/*****************************************************************************
 * Methode:         BumpAllocator::alloc                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * BumpAllocator::alloc(uint64_t req_size) {
    uint64_t free_memory = reinterpret_cast<unsigned char *>(Allocator::heap_end) - next;
    if(req_size > free_memory) {
        kout << "ERROR: Tried to allocate " << req_size << " byte, but only have " << free_memory << " byte of memory left." << endl;
        return nullptr;
    }
    void *mem = next;
    next += req_size;
    return mem;
}


/*****************************************************************************
 * Methode:         BumpAllocator::free                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Nicht implementiert.                                     *
 *****************************************************************************/
void BumpAllocator::free(void *ptr) {
    kout << "   mm_free: ptr= " << hex << (uint64_t)ptr << ", not supported" << endl;
}

