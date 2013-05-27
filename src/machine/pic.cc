/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/pic.h"
#include "machine/io_port.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

PIC::PIC() : masterCntrlPort(0x20), slaveCntrlPort(0xA0), masterDataPort (0x21), slaveDataPort (0xA1) {

    // Initialize the pic controller
    // Standard status for the pic controller is something we dont want to have
    // So we have to initialize it
    // Nice dude!

    masterCntrlPort.outb(0x11);
    slaveCntrlPort.outb(0x11);

    // Offset for interrupt indecies
    masterDataPort.outb(32); // Offset for devices on master
    slaveDataPort.outb(40); // Offset for devices on slave

    masterDataPort.outb(4);
    slaveDataPort.outb(2);

    masterDataPort.outb(3);
    slaveDataPort.outb(3);

    masterDataPort.outb(0xFB);
    slaveDataPort.outb(0xFF);
}

void PIC::allow(Interrupts interrupt) {
    unsigned char tmp = 0;
    IO_Port dest = masterDataPort;
    // OCW from master
    if (interrupt < 8) {
        dest = masterDataPort;
        tmp = interrupt;
    }
        
    // OCW from slave
    else {
        dest = slaveDataPort;
        tmp = interrupt - 8;
    }

    // Delete the bit -> allow interrupt for this machine
    dest.outb(dest.inb() & ~(1 << tmp));
}

void PIC::forbid(Interrupts interrupt) {
    unsigned char tmp = 0;
    IO_Port dest = masterDataPort;
    // OCW from master
    if (interrupt < 8) {
        dest = masterDataPort;
        tmp = interrupt;
    }
        
    // OCW from slave
    else {
        dest = slaveDataPort;
        tmp = interrupt - 8;
    }

    // Set the bit -> disallow interrupt for this machine
    dest.outb(dest.inb() | (1 << tmp));
}

// Inform the PIC that a interrupt is complete
void PIC::ack(bool secondPIC) {

    const unsigned char EOI = 0x20;

    // When the slave ack is set, also set the master
    if (secondPIC)
        slaveCntrlPort.outb(EOI);

    masterCntrlPort.outb(EOI);
}

// Get the current stat of the ISR
unsigned char PIC::getISR(bool secondPIC) {

    const unsigned char READ_ISR = 0x0B;

    // Get the ISR from the slave
    if (secondPIC) {
        slaveCntrlPort.outb(READ_ISR);
        return slaveDataPort.inb();
    }
    // Get the ISR from the master
    else {
        masterCntrlPort.outb(READ_ISR);
        return masterDataPort.inb();
    }
}
