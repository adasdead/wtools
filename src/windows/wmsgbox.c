#include "wtools/wmsgbox.h"

#include "wtools/wterminal.h"

#define IDPROMPTEDIT            47
#define IDPROMPTSTATIC          48

static HHOOK                  _hook;

static wchar_t                _buttons[2][W_MSGBOX_INPUT_SIZE];
static wchar_t                _prompt_text[W_MSGBOX_TEXT_SIZE];
static wchar_t                _prompt_input[W_MSGBOX_INPUT_SIZE];

static LPCWSTR                _promt_clz_name = L"PROMPTCLZ";

static LRESULT CALLBACK w_msgbox_proc(INT code,
                                      WPARAM w_param,
                                      LPARAM l_param)
{
    HWND child_hwnd;

    if (code == HCBT_ACTIVATE)
    {
        child_hwnd = (HWND) w_param;

        if (GetDlgItem(child_hwnd, IDOK))
            SetDlgItemTextW(child_hwnd, IDOK, _buttons[0]);

        if (GetDlgItem(child_hwnd, IDCANCEL))
            SetDlgItemTextW(child_hwnd, IDCANCEL, _buttons[1]);

        UnhookWindowsHookEx(_hook);
    }
    else
        CallNextHookEx(_hook, code, w_param, l_param);

    return 0;
}

static LRESULT CALLBACK w_promt_proc(HWND hwnd,
                                     UINT msg,
                                     WPARAM w_param,
                                     LPARAM l_param)
{
    switch(msg)
    {
    case WM_CREATE:
        WPARAM font = (WPARAM) GetStockObject(DEFAULT_GUI_FONT);
        
        CreateWindowW(L"button", _buttons[0], WS_VISIBLE | WS_CHILD,
                      270, 10, 75, 25, hwnd, (HMENU) IDOK, NULL,
                      NULL);

        CreateWindowW(L"button", _buttons[1], WS_VISIBLE | WS_CHILD,
                      270, 40, 75, 25, hwnd, (HMENU) IDCANCEL, NULL,
                      NULL);

        CreateWindowW(L"edit", L"", WS_BORDER | WS_CHILD |
                      WS_VISIBLE, 10, 100, 335, 20,
                      hwnd, (HMENU) IDPROMPTEDIT, NULL, NULL);

        CreateWindowW(L"static", _prompt_text, SS_EDITCONTROL |
                      WS_CHILD | WS_VISIBLE, 10, 10, 250, 80,
                      hwnd, (HMENU) IDPROMPTSTATIC, NULL, NULL);

        SendMessage(GetDlgItem(hwnd, IDOK), WM_SETFONT, font, TRUE);
        SendMessage(GetDlgItem(hwnd, IDCANCEL), WM_SETFONT, font, TRUE);
        SendMessage(GetDlgItem(hwnd, IDPROMPTEDIT), WM_SETFONT, font, TRUE);
        SendMessage(GetDlgItem(hwnd, IDPROMPTSTATIC), WM_SETFONT, font, TRUE);

        SendMessage(hwnd, DM_SETDEFID, (WPARAM) IDOK, (LPARAM) 0); 

        SetDlgItemTextW(hwnd, IDPROMPTEDIT, _prompt_input);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_PAINT:
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW));
        EndPaint(hwnd, &ps);
        break;

    case WM_COMMAND:
        GetDlgItemTextW(hwnd, IDPROMPTEDIT, _prompt_input,
                        W_MSGBOX_INPUT_SIZE);
        
        switch (w_param)
        {        
        case IDCANCEL:
            wmemset(_prompt_input, 0, W_MSGBOX_INPUT_SIZE);

        case IDOK:
            DestroyWindow(hwnd);
        }

        break;

    case WM_CLOSE:
        wmemset(_prompt_input, 0, W_MSGBOX_INPUT_SIZE);
        DestroyWindow(hwnd);
        break;
    }
  
  return DefWindowProcW(hwnd, msg, w_param, l_param);
}

static void w_register_prompt_class(void)
{
    WNDCLASSEXW wc = {0};

    wc.cbSize        = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc   = (WNDPROC) w_promt_proc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.lpszClassName = _promt_clz_name;

    RegisterClassExW(&wc);
}

void w_msgbox_alert(w_castr_t text, w_castr_t title,
                    w_castr_t button)
{
    wchar_t _text[W_MSGBOX_TEXT_SIZE], _title[W_MSGBOX_TITLE_SIZE];

    if (!(text && title && button)) return;

    w_ascii_to_utf16le(_text, text, W_MSGBOX_TEXT_SIZE);
    w_ascii_to_utf16le(_title, title, W_MSGBOX_TITLE_SIZE);
    w_ascii_to_utf16le(_buttons[0], button, W_MSGBOX_BUTTON_TEXT_SIZE);

    _hook = SetWindowsHookEx(WH_CBT, &w_msgbox_proc,
                             NULL, GetCurrentThreadId());

    MessageBoxW(NULL, _text, _title, MB_OK);
}

w_clicked_t w_msgbox_confirm(w_castr_t text, w_castr_t title,
                             w_castr_2_t btns)
{
    wchar_t _text[W_MSGBOX_TEXT_SIZE], _title[W_MSGBOX_TITLE_SIZE];

    if (!(text && title && btns)) return W_ERR;

    w_ascii_to_utf16le(_text, text, W_MSGBOX_TEXT_SIZE);
    w_ascii_to_utf16le(_title, title, W_MSGBOX_TITLE_SIZE);

    w_ascii_to_utf16le(_buttons[0], btns[0], W_MSGBOX_BUTTON_TEXT_SIZE);
    w_ascii_to_utf16le(_buttons[1], btns[1], W_MSGBOX_BUTTON_TEXT_SIZE);

    _hook = SetWindowsHookEx(WH_CBT, &w_msgbox_proc, 0,
                             GetCurrentThreadId());

    int result = MessageBoxW(NULL, _text, _title, MB_OKCANCEL);

    return (result == IDOK) ? W_MSGBOX_BUTTON_1 : W_MSGBOX_BUTTON_2;
}

void w_msgbox_prompt(w_castr_t text, w_castr_t title,
                     w_astr_t out, size_t size)
{
    w_castr_2_t buttons = {"OK", "Cancel"};
    w_msgbox_prompt_ex(text, title, "", buttons, out, size);
}

void w_msgbox_prompt_ex(w_castr_t text, w_castr_t title,
                        w_castr_t def, w_castr_2_t btns,
                        w_astr_t out, size_t size)
{
    w_register_prompt_class();

    wchar_t _title[W_MSGBOX_TITLE_SIZE];

    if (!(text && title)) return;

    w_ascii_to_utf16le(_prompt_text, text, W_MSGBOX_TEXT_SIZE);
    w_ascii_to_utf16le(_title, title, W_MSGBOX_TITLE_SIZE);
    w_ascii_to_utf16le(_prompt_input, def, W_MSGBOX_INPUT_SIZE);

    w_ascii_to_utf16le(_buttons[0], btns[0], W_MSGBOX_BUTTON_TEXT_SIZE);
    w_ascii_to_utf16le(_buttons[1], btns[1], W_MSGBOX_BUTTON_TEXT_SIZE);

    CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,
                    _promt_clz_name, _title, 
                    WS_VISIBLE | WS_SYSMENU | WS_CAPTION,
                    CW_USEDEFAULT, CW_USEDEFAULT, 370, 170,
                    NULL, NULL, GetModuleHandle(NULL), NULL);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
        TranslateMessage(&msg);
    }

    w_utf16le_to_ascii(out, _prompt_input, size);
}