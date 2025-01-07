#include "time.h"

#include <vmsys.h>

namespace Time {
int64_t currentTimeMillis()
{
    return vm_get_tick_count();
}

void sleep(int64_t ms)
{
    //SDL_Delay(ms);
}
}