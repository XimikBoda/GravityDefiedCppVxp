#include "time.h"

#include <vmsys.h>
#include <vmtimer.h>

extern "C" {
#include <thread.h>
}

static void timer(int timer_id) {
    vm_delete_timer(timer_id);

    thread_next();
}

namespace Time {
int64_t currentTimeMillis()
{
    return vm_get_tick_count();
}

void sleep(int64_t ms)
{
    vm_create_timer(ms, timer);

    thread_next();
    //SDL_Delay(ms);
}
}