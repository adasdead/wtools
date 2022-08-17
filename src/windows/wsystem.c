#include "wtools/wsystem.h"

#define RtlAdjustPrivilege(privilege, enable, current_thread, old_val) \
    ((void(*)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN))                      \
        GetProcAddress(LoadLibraryA("ntdll"), "RtlAdjustPrivilege"))   \
        (privilege, enable, current_thread, old_val)

#define NtRaiseHardError(status, num_of_params, ustr_param_mask, params, options, response) \
    ((void(*)(LONG, ULONG, ULONG, PULONG_PTR, ULONG, PULONG))                               \
        GetProcAddress(LoadLibraryA("ntdll"), "NtRaiseHardError"))                          \
        (status, num_of_params, ustr_param_mask, params, options, response);

// https://docs.microsoft.com/en-us/windows/win32/shutdown/how-to-shut-down-the-system

static void w_process_privileges(void)
{
    HANDLE token;
	TOKEN_PRIVILEGES privileges;

	if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                          &token))
    {
        return;
    }

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
                         &privileges.Privileges[0].Luid);

	privileges.PrivilegeCount = 1;
	privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(token, FALSE, &privileges, 0,
                          (PTOKEN_PRIVILEGES)NULL, 0);
}

void w_system_reboot(void)
{
    w_process_privileges();
    ExitWindowsEx(EWX_REBOOT, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);
}

void w_system_shutdown(void)
{
    w_process_privileges();
    ExitWindowsEx(EWX_SHUTDOWN, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);
}

void w_system_bsod(long error_code)
{
    BOOLEAN old;
    ULONG response;
    
    RtlAdjustPrivilege(19, TRUE, FALSE, &old);
    NtRaiseHardError(error_code, 0, 0, NULL, 6, &response);
}