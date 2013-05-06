/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                           K E Y B O A R D _ C O N T R O L L E R                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* INCLUDES */
#include "machine/keyctrl.h"
#include "machine/cpu.h"
#include "device/cgastr.h"

extern CPU cpu;

/* GLOBALE VARIABLS */

/* STATIC MEMERS   */
unsigned char Keyboard_Controller::normal_tab[] = {
  0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 225, 39, '\b',
  0, 'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', 129, '+', '\n',
  0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 148, 132, '^', 0, '#',
  'y', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0,
  '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-',
  0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, '<', 0, 0
};

unsigned char Keyboard_Controller::shift_tab[] = {
  0, 0, '!', '"', 21, '$', '%', '&', '/', '(', ')', '=', '?', 96, 0,
  0, 'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', 154, '*', 0,
  0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 153, 142, 248, 0, 39,
  'Y', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0,
  0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '>', 0, 0
};

unsigned char Keyboard_Controller::alt_tab[] = {
  0, 0, 0, 253, 0, 0, 0, 0, '{', '[', ']', '}', '\\', 0, 0,
  0, '@', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '~', 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 230, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '|', 0, 0
};

unsigned char Keyboard_Controller::asc_num_tab[] = {
  '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', ','
};

unsigned char Keyboard_Controller::scan_num_tab[] = {
  8, 9, 10, 53, 5, 6, 7, 27, 2, 3, 4, 11, 51
};

/* PRIVATE METHODS */
bool Keyboard_Controller::key_decoded () {
  bool done = false;
  
  // keys of MF II keyboards start sending one of two prefix bytes
  if (code == prefix1 || code == prefix2) { 
    prefix = code;
    return false;
  }
  
  // releasing a key is important for the modifier keys (SHIFT, CTRL, ALT, ...)
  // break codes from other keys are ignored
  if (code & break_bit) {
    // break code of a key is equal to the make code but additionaly the 
    // break_bit is set
    code &= ~break_bit;
    switch (code) {
      case 42:
      case 54:
        gather.shift (false);
        break;
      case 56:
        if (prefix == prefix1)
          gather.alt_right (false);
        else
          gather.alt_left (false);
        break;
      case 29:
        if (prefix == prefix1)
          gather.ctrl_right (false);
        else
          gather.ctrl_left (false);
        break;
    }
    
    // a prefix is only valid for the following code
    prefix = 0;
    
    // returns false since the break codes gives no additional information
    return false;
  }
  
  // a key has been pressed, if it was a modifier key like SHIFT, ALT, NUM_LOCK
  // eg. only the internal state is changed. Return value 'false' shows that 
  // the input is not finished yet. If other keys have been pressed the ASCII 
  // and Scancode is read and 'ture' is returned.
  switch (code) {
    case 42:
    case 54:
      gather.shift (true);
      break;
    case 56:
      if (prefix == prefix1)
        gather.alt_right (true);
      else
        gather.alt_left (true);
        break;
    case 29:
      if (prefix == prefix1)
        gather.ctrl_right (true);
      else
        gather.ctrl_left (true);
      break;
    case 58:
      gather.caps_lock (!gather.caps_lock ());
      set_led (caps_lock, gather.caps_lock());
      break;
    case 70:
      gather.scroll_lock (!gather.scroll_lock ());
      set_led (scroll_lock, gather.scroll_lock());
      break;
    case 69: // NUM_LOCK or BREAK ?
      if (gather.ctrl_left ()) {        // BREAK
        get_ascii_code ();
        done = true;
      } else {                          // NUM_LOCK
        gather.num_lock (!gather.num_lock());
        set_led (num_lock, gather.num_lock ());
      }
      break;
    default:                            // other keys
       // get ASCII codes from table, DONE
      get_ascii_code ();
      done = true;
  }
  
    // a prefix is only valid for the following code
  prefix = 0;
  
  if (done)
    return true;
  else
    return false;
}

/**
 * Determins the ASCII code of a key using the scancode and modifier bits.
 */
void Keyboard_Controller::get_ascii_code () {
  if (code == 53 && prefix == prefix1) { // special case scancode 53
    gather.ascii ('/');
    gather.scancode (Key::scan::div);
  } else if (gather.num_lock () && !prefix && code>=71 && code<=83) {
    gather.ascii (asc_num_tab[code-71]);
    gather.scancode (scan_num_tab[code-71]);
  } else if (gather.alt_right ()) {
    gather.ascii (alt_tab[code]);
    gather.scancode (code);
  } else if (gather.shift ()) {
    gather.ascii (shift_tab[code]);
    gather.scancode (code);
  } else if (gather.caps_lock ()) {
    if ((code>=16 && code<=26) || (code>=30 && code<=40)
        || (code>=44 && code<=50)) {
      gather.ascii (shift_tab[code]);
      gather.scancode (code);
    } else {
      gather.ascii (normal_tab[code]);
      gather.scancode (code);
    }
  } else {
    gather.ascii (normal_tab[code]);
    gather.scancode (code);
  }
}

/* PUBLIC METHODS */
Keyboard_Controller::Keyboard_Controller () : ctrl_port (0x64), data_port (0x60) {
  // switch all LEDs off (some PCs switch LEDs on)
  set_led (caps_lock, false);
  set_led (scroll_lock, false);
  set_led (num_lock, false);
  
  // set maximal speed and delay of keyboard
  set_repeat_rate (0, 0);
  
  while(true){
  unsigned char status=ctrl_port.inb();
  if(status&outb){
    data_port.inb();
    continue;
  }
  if(!(status&inpb))
    break;
  }
}

void Keyboard_Controller::reboot () {
  int status;
  
  // The BIOS has to be told that reset is real and no memory test.
  *(unsigned short*) 0x472 = 0x1234;
  
  // keyboard controller has to send a reset
  do {                                  // wait until last command was processed
    status = ctrl_port.inb ();
  } while ((status & inpb) != 0);
  ctrl_port.outb (cmd_cpu_reset);       // reset
}

Key Keyboard_Controller::key_hit () {

    // invalid default key
    Key invalid; 

    // Get the status of the keycontroller
    unsigned char status = ctrl_port.inb();
    // No key pressed or status is from the mouse -> 
    // Return invalid key
    if (!(status & outb) || (status & auxb)) {
        return invalid;
    }

    // Read data from the keyboard controller
    code = data_port.inb();

    // Decode the data from the keyboard controller
    if (!key_decoded())
        return invalid;

    // Map the decoded data to an ASCII char
    get_ascii_code();

    // Return the key
    return gather;
}

void Keyboard_Controller::set_repeat_rate (unsigned char speed, unsigned char delay) {

    while (ctrl_port.inb() & inpb) {
        // Wait until keyboard in buffer is empty
    }

    // Now the buffer is empty
    // Tell the keyboard controller, we want to update the speed and delay
    data_port.outb(cmd_set_speed);

    while (data_port.inb() != ack) {
        // Wait until the keyboard controller answer with an acknowledged
    }
    // Delete possible other bits
    speed &= 0x1F;
    delay &= 0x3;
    // Write new value to the controller
    data_port.outb(speed | (delay << 5));
}

void Keyboard_Controller::set_led (Leds led, bool on) {

    while (ctrl_port.inb() & inpb) {
        // Wait until keyboard in buffer is empty
    }

    // Now the buffer is empty
    // Tell the keyboard controller, we want to update the speed and delay
    data_port.outb(cmd_set_led);

    unsigned char status =0;
    do {
        status = ctrl_port.inb();
    } while ((status & outb) == 0);

    if (data_port.inb() == ack) {
        // Set the bit
        if (on) {
            leds |= led;
        }
        // Delete the bit
        else {
            leds &= ~(led);
        }
        // Write new led status
        data_port.outb(leds);

        // Leeren des Tastatur controller
        do {
            status = ctrl_port.inb();
        } while ((status & outb) == 0);

        data_port.inb();
    }

}
