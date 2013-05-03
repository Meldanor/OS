/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S T R E A M                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "device/cgastr.h"

void CGA_Stream::flush () {
	const char* tmp = (const char*)buffer;
	unsigned int n = pos;
	print(tmp, n);
	unsigned short x,y;
	getpos(x,y);
	setpos(0, y+1);
}

void CGA_Stream::setAttributes(int fgColor, int bgColor, bool blink){
	CGA_Screen::setAttributes(fgColor, bgColor, blink);
}
