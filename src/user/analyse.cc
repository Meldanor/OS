
#include "user/analyse.h"
#include "useful/kout.h"
#include "useful/cpu.h"

/** \brief 
 *    \~english analyse function for exception
 *    \~german  Funktion zur Analyse einer Fehlerbehandlungsroutine.
 * 
 * \~
 * \param[in] slot
 *   \~english
 *   This is the interrupt ID, hence the same parameter as \ref guardian.
 *   \~german
 *   Dies ist die ID des Interrupts, wie er auch der Funktion \ref guardian übergeben worden wäre.
 * 
 * \~
 * \param[in] esp
 *   \~english
 *   This is the pointer to the top of the stack as it would be at the start of function
 *   \ref handleException. No code of the function is been executed thus the esp is in a status
 *   of never touched by the function itself.
 *   \~german
 *   Dieser Zeiger geht auf den Anfang des Stacks, wie er beim Aufruf der Funktion 
 *   \ref handleException wäre. Zu dem festgehaltenem Zeitpunkt wurde zwar die Funktion schon 
 *   aufgerufen, es wurde aber noch keine einzige Zeile abgearbeitet. Die Funktion selber hat
 *   den Stack also noch nicht verändert.
 *   
 *   
 * \~
 * \todo \~german den markierten ToDo-Bereich ausfüllen \~english fill in the todo area
 */
void analyseException(unsigned short slot, void** esp){
  //Ausgabe, was passiert ist
  kout << endl;
  kout << "analyseException(" << slot << ", " << esp << ") called" << endl;
  
  /* * * * * * * * * * * * * * * * * * *\
  # Start ToDo-Bereich                  #
  \* * * * * * * * * * * * * * * * * * */
    const char* error = "";
    switch(slot) {
        case 0: error = "Divide Error"; break;
        case 1: error = "Debug/Reserved for Intel"; break;
        case 2: error = "Nonmaskable Interrupt"; break;
        case 3: error = "Breakpoint"; break;
        case 4: error = "Overflow"; break;
        case 5: error = "Bound Range Exceeded"; break;
        case 6: error = "Invalid Opcoude Fault"; break;
        case 7: error = "Device Not Available"; break;
        case 8: error = "Double Fault"; break;
        case 9: error = "Reserved"; break;
        case 10: error = "Invalid TSS"; break;
        case 11: error = "Segment Not Present"; break;
        case 12: error = "Stack-Segment Fault"; break;
        case 13: error = "General Protection"; break;
        case 14: error = "Page Fault"; break;
        case 15: error = "Reserved For Intel"; break;
        case 16: error = "x87 FPU Floating-Point"; break;
        case 17: error = "Aligment Check"; break;
        case 18: error = "Machine Check"; break;
        case 19: error = "SIMD Floating-Point Exception"; break;
        case 20: error = "Virtualization Exception"; break;
        default: error = "Generic Error - Such dir was aus";
    }

    kout << error << endl;

    kout << hex;
    
    for (int i = 0 ; i < 6 ; ++i, ++esp) {
        void* tmp = *esp;
        kout << (unsigned int) tmp << "   " << endl;   
    }
    kout << dec;
  
  /* * * * * * * * * * * * * * * * * * *\
  #  Ende ToDo-Bereich                  #
  \* * * * * * * * * * * * * * * * * * */
  
  //und anhalten, damit nichts schlimmes passiert
  cpu.disable_int();
  cpu.halt();
}


/** \brief 
 *    \~english analyse function for procedure stack
 *    \~german  Diese Funktion dient der Analyse des Prozedurstacks.
 * 
 * \~english
 * The functions prints the first 60 32 bit words of the stack, 
 * four of them in one line, each.
 * \~german 
 * Es werden die ersten 60 32-Bit-Worte vom Stack ausgegeben. Dabei 
 * erscheinen je vier der Worte in einer Zeile.
 * 
 * \~
 * \param[in] esp
 *   \~english
 *   This is a pointer to the top of the stack as it would be in function \ref alphaAckermann
 *   of task3B.cc before calling gotoAnalyse.
 *   \~german
 *   Dis ist ein Zeiger auf den Anfang des Stacks. Er ist aufgebau*kurz 
 *   vor dem Aufruf der Funktion gotoAnalyse innerhalb von \ref alphaAckermann in 
 *   der Datei task3B.cc. Auf diese Weise kann der Prozedurstack gut analysiert werden.
 * 
 * \~
 * \todo \~german Funktion fuer Analyse ausfuellen. \~english fill in todo area
 */
void analyseProcedureStack(void** esp) {
  //Ausgabe, was passiert ist
  kout << endl;
  kout << "analyseProcedureStack(" << esp << ") called" << endl;
  
  /* * * * * * * * * * * * * * * * * * *\
  # Start ToDo-Bereich                  #
  \* * * * * * * * * * * * * * * * * * */
    kout << hex;
    for (int i = 0 ; i < 60 ; ++i, ++esp) {
        if (i % 4 == 0)
            kout << endl;
        void* tmp = *esp;
        kout << (unsigned int) tmp << "   ";   
    }
    kout << endl;
    kout << dec;

    /*
    Wiederholende Strukturen: Parameter und Frame
    Array: Aufbau ganz normal?
    Stack: OBen nach unten wachsend
    Rekursiontiefe: 4

    */
  /* * * * * * * * * * * * * * * * * * *\
  #  Ende ToDo-Bereich                  #
  \* * * * * * * * * * * * * * * * * * */
} 
