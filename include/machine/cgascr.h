/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                    C G A _ S C R E E N                                        *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __screen_include__
#define __screen_include__

/* INCLUDES */

#include "machine/io_port.h"

/** \brief CGA-Dispaly driver
 *
 * CGA_Screen enables the basic control of the screen of a computer by accessing
 * the screen memory and I/O ports directly.
 */
class CGA_Screen {
  private:
    
    
  protected:
    
  public:
    
    
    /** \brief Constructor 
     * 
     * \~
     * \todo write implementation
     **/
    CGA_Screen(){};
  
    /** \brief Destructor 
     * 
     * \~
     * \todo write implementation
     **/
    ~CGA_Screen(){};
    
    /** \brief set the cursor position
     *
     * @param x column number of new position 
     * @param y row number of new position
     * 
     * \~
     * \todo write implementation
     */
    void setpos(unsigned short x, unsigned short y);
    
    /** \brief get the cursor position
     *
     * @param x reference for column number of current position
     * @param y reference for row number of curent position
     * 
     * \~
     * \todo write implementation
     */
    void getpos(unsigned short& x, unsigned short& y) const;
    
    /** \brief print a character to a specific position
     *
     * @param x column number of display position
     * @param y row number of display position
     * @param c character to be displayed
     * @param attrib display attributs
     * 
     * \~
     * \todo write implementation
     */
    void show(unsigned short x, unsigned short y, char c, unsigned char attrib);
    
    /** \brief print a string to the current position
     * 
     * @param string string of characters to be displayed
     * @param n number auf characters in string
     * @param attrib display attributs
     * 
     * \~
     * \todo write implementation
     */
    void print(const char* string, unsigned int n, unsigned char attrib);
    
    /** \brief scroll the display one line upwards
     *
     * The new row at the bottom of the screen is filled with spaces.
     * 
     * \todo write implementation
     **/
    void scrollup();
    
    /** \brief clear the screen 
     * 
     * \~
     * \todo write implementation
     **/
    void clear();
    
    /**
     * \~german 
     * \brief setzt die Vordergrundfarbe für die nachfolgenden Zeichen
     * 
     * \~english
     * \brief set foreground color for following characters
     * 
     * \~
     * \todo write implementation
     */
    void setFGColor(unsigned char fgColor);
    
    /**
     * \~german 
     * \brief setzt die Hintergrundfarbe für die nachfolgenden Zeichen
     * 
     * \~english
     * \brief set background color for following characters
     * 
     * \~
     * \todo write implementation
     */
    void setBGColor(unsigned char bgColor);
    
    /**
     * \~german 
     * \brief setzt das Blinken für die nachfolgenden Zeichen
     * 
     * \~english
     * \brief set blinking for following characters
     * 
     * \~
     * \todo write implementation
     */
    void setBlink(unsigned char blink);
    
    /**
     * \~german 
     * \brief setzt die Attribute (alle) für die nachfolgenden Zeichen
     * 
     * \~english
     * \brief set all attributes for following characters
     * 
     * \~
     * \todo write implementation
     */
    void setDefaultAttrib(unsigned char attrib);
};

#endif
