/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"
#include "machine/io_port.h"

static char* SCREEN_POINTER = (char*)0xb8000;
static char* endOfDevice = (char*)0xb8faf;

static unsigned char defaultAttribute;

CGA_Screen::CGA_Screen() {
    setAttributes(15, 0, 0);
}

/** \todo implementieren **/
CGA_Screen::~CGA_Screen(){
  /* ToDo: insert sourcecode */ 
}

void CGA_Screen::clear()
{

	char* temp;
	temp = SCREEN_POINTER;

	while(temp < endOfDevice)
	{
		*temp = ' ';
		*(temp + 1) = 0x0;
		temp += 0x2;
	}



}

void CGA_Screen::setpos (unsigned short x, unsigned short y) {

	// Is this neccessary or is this paradise?
	unsigned short pos = (y * 160 + x * 2);

	IO_Port idxPort = IO_Port(0x3d4);
	IO_Port dataPort = IO_Port(0x3d5);

	// convert the unsignded short to a single byte
	char lowValue = (char)(pos >> 8);
	// neccessary values are at right - no shift needed
	char highValue = (char)(pos);

	// Get control over the high register
	idxPort.outb(0x14);
	// Write high value into the high register
	dataPort.outb(highValue);
	// Get control over the high register
	idxPort.outb(0x15);
	// Write low value into the low register
	dataPort.outb(lowValue);
}

void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{
	IO_Port idxPort = IO_Port(0x3d4);
	IO_Port dataPort = IO_Port(0x3d5);

	unsigned short pos = 0;

	//unsigned short val,val_h,val_l;

	idxPort.outb(0x14);
	// Read from high index
	// 0000 0000 1110 1001
	pos = dataPort.inb();

	idxPort.outb(0x15);
	// Read from low index
	// 0000 0000 0110 1100
	// Bitshift the low index value 8 to the left
	// 0110 1100 0000 0000 
	// Combined  
	unsigned short tmp = dataPort.inb();
	pos = (tmp << 8) | pos;
	y = pos / 160;
	x = (pos % 160) >> 1;
}

/** \todo implementieren **/
void CGA_Screen::show (unsigned short x, unsigned short y, char c, unsigned char attrib) {
	// TODO: Implement range check for x and y
  	char* temp = SCREEN_POINTER;
  	// Every row = 160 Bytes (80 chars a 2 Byte)
  	// Every cell in one row = 2 Byte
  	int pos = x * 2 + y * 160;
  	temp[pos] = c;
  	temp[pos + 1] = attrib;
}


void CGA_Screen::print (const char* string, unsigned int n) {
	unsigned short x,y;
	getpos(x,y);

    for (unsigned int i = 0; i < n ; ++i) {
        show(x+i, y, string[i], defaultAttribute);
    }
}

/** \todo implementieren **/
void CGA_Screen::scrollup () {
  /* ToDo: insert sourcecode */ 
}

void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink){
    // TODO: Error
    defaultAttribute = fgColor | (bgColor << 4) | (blink << 8);
}
