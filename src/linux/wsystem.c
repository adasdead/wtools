#include "wtools/wsystem.h"

#include <unistd.h>

void w_system_reboot(void)
{
    execl("/bin/shutdown", "shutdown", "-r", "now", (char *)0);
}

void w_system_shutdown(void)
{
    execl("/bin/shutdown", "shutdown", "-P", "now", (char *)0);
}