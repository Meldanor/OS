/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                         W A T C H                                             *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   INCLUDES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "device/watch.h"
#include <pthread.h>

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                GLOBAL OBJECTS                   #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "useful/kout.h"
#include "useful/pic.h"
#include "useful/plugbox.h"
#include "useful/scheduler.h"

extern volatile unsigned int rrTimeSlice;
extern pthread_mutex_t tsMutex;

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   METHODS                       #
\* * * * * * * * * * * * * * * * * * * * * * * * */

Watch::Watch(unsigned int us) : Gate()
{
    // ????
    pthread_mutex_lock(&tsMutex);
    rrTimeSlice=us;
    pthread_mutex_unlock(&tsMutex);
}

/**\~english \todo implement**/
void Watch::windup() {
    plugbox.assign(Plugbox::timer,*this);
    pic.allow(pic.timer);
}

/**\~english \todo implement**/
void Watch::trigger() {
    scheduler.resume();
}
 
