/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         T H R E A D                                           *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   INCLUDES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/thread.h"
#include "useful/scheduler.h"
#include "useful/kout.h"
#include <ucontext.h>

const unsigned int STACK_SIZE = 1024*1024;

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   METHODS                       #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/**\~english \todo implement**/
void Thread::kickoff(Thread* thread){
    thread->action();
    thread->exit();
}

Thread::Thread() {
    if(getcontext(&context) == -1)
        kout << "getContext Error in Thread!" << endl;
    //Bereitstellung des Stacks
    context.uc_stack.ss_sp = stack;
    context.uc_stack.ss_size = STACK_SIZE;
    
    //Successor-Context
    context.uc_link = NULL;
    makecontext(&context,(void(*)())&Thread::kickoff,1,this);
}

Thread::~Thread(){
    //scheduler.kill(*this);
}

/**\~english \todo implement**/
void Thread::resume() {

    scheduler.resume();
}

/**\~english \todo implement**/
void Thread::exit(){
    scheduler.exit();
}
