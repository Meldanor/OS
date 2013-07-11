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

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   METHODS                       #
\* * * * * * * * * * * * * * * * * * * * * * * * */

void Scheduler::schedule(Thread& first) {

    go(first);
    if (!threads.empty()) {
        // dispatch(*threads.front());
        Thread* next = threads.front();
        threads.pop_front();
        dispatch(*next); 
    }
}

void Scheduler::ready(Thread& that) {
    threads.push_back(&that);
}

void Scheduler::exit() {
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
    for (ThreadIterator iter = threads.begin(); iter != threads.end() ; ++iter) {
        Thread* thread = *iter;
        if (thread == &that) {
            threads.erase(iter);
            break;
        }
    }
}

void Scheduler::resume() {

    threads.push_back(active());
    Thread* next = threads.front();
    threads.pop_front();
    dispatch(*next);
}
