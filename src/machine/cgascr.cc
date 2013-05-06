/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"
#include "config.h"

const char* CGA_Screen::SCREEN_MEMORY_START = (char*)0xb8000;
const char* CGA_Screen::SCREEN_MEMORY_END = (char*)0xb8fa0;

const IO_Port CGA_Screen::INDEX_PORT = IO_Port(0x3d4);
const IO_Port CGA_Screen::DATA_PORT = IO_Port(0x3d5);

CGA_Screen::CGA_Screen() {
	colorAttribute = DEFAULT_SCREEN_ATTRIB;
}

CGA_Screen::~CGA_Screen(){
}

void CGA_Screen::clear() {
	// Reset the screen
	for (char* tmp = (char*)SCREEN_MEMORY_START ; tmp < SCREEN_MEMORY_END ; tmp += 2) {
		*tmp = ' ';
		*(tmp +1) = '\0';
	}
	// Reset the cursor
	setpos(0,0);
}

void CGA_Screen::setpos (unsigned short x, unsigned short y) {
	// Range check
	if (x < 0 || y < 0 || x >= COLUMNS || y >= ROWS) {
		return;
	}

	// The current pixel index (not byte index) of the cursor
	unsigned short pos = x + (y * COLUMNS);

	// Shift bits of the left side of the position to the right 
	unsigned char highValue = (unsigned char)(pos >> 8);
	unsigned char lowValue = (unsigned char)(pos);

	// Write the values to the graphic card register
	// Get control over the high register
	INDEX_PORT.outb(14);
	// Write high value into the high register
	DATA_PORT.outb(highValue);
	// Get control over the high register
	INDEX_PORT.outb(15);
	// Write low value into the low register
	DATA_PORT.outb(lowValue);
}

void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{

	unsigned short pos = 0;

	// Access the high register
	INDEX_PORT.outb(14);
	// Read the high bytes of the cursor position
	unsigned char highValue = DATA_PORT.inb();

	// Access the low register
	INDEX_PORT.outb(15);
	// Read the low bytes of the cursor position
	unsigned char lowValue = DATA_PORT.inb();

	// Combine the high and low byte to one value
	pos = ((((unsigned short)highValue) << 8) | lowValue);
	// calculate the x and y position from the pos
	y = pos / COLUMNS;
	x = (pos % COLUMNS);
}

void CGA_Screen::show (unsigned short x, unsigned short y, char c, unsigned char attrib) {
	// Range check
	if (x >= COLUMNS || y >= ROWS) {
		return;
	}
  	char* temp = (char*)SCREEN_MEMORY_START;
  	// Every row = 160 Bytes (80 chars a 2 Byte)
  	// Every cell in one row = 2 Byte
  	int pos = x * 2 + y * (COLUMNS * 2);
  	// Set the char
  	temp[pos] = c;
  	// Set the char attributes
  	temp[pos + 1] = attrib;
}


void CGA_Screen::print (const char* string, unsigned int n) {
	unsigned short x,y;
	// Get the current cursor position
	getpos(x,y);
	for (unsigned int i = 0 ; i < n ; ++i, ++x) {
		// Make a new line
		if (string[i] == '\n') {
			++y;
			x = 0;
			continue;
		}
		// Current line is full - switch to next line
		if (x >= COLUMNS) {
			++y;
			x = 0;
		}
		//  Complete console is full - scroll up
		if (y >= ROWS) {
			--y;
			scrollup();
		}
		show(x, y, string[i], colorAttribute);
	}
	// Update the cursor position
    setpos(x, y);
}

void CGA_Screen::scrollup () {
    // Shift memory
    for (char* tmp = (char*)SCREEN_MEMORY_START + (COLUMNS * 2) ; tmp <= SCREEN_MEMORY_END ; ++tmp) {
    	*(tmp - (COLUMNS * 2)) = *tmp;
    }
    // Clear last line
	for (char* tmp = (char*)SCREEN_MEMORY_END - (COLUMNS * 2) ; tmp <= SCREEN_MEMORY_END ; tmp += 2) {
    	*tmp = ' ';
    	*(tmp + 1) = 0;
    }
    
    // update the cursor position
    unsigned short x, y;
    getpos(x, y);
    setpos(x, --y);
}

void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink) {
	// First four bits are the forecolor
	// the fourth until the seventh bit are the backcolor
	// 0xF == 0000 1111 (Mask for front color)
	// 0xE0== 0111 0000 (Mask for back color)
	// Shift the black ground color forth to the left to be at the right position
	// Combine the both with the LOGICAL OR
	colorAttribute = (fgColor) | ((bgColor ) << 4);
	// Set the bit
	if (blink) 
		colorAttribute |= 0x80;
	// Delete the bit
	else
		colorAttribute &= ~(0x80);
}
