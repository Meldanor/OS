/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                       K E Y B O A R D                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "device/keyboard.h"
#include "useful/plugbox.h"
#include "useful/pic.h"
#include "useful/kout.h"
#include "config.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

const unsigned char x = 4;
const unsigned char y = 10;
const bool isSecondPIC = PIC::keyboard >= 8;

Keyboard::Keyboard() : Keyboard_Controller() , Gate() {

}

void Keyboard::plugin() {
	pic.allow(PIC::keyboard);
	plugbox.assign(Plugbox::keyboardSlot, *this);
}

extern unsigned char globalTaskChoice; 

void Keyboard::trigger() {
	Key key = key_hit();
	if (key.valid()) {

		// CTRL + ALT + DEL = Reboot
		if (key.ctrl() && key.alt() && key.scancode() == Key::scan::del) {
			reboot();
		}
		else if (key.alt()) {
			switch(key.ascii()) {
				case '1':
					globalTaskChoice = 1;
					break;
				case '2':
					globalTaskChoice = 2;
					break;
				default:
					break;
					// Nothing to do
			}
		}
		// Otherwise print the key in ascii on a specific position
		else {
			kout.show(4,10, key.ascii(), DEFAULT_SCREEN_ATTRIB);	
		}
	}
	pic.ack(isSecondPIC );	
}
