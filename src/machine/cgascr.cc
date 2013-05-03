/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"
#include "machine/io_port.h"
#include "config.h"

static char* SCREEN_MEMORY_START = (char*)0xb8000;
static char* SCREEN_MEMORY_END = (char*)0xb8fa0;

static unsigned char defaultAttribute;

CGA_Screen::CGA_Screen() {
	defaultAttribute = DEFAULT_SCREEN_ATTRIB;
}

CGA_Screen::~CGA_Screen(){
}

void CGA_Screen::clear() {
	// Reset the screen
	for (char* tmp = SCREEN_MEMORY_START ; tmp < SCREEN_MEMORY_END ; tmp += 2) {
		*tmp = ' ';
		*(tmp +1) = '\0';
	}
	// Reset the cursor
	setpos(0,0);
}

void CGA_Screen::setpos (unsigned short x, unsigned short y) {
	// Range check
	if (x < 0 || y < 0 || x >= 80 || y >= 25) {
		return;
	}

	unsigned short pos = (x + y * 80);

	IO_Port idxPort = IO_Port(0x3d4);
	IO_Port dataPort = IO_Port(0x3d5);

	// Shift bits of the left side of the position to the right 
	unsigned char highValue = (unsigned char)(pos >> 8);
	unsigned char lowValue = (unsigned char)(pos);

	// Write the values to the graphic card register
	// Get control over the high register
	idxPort.outb(14);
	// Write high value into the high register
	dataPort.outb(highValue);
	// Get control over the high register
	idxPort.outb(15);
	// Write low value into the low register
	dataPort.outb(lowValue);
}

void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{

	unsigned short pos = 0;
	IO_Port idxPort = IO_Port(0x3d4);
	IO_Port dataPort = IO_Port(0x3d5);

	// Access the high register
	idxPort.outb(14);
	// Read the high bytes of the cursor position
	unsigned char highValue = dataPort.inb();

	// Access the low register
	idxPort.outb(15);
	// Read the low bytes of the cursor position
	unsigned char lowValue = dataPort.inb();

	// Combine the high and low byte to one value
	pos = ((((unsigned short)highValue) << 8) | lowValue);
	// calculate the x and y position from the pos
	y = pos / 80;
	x = (pos % 80);
}

void CGA_Screen::show (unsigned short x, unsigned short y, char c, unsigned char attrib) {
	// Range check
	if (x >= 80 || y >= 25) {
		return;
	}
  	char* temp = SCREEN_MEMORY_START;
  	// Every row = 160 Bytes (80 chars a 2 Byte)
  	// Every cell in one row = 2 Byte
  	int pos = x * 2 + y * 160;
  	temp[pos] = c;
  	temp[pos + 1] = attrib;
}


void CGA_Screen::print (const char* string, unsigned int n) {
	unsigned short x,y;
	// Get the current cursor position
	getpos(x,y);
	for (unsigned int i = 0 ; i < n ; ++i, ++x) {
		// Current line is full - switch to next line
		if (x >= 80) {
			++y;
			x = 0;
		}
		//  Complete console is full - scroll up
		if (y >= 25) {
			--y;
			scrollup();
		}
		show(x, y, string[i], defaultAttribute);
	}
	// Update the cursor position
    setpos(x, y);
}

void CGA_Screen::scrollup () {
    // Shift memory
    for (char* tmp = SCREEN_MEMORY_START + 160 ; tmp <= SCREEN_MEMORY_END ; ++tmp) {
    	*(tmp - 160) = *tmp;
    }
    // Clear last line
	for (char* tmp = SCREEN_MEMORY_END - 160 ; tmp <= SCREEN_MEMORY_END ; tmp += 2) {
    	*tmp = ' ';
    	*(tmp + 1) = 0;
    }
    
    // update the cursor position
    unsigned short x,y;
    getpos(x,y);
    setpos(x,y-1);
}

void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink) {
    defaultAttribute = fgColor | (bgColor << 4) | (blink << 7);
}
