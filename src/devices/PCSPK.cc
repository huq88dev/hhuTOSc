/*****************************************************************************
 *                                                                           *
 *                                P C S P K                                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Mit Hilfe dieser Klasse kann man Toene auf dem           *
 *                  PC-Lautsprecher ausgeben.                                *
 *                                                                           *
 * Achtung:         Qemu muss mit dem Parameter -soundhw pcspk aufgerufen    *
 *                  werden. Ansonsten kann man nichts hoeren.                *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 22.9.2016                       *
 *****************************************************************************/

#include "devices/PCSPK.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         PCSPK::play                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ton abspielen.                                           *
 *                                                                           *
 * Rückgabewerte:   f:   Frequenz des Tons                                   *
 *                  len: Laenge des Tons in ms                               *
 *****************************************************************************/
void PCSPK::play (float f, int len) {
    int freq = (int)f;
    int cntStart  =  1193180 / freq;
    int status;
    
    
    // Zaehler laden
    control.outb (0xB6);            // Zaehler-2 konfigurieren
    data2.outb (cntStart%256);      // Zaehler-2 laden (Lobyte)
    data2.outb (cntStart/256);      // Zaehler-2 laden (Hibyte)

    // Lautsprecher einschalten
    status = (int)ppi.inb ();       // Status-Register des PPI auslesen
    ppi.outb ( status|3 );          // Lautpsrecher Einschalten

    // Pause
    delay(len);
    
    // Lautsprecher ausschalten
    off ();
}


/*****************************************************************************
 * Methode:         PCSPK::off                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Lautsprecher ausschalten.                                *
 *****************************************************************************/
void PCSPK::off () {
    int status;

    status = (int)ppi.inb ();       // Status-Register des PPI auslesen
    ppi.outb ( (status>>2)<<2 );    // Lautsprecher ausschalten
}


/*****************************************************************************
 * Methode:         PCSPK::readCounter                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zaehler von PIT Channel 0 auslesen.                      * 
 *                  (wird fuer delay benoetigt).                             *
 *                                                                           *
 * Rückgabewerte:   counter                                                  *
 *****************************************************************************/
inline unsigned int PCSPK::readCounter() {
    unsigned char lo, hi;

    control.outb (0x0);         // Latch Command
    lo = data0.inb ();       // Lobyte des Counters auslesen
    hi = data0.inb ();       // Hibyte des Counters auslesen
    return (hi << 8) | lo;
}


/*****************************************************************************
 * Methode:         PCSPK::delay                                             *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Verzoegerung um X ms (in 1ms Schritten; Min. 1ms).       *
 *                  Da der Counter "nur" 16 Bit hat muss man evt. mehrmals   *
 *                  herunterzaehlen.                                         * 
 *                                                                           *
 * Parameter:       time (delay in ms)                                       *
 *****************************************************************************/
inline void PCSPK::delay (int time) {
    if(time <= 0) {
        return;
    }
    unsigned int pit_freq = 1193180;
    unsigned int necessary_decrements = (pit_freq * (unsigned int)time)/1000;
    unsigned int last_read = readCounter();
    unsigned int done_decrements = 0;
    while(done_decrements < necessary_decrements) {
        unsigned int current_read = readCounter();
        if(last_read >= current_read) {
            done_decrements += last_read - current_read;
            last_read = current_read;
        } else {
            done_decrements += last_read;
            done_decrements += UINT16_MAX - current_read;
            last_read = current_read;
        }
    }

}


/*****************************************************************************
 * Methode:         PCSPK::tetris                                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Tetris Sound, Kévin Rapaille, August 2013                *
 *                  https://gist.github.com/XeeX/6220067                     *
 *****************************************************************************/
void PCSPK::tetris () {
    play(658, 125);
    play(1320, 500);
    play(990, 250);
    play(1056, 250);
    play(1188, 250);
    play(1320, 125);
    play(1188, 125);
    play(1056, 250);
    play(990, 250);
    play(880, 500);
    play(880, 250);
    play(1056, 250);
    play(1320, 500);
    play(1188, 250);
    play(1056, 250);
    play(990, 750);
    play(1056, 250);
    play(1188, 500);
    play(1320, 500);
    play(1056, 500);
    play(880, 500);
    play(880, 500);
    delay(250);
    play(1188, 500);
    play(1408, 250);
    play(1760, 500);
    play(1584, 250);
    play(1408, 250);
    play(1320, 750);
    play(1056, 250);
    play(1320, 500);
    play(1188, 250);
    play(1056, 250);
    play(990, 500);
    play(990, 250);
    play(1056, 250);
    play(1188, 500);
    play(1320, 500);
    play(1056, 500);
    play(880, 500);
    play(880, 500);
    delay(500);
    play(1320, 500);
    play(990, 250);
    play(1056, 250);
    play(1188, 250);
    play(1320, 125);
    play(1188, 125);
    play(1056, 250);
    play(990, 250);
    play(880, 500);
    play(880, 250);
    play(1056, 250);
    play(1320, 500);
    play(1188, 250);
    play(1056, 250);
    play(990, 750);
    play(1056, 250);
    play(1188, 500);
    play(1320, 500);
    play(1056, 500);
    play(880, 500);
    play(880, 500);
    delay(250);
    play(1188, 500);
    play(1408, 250);
    play(1760, 500);
    play(1584, 250);
    play(1408, 250);
    play(1320, 750);
    play(1056, 250);
    play(1320, 500);
    play(1188, 250);
    play(1056, 250);
    play(990, 500);
    play(990, 250);
    play(1056, 250);
    play(1188, 500);
    play(1320, 500);
    play(1056, 500);
    play(880, 500);
    play(880, 500);
    delay(500);
    play(660, 1000);
    play(528, 1000);
    play(594, 1000);
    play(495, 1000);
    play(528, 1000);
    play(440, 1000);
    play(419, 1000);
    play(495, 1000);
    play(660, 1000);
    play(528, 1000);
    play(594, 1000);
    play(495, 1000);
    play(528, 500);
    play(660, 500);
    play(880, 1000);
    play(838, 2000);
    play(660, 1000);
    play(528, 1000);
    play(594, 1000);
    play(495, 1000);
    play(528, 1000);
    play(440, 1000);
    play(419, 1000);
    play(495, 1000);
    play(660, 1000);
    play(528, 1000);
    play(594, 1000);
    play(495, 1000);
    play(528, 500);
    play(660, 500);
    play(880, 1000);
    play(838, 2000);
    off ();
}


/*****************************************************************************
 * Methode:         PCSPK::tetris                                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:        Clint, Part of Daft Punk’s Aerodynamic               *
 *                      https://www.kirrus.co.uk/2010/09/linux-beep-music/   *
 *****************************************************************************/
void PCSPK::aerodynamic() {
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(440.0, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(440.0, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(440.0, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(440.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(440.0, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(440.0, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(440.0, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(370.0, 122);
    play(493.9, 122);
    play(370.0, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(587.3, 122);
    play(415.3, 122);
    play(493.9, 122);
    play(415.3, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(784.0, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(493.9, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(440.0, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(440.0, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(440.0, 122);
    play(659.3, 122);
    play(440.0, 122);
    play(554.4, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(740.0, 122);
    play(987.8, 122);
    play(740.0, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1174.7, 122);
    play(830.6, 122);
    play(987.8, 122);
    play(830.6, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1568.0, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(987.8, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    play(1318.5, 122);
    play(880.0, 122);
    play(1108.7, 122);
    play(880.0, 122);
    off ();
}
