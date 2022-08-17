#ifndef WTOOLS_WMSGBOX_H
#define WTOOLS_WMSGBOX_H

#include "wcore.h"

#define W_MSGBOX_BUTTON_1           0
#define W_MSGBOX_BUTTON_2           1

#define W_MSGBOX_BUTTON_TEXT_SIZE   64
#define W_MSGBOX_TEXT_SIZE          1024
#define W_MSGBOX_TITLE_SIZE         256
#define W_MSGBOX_INPUT_SIZE         256

typedef short w_clicked_t;
typedef char w_astr_2_t[2][W_MSGBOX_BUTTON_TEXT_SIZE];
typedef const w_astr_2_t w_castr_2_t;

void w_msgbox_alert(w_castr_t text, w_castr_t title, w_castr_t button);
w_clicked_t w_msgbox_confirm(w_castr_t text, w_castr_t title, w_castr_2_t btns);
void w_msgbox_prompt(w_castr_t text, w_castr_t title, w_astr_t out, size_t size);
void w_msgbox_prompt_ex(w_castr_t text, w_castr_t title, w_castr_t def, w_castr_2_t btns, w_astr_t out, size_t size);

#endif // WTOOLS_WMSGBOX_H