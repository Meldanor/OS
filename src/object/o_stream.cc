/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "object/o_stream.h"

/* ToDo: insert sourcecode */

O_Stream& O_Stream::operator << (FGColor fgColor){
  flush();
  setAttribFGColor(fgColor.fgColor);
  return *this;
}

O_Stream& O_Stream::operator << (BGColor bgColor){
  flush();
  setAttribBGColor(bgColor.bgColor);
  return *this;
}

O_Stream& O_Stream::operator << (Blink blink){
  flush();
  setAttribBlink(blink.bBlink);
  return *this;
}


/* ToDo: insert sourcecode */
