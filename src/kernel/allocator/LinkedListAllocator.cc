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
    free_start->size = HEAP_MIN_FREE_BLOCK_SIZE;
    free_block *first = free_start + HEAP_MIN_FREE_BLOCK_SIZE;
    *first = free_block();
    first->size = Allocator::heap_size - HEAP_MIN_FREE_BLOCK_SIZE;
    first->next = nullptr;
    free_start->next = first;
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::dump_free_memory                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherliste. Zu Debuggingzwecken.      *
 *****************************************************************************/
void LinkedListAllocator::dump_free_memory() {
    if(!initialized) {
        init();
    }
    kout << "Free memory list: ";
    free_block *current = free_start;
    while(nullptr != current->next) {
        kout << current << ": " << current->size << " Byte -> ";
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
    if(!initialized) {
        init();
    }
    if (req_size > (UINT64_MAX - 8)) { // `req_size + 8` would overflow
        return nullptr;
    }
    uint64_t needed_size = req_size + 8;
    if(needed_size < HEAP_MIN_FREE_BLOCK_SIZE) {
        needed_size = HEAP_MIN_FREE_BLOCK_SIZE;
        req_size = HEAP_MIN_FREE_BLOCK_SIZE - 8;
    }
    free_block *current = free_start->next;
    free_block *before = free_start;
    while(nullptr != current && current->size < needed_size) {
        before = current;
        current = current->next;
    }
    if(nullptr == current) {
        return nullptr;
    }
    uint64_t final_size = req_size;
    void *mem = (char *)(current) + 8;
    if((uint64_t) current->size - needed_size < HEAP_MIN_FREE_BLOCK_SIZE) {
        final_size = current->size - 8;
        before->next = current->next;
    } else {
        free_block *new_block = current + needed_size;
        *new_block = free_block();
        new_block->size = current->size - needed_size;
        new_block->next = current->next;
        before->next = new_block;
    }
    uint64_t *size = reinterpret_cast<uint64_t *>(current);
    *size = final_size;
    return mem;
}


/*****************************************************************************
 * Methode:         LinkedListAllocator::free                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen Speicherblock freigeben.                           *
 *****************************************************************************/
void LinkedListAllocator::free(void *ptr) {

     /* Hier muess Code eingefuegt werden */

}

