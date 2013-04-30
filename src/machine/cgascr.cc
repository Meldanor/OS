/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#include "machine/cgascr.h"

 static char* SCREEN_POINTER = (char*)0xb8000;
 static char* endOfDevice = (char*)0xb8faf;

/** \todo implementieren **/
CGA_Screen::CGA_Screen(){
  /* ToDo: insert sourcecode */
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
		*temp = 0x20;
		*(temp + 1) = 0x0;
		temp += 0x2;
	}



}

/** \todo implementieren **/
void CGA_Screen::setpos (unsigned short x, unsigned short y) {
  /* ToDo: insert sourcecode */ 
}

/** \todo implementieren **/
void CGA_Screen::getpos (unsigned short& x, unsigned short& y) const{
  /* ToDo: insert sourcecode */ 
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

/** \todo implementieren **/
void CGA_Screen::print (const char* string, unsigned int n) {
  /* ToDo: insert sourcecode */ 
}

/** \todo implementieren **/
void CGA_Screen::scrollup () {
  /* ToDo: insert sourcecode */ 
}

/** \todo implementieren **/
void CGA_Screen::setAttributes(int fgColor, int bgColor, bool blink){
  /* ToDo: insert sourcecode */ 
}
