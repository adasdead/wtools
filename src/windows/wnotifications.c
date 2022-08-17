#include "wtools/wnotifications.h"

w_result_t w_notifications_notify(w_castr_t message, w_castr_t title)
{
    wchar_t _message[256], _title[64];

    if (!(message && title)) return W_ERR;

    w_ascii_to_utf16le(_message, message, 256);
    w_ascii_to_utf16le(_title, title, 64);

    NOTIFYICONDATAW nid = {0};

    nid.cbSize = sizeof(nid);
    nid.hWnd = GetForegroundWindow();
    nid.uVersion = NOTIFYICON_VERSION_4;
    nid.uFlags = NIF_INFO;

    wcsncpy(nid.szInfoTitle, _title, 64);
    wcsncpy(nid.szInfo, _message, 256);

    w_result_t result;
    result = Shell_NotifyIconW(NIM_ADD, &nid);
    Shell_NotifyIconW(NIM_DELETE, &nid);

    return (result == S_OK) ? W_OK : W_ERR;
}