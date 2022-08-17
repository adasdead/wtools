#include "wtools/wterminal.h"

#include "wtools/wcore.h"

static HANDLE                       _handle = NULL;

static short w_ascii_clr_to_win_clr(short clr)
{
    switch (clr)
    {
    case WT_COLOR_BLACK:            return 0;
    case WT_COLOR_BLUE:             return 1;
    case WT_COLOR_GREEN:            return 2;
    case WT_COLOR_CYAN:             return 3;
    case WT_COLOR_RED:              return 4;
    case WT_COLOR_MAGENTA:          return 5;
    case WT_COLOR_YELLOW:           return 6;
    case WT_COLOR_WHITE:            return 7;
    case WT_COLOR_GRAY:             return 8;
    case WT_COLOR_BIRGHT_BLUE:      return 9;
    case WT_COLOR_BIRGHT_GREEN:     return 10;
    case WT_COLOR_BIRGHT_CYAN:      return 11;
    case WT_COLOR_BIRGHT_RED:       return 12;
    case WT_COLOR_BIRGHT_MAGENTA:   return 13;
    case WT_COLOR_BIRGHT_YELLOW:    return 14;
    case WT_COLOR_BIRGHT_WHITE:     return 15;

    default:                        return clr;
    }
}

static void w_console_write(w_castr_t text)
{
    wchar_t wtext[WT_BUFFER_SIZE] = {L""};
    w_ascii_to_utf16le(wtext, text, strlen(text));

    WriteConsoleW(_handle, wtext, (DWORD)wcslen(wtext),
                  NULL, NULL);
}

void w_terminal_write(w_castr_t text)
{
    if (!text) return;

    if (!_handle)
        _handle = GetStdHandle(STD_OUTPUT_HANDLE);

    char out_buffer[WT_BUFFER_SIZE] = {'\0'};
    size_t out_buffer_len = 0;

    for (size_t i = 0; i < strlen(text); i++)
    {
        const char *cur_char = text + i;

        if (*cur_char == WT_COLOR_CHAR)
        {
            i++;

            w_console_write(out_buffer);

            short color = w_terminal_char_to_color(*(cur_char + 1));

            w_terminal_set_out_color(color);

            memset(out_buffer, 0, WT_BUFFER_SIZE);
            
            out_buffer_len = 0;
            continue;
        }

        out_buffer[out_buffer_len] = *cur_char;
        out_buffer_len++;
    }

    w_console_write(out_buffer);
    w_terminal_reset_color();
}

void w_terminal_writeln(w_castr_t text)
{
    if (!text) return;

    size_t len = sizeof(char) * (strlen(text) + 2);

    w_astr_t buffer = malloc(len);
    
    strncpy(buffer, text, len);

    buffer[len - 2] = '\n';
    buffer[len - 1] = '\0';

    w_terminal_write(buffer);

    free(buffer);
}

void w_terminal_set_out_color(short color)
{
    if (!_handle)
        _handle = GetStdHandle(STD_OUTPUT_HANDLE);

    short winclr = w_ascii_clr_to_win_clr(color);

    SetConsoleTextAttribute(_handle, winclr);
}

void w_terminal_reset_color(void)
{
    if (!_handle)
        _handle = GetStdHandle(STD_OUTPUT_HANDLE);

    w_terminal_set_out_color(FOREGROUND_BLUE  |
                             FOREGROUND_GREEN |
                             FOREGROUND_RED);
}