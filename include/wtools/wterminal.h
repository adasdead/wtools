#ifndef WTOOLS_WTERMINAL_H
#define WTOOLS_WTERMINAL_H

#include "wcore.h"

#define WT_COLOR_CHAR           '\\'
#define WT_BUFFER_SIZE          1024

#define WT_COLOR_BLACK          30
#define WT_COLOR_RED            31
#define WT_COLOR_GREEN          32
#define WT_COLOR_YELLOW         33
#define WT_COLOR_BLUE           34
#define WT_COLOR_MAGENTA        35
#define WT_COLOR_CYAN           36
#define WT_COLOR_WHITE          37

#define WT_COLOR_GRAY           90
#define WT_COLOR_BIRGHT_RED     91
#define WT_COLOR_BIRGHT_GREEN   92
#define WT_COLOR_BIRGHT_YELLOW  93
#define WT_COLOR_BIRGHT_BLUE    94
#define WT_COLOR_BIRGHT_MAGENTA 95
#define WT_COLOR_BIRGHT_CYAN    96
#define WT_COLOR_BIRGHT_WHITE   97

static short w_terminal_char_to_color(char ch)
{
    switch (ch)
    {
    case '0': return WT_COLOR_BLACK;
    case '1': return WT_COLOR_RED;
    case '2': return WT_COLOR_GREEN;
    case '3': return WT_COLOR_YELLOW;
    case '4': return WT_COLOR_BLUE;
    case '5': return WT_COLOR_MAGENTA;
    case '6': return WT_COLOR_CYAN;
    case '7': return WT_COLOR_WHITE;
    case '8': return WT_COLOR_GRAY;
    case '9': return WT_COLOR_BIRGHT_RED;
    case 'a': return WT_COLOR_BIRGHT_GREEN;
    case 'b': return WT_COLOR_BIRGHT_YELLOW;
    case 'c': return WT_COLOR_BIRGHT_BLUE;
    case 'd': return WT_COLOR_BIRGHT_MAGENTA;
    case 'e': return WT_COLOR_BIRGHT_CYAN;
    case 'f': return WT_COLOR_BIRGHT_WHITE;
    }

    return WT_COLOR_BIRGHT_WHITE;
}

void w_terminal_write(w_castr_t text);
void w_terminal_writeln(w_castr_t text);

void w_terminal_set_out_color(short color);
void w_terminal_reset_color(void);

#endif // WTOOLS_WTERMINAL_H