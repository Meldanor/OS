/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                      O _ S T R E A M                                          *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "object/o_stream.h"

O_Stream::O_Stream() : Stringbuffer() {
    // Standard base is decimal
    base = O_Stream::dec;
}

O_Stream::~O_Stream(){
}

O_Stream& O_Stream::operator << (char value) {
    // Print the value 
    put(value);
    return *this;
}

O_Stream& O_Stream::operator << (unsigned char value) {
    // Print the value
    put(value);
    return *this;
}
    
O_Stream& O_Stream::operator << (char* value) {
    // Print the null terminated string
    for (char* tmp = value; *tmp != '\0'; ++tmp) {
        put (*tmp);
    }
    return *this;
}

O_Stream& O_Stream::operator << (const char* value) {
    // Print the null terminated string
    for (char* tmp = (char*)value; *tmp != '\0'; ++tmp) {
        put (*tmp);
    }
    return *this;
}

O_Stream& O_Stream::operator << (short value) {
    // Check if negative - start with a '-' and convert number to positive
    if (value < 0) {
        put('-');
        value *= -1;
    }
    convertNumber((unsigned short)value);
    return *this;
}

O_Stream& O_Stream::operator << (unsigned short value) {
    convertNumber(value);
    return *this;
}

O_Stream& O_Stream::operator << (int value) {
    // Check if negative - start with a '-' and convert number to positive
    if (value < 0) {
        put('-');
        value *= -1;
    }
    convertNumber((unsigned int)value);
    return *this;
}

O_Stream& O_Stream::operator << (unsigned int value) {
    convertNumber(value);
    return *this;
}

O_Stream& O_Stream::operator << (long value) {
    // Check if negative - start with a '-' and convert number to positive
    if (value < 0) {
        put('-');
        value *= -1;
    }
    convertNumber((unsigned long)value);
    return *this;
}

O_Stream& O_Stream::operator << (unsigned long value) {
    convertNumber(value);
    return *this;
}

// The followning functions convert the value to a printable string
// Every function convert the value to the string in the current base , but reversed.
// The reversed string is temponary saved into an array (which size is the max count of binary)
// After the convertion the reversed string will be reversed printed

void O_Stream::convertNumber(unsigned short value) {
    printPrefix();
    if (base != O_Stream::hex && value == 0) {
        put('0');
    }
    int n = 0;
    while (value > 0) {
        numberBuffer[n++] = value % base;
        value = value / base;
    }
    --n;
    if (base == O_Stream::hex) {
        for (int j = 3 - n; j > 0; --j)
            put('0');
    }
    for (; n >= 0; --n) {
        printNumber(numberBuffer[n]);
    }
}

void O_Stream::convertNumber(unsigned int value) {
    printPrefix();
    if (base != O_Stream::hex && value == 0) {
        put('0');
    }
    int n = 0;
    while (value > 0) {
        numberBuffer[n++] = value % base;
        value = value / base;
    }
    --n;
    if (base == O_Stream::hex) {
        for (int j = 7 - n; j > 0; --j)
            put('0');
    }
    for (; n >= 0; --n) {
        printNumber(numberBuffer[n]);
    }
}

void O_Stream::convertNumber(unsigned long value) {
    printPrefix();
    if (base != O_Stream::hex && value == 0) {
        put('0');
    }
    int n = 0;
    while (value > 0) {
        numberBuffer[n++] = value % base;
        value = value / base;
    }
    --n;
    if (base == O_Stream::hex) {
        for (int j = 15 - n; j > 0; --j)
            put('0');
    }
    for (; n >= 0; --n) {
        printNumber(numberBuffer[n]);
    }
}

void O_Stream::printNumber(unsigned char number) {
    // For number 0 - 9
    if (number < 10) {
        put('0' + number);
    }
    // For hexadecimal representation
    else {
        put('A' + (number - 10));
    }
}

void O_Stream::printPrefix() {
    switch (base) {
        case O_Stream::bin:
            // Do nothing
            break;
        case O_Stream::oct:
            put('0');
            break;
        case O_Stream::dec:
            // Do nothing
            break;
        case O_Stream::hex:
            put('0');
            put('x');
            break;
    }
}

O_Stream& O_Stream::operator << (void* value) {
    for (char* tmp = (char*)value; *tmp != '\0'; ++tmp) {
        put (*tmp);
    }
    return *this;
}

O_Stream& O_Stream::operator << (FGColor fgColor) {
    curFGColor = fgColor.color;
    flush();
    setAttributes(curFGColor, curBGColor , isBlinking);
    return *this;
}

O_Stream& O_Stream::operator << (BGColor bgColor) {  
    curBGColor = bgColor.color;
    flush();
    setAttributes(curFGColor, curBGColor , isBlinking);
    return *this;
}

O_Stream& O_Stream::operator << (Blink blink) {
    isBlinking = blink.blink;
    flush();
    setAttributes(curFGColor, curBGColor , isBlinking);
    return *this;
}

O_Stream& endl (O_Stream& os) {
    os.put('\n');
    os.flush();
    return os;
}

O_Stream& bin (O_Stream& os) {
    os.base = O_Stream::bin;
    return os;
}

O_Stream& oct (O_Stream& os) {
    os.base = O_Stream::oct;
    return os;
}

O_Stream& dec (O_Stream& os) {
    os.base = O_Stream::dec;
    return os;
}

O_Stream& hex (O_Stream& os) {
    os.base = O_Stream::hex;
    return os;
}

O_Stream& O_Stream::operator << (O_Stream& (*f) (O_Stream&)) {
    return f(*this);
}
