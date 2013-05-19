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
	plugbox.assign(PIC::keyboard, *this);
}

void Keyboard::trigger() {
	Key key = key_hit();
	// Invalid key
	if (!key.valid()) {
		kout << "Invalid key!" << endl;
		pic.ack(isSecondPIC );
		return;	
	}
	// CTRL + ALT + DEL = Reboot
	else if (key.ctrl() && key.alt() && key.scancode() == Key::scan::del) {
		reboot();
	}
	// Otherwise print the key in ascii on a specific position
	else {
		kout.show(4,10, key.ascii(), DEFAULT_SCREEN_ATTRIB);
		pic.ack(isSecondPIC );	
	}
}
