#include "wtools/wmouse.h"

#include <X11/Xlib.h>

void w_mouse_click(w_mbutton_t button)
{
    XButtonEvent event = {0};

    Display *dpy = XOpenDisplay(0);

    switch (button)
    {
    case W_MOUSE_LEFT_BUTTON:
        button = Button1;
        break;
    
    case W_MOUSE_RIGHT_BUTTON:
        button = Button2;
        break;
    }

    event.same_screen = 1;
    event.type = ButtonPress;
    event.subwindow = DefaultRootWindow(dpy);

    while (event.subwindow)
    {
        event.window = event.subwindow;

        XQueryPointer(dpy, event.window,
                      &event.root, &event.subwindow,
                      &event.x_root, &event.y_root,
                      &event.x, &event.y,
                      &event.state);
    }

    for (int i = ButtonPress; i <= ButtonRelease; i++)
    {
        event.type = i;

        XSendEvent(dpy, PointerWindow, True,
                   ButtonPressMask, (XEvent *)&event);

        XFlush(dpy);
    }
}

void w_mouse_set_cursor_pos(w_pos_t pos)
{
    w_pos_t last_pos;
    last_pos = w_mouse_get_cursor_pos();

    Display *dpy = XOpenDisplay(0);

    XWarpPointer(dpy, None, None, 0, 0,
                0, 0, pos.x, pos.y);

    XFlush(dpy);
}

w_pos_t w_mouse_get_cursor_pos(void)
{
    XButtonEvent b_event;

    w_pos_t pos = {0};

    Display *dpy = XOpenDisplay(0);

    XQueryPointer(dpy, DefaultRootWindow(dpy),
                  &b_event.root, &b_event.window,
                  &b_event.x_root, &b_event.y_root,
                  &pos.x, &pos.y, &b_event.state);

    return pos;
}