/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         S C H E D U L E R                                     *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   INCLUDES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "thread/scheduler.h"
#include "useful/kout.h"
#include "thread/lock.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   METHODS                       #
\* * * * * * * * * * * * * * * * * * * * * * * * */

void Scheduler::schedule(Thread& first) {

    Lock lock;
    go(first);
    if (!threads.empty()) {
        // dispatch(*threads.front());
        Thread* next = threads.front();
        threads.pop_front();
        dispatch(*next); 
    }
}

void Scheduler::ready(Thread& that) {
    Lock lock;
    threads.push_back(&that);
}

void Scheduler::exit() {

    Lock lock;

    if (threads.empty()) {
        while(true) {
            kout << "NixZuTun" << endl;
        }
    }
    else {
        Thread* next = threads.front();
        threads.pop_front();
        dispatch(*next);
    }
}

void Scheduler::kill(Thread& that) {

    Lock lock;

    for (ThreadIterator iter = threads.begin(); iter != threads.end() ; ++iter) {
        Thread* thread = *iter;
        if (thread == &that) {
            threads.erase(iter);
            break;
        }
    }
}

void Scheduler::resume() {

    Thread* next = active();
    {
        Lock lock;
        threads.push_back(active());
        next = threads.front();
        threads.pop_front();
    
    }
    dispatch(*next);
}
