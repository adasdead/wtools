#include "wtools/wmouse.h"

void w_mouse_click(w_mbutton_t button)
{
    w_pos_t pos = w_mouse_get_cursor_pos();

    INPUT inputs[3] = {0};
    
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags |= MOUSEEVENTF_ABSOLUTE;
    inputs[0].mi.dx = pos.x;
    inputs[0].mi.dy = pos.y;

    inputs[1].type = INPUT_MOUSE;
    
    if (button == W_MOUSE_LEFT_BUTTON)
        inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    else if (button == W_MOUSE_RIGHT_BUTTON)
        inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    inputs[2].type = INPUT_MOUSE;

    if (button == W_MOUSE_LEFT_BUTTON)
        inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    else if (button == W_MOUSE_RIGHT_BUTTON)
        inputs[2].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    SendInput(3, inputs, sizeof(INPUT));
}

void w_mouse_set_cursor_pos(w_pos_t pos)
{
    SetCursorPos(pos.x, pos.y);
}

w_pos_t w_mouse_get_cursor_pos(void)
{
    POINT cursor;
	GetCursorPos(&cursor);
    
    return (w_pos_t) { cursor.x, cursor.y };
}