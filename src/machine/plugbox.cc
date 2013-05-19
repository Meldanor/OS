/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                         P L U G B O X                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/plugbox.h"
#include "useful/panic.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

Plugbox::Plugbox() : slotCounter(0) {
	// Fill array with standard values
	for (int i = 0; i < 256 ; ++i) {
		gates[i] = &panic;
	}
}

void Plugbox::assign(unsigned short slot, Gate& gate) {
	// Error
	if (slot > 256)
		return;
	gates[slot] = &gate;
	gate.setInterruptNumber(slot);
}

Gate& Plugbox::report(unsigned short slot) {
	// Error - return panic object
	if (slot > 256)
		return panic;
	else
		return *(gates[slot]);
}
