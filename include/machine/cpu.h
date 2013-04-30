/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                           C P U                                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __CPU_include__
#define __CPU_include__

/** \brief Hardware accessor for %CPU specific instructions
 *
 * Class CPU implements an abstraction of the processor. It provides methods to
 * enable/disable interrupts globally and to halt the processor.
 */
class CPU {
  private:
    int iIFlag;
    
  public:
    
    /**
     * \~german
     * \brief ...
     * 
     * \~english
     * \brief ...
     **/
    CPU():iIFlag(0){
      
    }
    
    /** \brief globally enable interrupts **/
    inline void enable_int () {
      asm(
        "movl $0x0200, %0 \n\t"
        "sti \n\t"
        :"=r"(iIFlag)
      );
    }
    
    /** \brief globally dissable interrupts **/
    inline void disable_int () {
      asm(
        "pushf\n\t"
        "cli\n\t"
        "movl (%%esp), %0\n\t"
        "add $4, %%esp \n\t"
        :"=r"(iIFlag)
      );
    }
    
    /** \brief restore old state of interrupt **/
    inline void retore_interrupt_state () {
      asm(
        "cli \n\t"
        "andl $0x0200, %0 \n\t"
        "pushf \n\t"
        "orl %0, (%%esp) \n\t"
        "popf \n\t"
        :
        :"r"(iIFlag)
      );
    }
    
    /** \brief halt the cpu
     *
     * When the cpu is halted the program counter will not increase until an
     * interrupt occurs.  If an interrupt occurs the cpu will handle the
     * interrupt and continue with the execution after the halt command.
     */
    inline void halt () {
      asm("hlt");
    }
};

#endif
