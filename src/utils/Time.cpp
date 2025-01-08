#include "time.h"

#include <vmsys.h>
#include <vmtimer.h>

extern "C" {
#include <thread.h>
}

namespace Time {
int64_t currentTimeMillis()
{
    return vm_get_tick_count();
}

void sleep(int64_t ms)
{
    int64_t beg = currentTimeMillis();
    thread_next();
    while(currentTimeMillis() - beg < ms)
        thread_next();
}
}