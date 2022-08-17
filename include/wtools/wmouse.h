#ifndef WTOOLS_WMOUSE_H
#define WTOOLS_WMOUSE_H

#include "wcore.h"

#define W_MOUSE_RIGHT_BUTTON    0
#define W_MOUSE_LEFT_BUTTON     1

struct _w_pos
{
    unsigned int x, y;
};

typedef struct _w_pos w_pos_t;
typedef short w_mbutton_t;

void w_mouse_click(w_mbutton_t button);
void w_mouse_set_cursor_pos(w_pos_t pos);
w_pos_t w_mouse_get_cursor_pos(void);

#endif // WTOOLS_WMOUSE_H