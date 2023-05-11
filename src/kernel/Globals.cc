/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/

#include "kernel/Globals.h"

CPU             cpu;        // CPU-spezifische Funktionen
PCSPK           pcspk;      // PC-Lautsprecher
CGA_Stream      kout;       // Ausgabe-Strom fuer Kernel
uint64_t        total_mem;  // RAM total
Keyboard        kb;         // Tastatur
IntDispatcher         intdis;     // Unterbrechungsverteilung
PIC                   pic;        // Interrupt-Controller
BumpAllocator         allocator;
//LinkedListAllocator   allocator;
Scheduler             scheduler;  // Scheduler

