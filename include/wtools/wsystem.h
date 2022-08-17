#ifndef WTOOLS_WSYSTEM_H
#define WTOOLS_WSYSTEM_H

#include "wcore.h"

void w_system_reboot(void);
void w_system_shutdown(void);

#if _WIN32

void w_system_bsod(long error_code);

#endif // _WIN32

#endif // WTOOLS_WSYSTEM_H