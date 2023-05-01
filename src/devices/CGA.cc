/*****************************************************************************
 *                                                                           *
 *                                    C G A                                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Mit Hilfe dieser Klasse kann man auf den Bildschirm des  *
 *                  PCs zugreifen. Der Zugriff erfolgt direkt auf der Hard-  *
 *                  wareebene, d.h. ueber den Bildschirmspeicher und den     *
 *                  I/O-Ports der Grafikkarte.                               *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *                  Aenderungen von Michael Schoettner, HHU, 21.8.2016       *
 *****************************************************************************/
#include "devices/CGA.h"


/*****************************************************************************
 * Methode:         CGA::setpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Setzen des Cursors in Spalte x und Zeile y.              *
 *****************************************************************************/
void CGA::setpos (int x, int y) {
    unsigned short total_pos = y * COLUMNS + x;
    index_port.outb(14);
    data_port.outb(total_pos >> 8);
    index_port.outb(15);
    data_port.outb(total_pos & 0xff);
}


/*****************************************************************************
 * Methode:         CGA::getpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Abfragem der Cursorposition                              *
 *                                                                           *
 * Rückgabewerte:   x und y                                                  *
 *****************************************************************************/
void CGA::getpos (int &x, int &y) {
    index_port.outb(14);
    unsigned short high = data_port.inb();
    index_port.outb(15);
    unsigned short low = data_port.inb();
    unsigned short total_pos = (high << 8) | low;
    x = total_pos % COLUMNS;
    y = (int) total_pos / COLUMNS;
}


/*****************************************************************************
 * Methode:         CGA::show                                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige eines Zeichens mit Attribut an einer bestimmten  *
 *                  Stelle auf dem Bildschirm.                               *
 *                                                                           *
 * Parameter:                                                                *
 *      x,y         Position des Zeichens                                    *
 *      character   Das auszugebende Zeichen                                 *
 *      attrib      Attributbyte fuer das Zeichen                            *
 *****************************************************************************/
void CGA::show (int x, int y, char character, unsigned char attrib) {
    char *pos;
    pos = const_cast<char *>(CGA_START) + 2*(x + y*COLUMNS);
    *pos = character;
    *(pos + 1) = attrib;
}


/*****************************************************************************
 * Methode:         CGA::print                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige von 'n' Zeichen ab der aktuellen Cursorposition  *
 *                  '\n' fuer Zeilenvorschub.                                *
 *                                                                           *
 * Parameter:                                                                *
 *      string      Auszugebende Zeichenkette                                *
 *      n           Laenger der Zeichenkette                                 *
 *      attrib      Attributbyte fuer alle Zeichen der Zeichenkette          *
 *****************************************************************************/
void CGA::print (char* string, int n, unsigned char attrib) {
    int x, y;
    getpos(x, y);
    while(y >= ROWS) {
        scrollup();
        getpos(x, y);
    }
    for (int i = 0; i < n; ++i) {
        if(x == COLUMNS || *(string + i) == '\n') {
            x = 0;
            y++;
            setpos(x, y);
            if (y == ROWS) {
                scrollup();
                y--;
            }
        } else {
            show(x, y, *(string + i), attrib);
            x++;
        }
    }
    setpos(x, y);
}


/*****************************************************************************
 * Methode:         CGA::scrollup                                            *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Verschiebt den Bildschirminhalt um eine Zeile nach oben. *
 *                  Die neue Zeile am unteren Bildrand wird mit Leerzeichen  *
 *                  gefuellt.                                                *
 *****************************************************************************/
void CGA::scrollup () {
    char *send, *recv;
    for(int y = 0; y < ROWS-1; y++) {
        for(int x = 0; x < (COLUMNS*2); x++) {
            send = const_cast<char *>(CGA_START) + x + (y+1) * (COLUMNS*2);
            recv = const_cast<char *>(CGA_START) + x + y * (COLUMNS*2);
            *recv = *send;
        }
    }
    for(int x = 0; x < COLUMNS; x++) {
        show(x, ROWS-1, ' ', BLACK);
    }
    setpos(0, ROWS-1);
}


/*****************************************************************************
 * Methode:         CGA::clear                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Lösche den Textbildschirm.                               *
 *****************************************************************************/
void CGA::clear () {
    for (int x = 0; x < COLUMNS; ++x) {
        for (int y = 0; y < ROWS; ++y) {
            show(x, y, ' ', BLACK);
        }
    }
    setpos(0, 0);
}


/*****************************************************************************
 * Methode:         CGA::attribute                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hilfsfunktion zur Erzeugung eines Attribut-Bytes aus     *
 *                  Hintergrund- und Vordergrundfarbe und der Angabe, ob das *
 *                  Zeichen blinkend darzustellen ist.                       *
 *                                                                           *
 * Parameter:                                                                *
 *      bg          Background color                                         *
 *      fg          Foreground color                                         *
 *      blink       ywa/no                                                   *
 *****************************************************************************/
unsigned char CGA::attribute (CGA::color bg, CGA::color fg, bool blink) {
    unsigned char att = 0;
    if(blink) {
        att |= 1 << 7;
    }
    att |= (bg << 4 | fg);
    return att;
}
