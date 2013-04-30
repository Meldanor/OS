/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "object/o_stream.h"

/** \todo implementieren **/
O_Stream::O_Stream() : Stringbuffer(){
  /* ToDo: insert sourcecode */
}

/** \todo implementieren **/
O_Stream::~O_Stream(){
  /* ToDo: insert sourcecode */
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (char value) {
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (unsigned char value) {
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (char* value) {
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (const char* value) {
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (short value) {
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (unsigned short value) {
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (int value) {
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (unsigned int value) {
  /* ToDo: insert sourcecode */
  return *this;

}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (long value) {
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (unsigned long value) {
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (void* value) {
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (FGColor fgColor){
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (BGColor bgColor){
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& O_Stream::operator << (Blink blink){
  /* ToDo: insert sourcecode */
  return *this;
}

/** \todo implementieren **/
O_Stream& endl (O_Stream& os) {
  /* ToDo: insert sourcecode */
  return os;
}

/** \todo implementieren **/
O_Stream& bin (O_Stream& os) {
  /* ToDo: insert sourcecode */
  return os;
}

/** \todo implementieren **/
O_Stream& oct (O_Stream& os) {
  /* ToDo: insert sourcecode */
  return os;
}

/** \todo implementieren **/
O_Stream& dec (O_Stream& os) {
  /* ToDo: insert sourcecode */
  return os;
}

/** \todo implementieren **/
O_Stream& hex (O_Stream& os) {
  /* ToDo: insert sourcecode */
  return os;
}

O_Stream& O_Stream::operator << (O_Stream& (*f) (O_Stream&)) {
  return f(*this);
}
