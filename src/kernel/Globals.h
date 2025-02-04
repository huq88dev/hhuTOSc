/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/
#ifndef __Globals_include__
#define __Globals_include__

#include "devices/CGA_Stream.h"
#include "devices/Keyboard.h"
#include "devices/PCSPK.h"
#include "kernel/CPU.h"
#include "kernel/allocator/BumpAllocator.h"
#include "kernel/allocator/BumpAllocator.h"
//#include "kernel/allocator/LinkedListAllocator.h"
#include "kernel/interrupts/IntDispatcher.h"
#include "kernel/interrupts/PIC.h"

extern CPU                   cpu;        // CPU-spezifische Funktionen
extern PCSPK                 pcspk;      // PC-Lautsprecher
extern CGA_Stream            kout;       // Ausgabe-Strom fuer Kernel
extern Keyboard              kb;         // Tastatur
extern IntDispatcher         intdis;     // Unterbrechungsverteilung
extern PIC                   pic;        // Interrupt-Controller
extern uint64_t          total_mem;  // RAM total
extern BumpAllocator         allocator;
//extern LinkedListAllocator   allocator;

#endif
