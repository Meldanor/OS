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

PIC::PIC() : masterCntrlPort(0x20), slaveCntrlPort(0xa0), masterDataPort (0x21), slaveDataPort (0xa1) {

    // Initialize the pic controller
    // Standard status for the pic controller is something we dont want to have
    // So we have to initialize it
    // Nice dude!

    masterCntrlPort.outb(0x11);
    slaveCntrlPort.outb(0x11);

    masterDataPort.outb(32);
    slaveDataPort.outb(40);

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
    dest.outb(dest.inb() & !(1 << tmp));
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

/** \todo \~german implementieren \~english write implementation*/
void PIC::ack(bool secondPIC){
}

/** \todo \~german implementieren \~english write implementation*/
unsigned char PIC::getISR(bool secondPIC){
  ///todo remove dummy
  return 0;
}
