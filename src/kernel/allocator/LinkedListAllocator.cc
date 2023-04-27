/*****************************************************************************
 *                                                                           *
 *                  L I N K E D L I S T A L L O C A T O R                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einfache Speicherverwaltung, welche den freien Speicher  *
 *                  mithilfe einer einfach verketteten Liste verwaltet.      *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 13.6.2020                        *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/allocator/LinkedListAllocator.h"

#define HEAP_MIN_FREE_BLOCK_SIZE 64         // min. Groesse eines freien Blocks


/*****************************************************************************
 * Methode:         LinkedListAllocator::init                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Liste der Freispeicherbloecke intitialisieren.           *
 *                  Anker zeigt auf ein Dummy-Element. Danach folgt          *
 *                  ein Block der den gesamten freien Speicher umfasst.      *
 *                                                                           *
 *                  Wird automatisch aufgerufen, sobald eine Funktion der    *
 *                  Speicherverwaltung erstmalig gerufen wird.               *
 *****************************************************************************/
void LinkedListAllocator::init() {
    initialized = true;

    free_start = reinterpret_cast<free_block *>(Allocator::heap_start);
    *free_start = free_block();
    free_start->size = Allocator::heap_size - HEAP_MIN_FREE_BLOCK_SIZE;
    free_start->next = nullptr;
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::dump_free_memory                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherliste. Zu Debuggingzwecken.      *
 *****************************************************************************/
void LinkedListAllocator::dump_free_memory() {
    kout << "Free memory list: " << free_start << " -> ";
    free_block *current = free_start;
    while(nullptr != current->next) {
        kout << hex << current->next << ": " << current->size << " Byte -> ";
        current = current->next;
    }
    kout  << current << ": " << current->size << " Byte" << endl;
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::alloc                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * LinkedListAllocator::alloc(uint64_t req_size) {

     /* Hier muess Code eingefuegt werden */

}


/*****************************************************************************
 * Methode:         LinkedListAllocator::free                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen Speicherblock freigeben.                           *
 *****************************************************************************/
void LinkedListAllocator::free(void *ptr) {

     /* Hier muess Code eingefuegt werden */

}

