#include "wtools/wterminal.h"

#include <stdio.h>
#include <string.h>

#include "wtools/wcore.h"

void w_terminal_write(w_castr_t text)
{
    if (!text) return;

    char out_buffer[WT_BUFFER_SIZE] = {'\0'};
    size_t out_buffer_len = 0;

    for (size_t i = 0; i < strlen(text); i++)
    {
        const char *cur_char = text + i;

        if (*cur_char == WT_COLOR_CHAR)
        {
            i++;

            printf(out_buffer);

            short color = w_terminal_char_to_color(*(cur_char + 1));

            w_terminal_set_out_color(color);

            memset(out_buffer, 0, WT_BUFFER_SIZE);
            
            out_buffer_len = 0;
            continue;
        }

        out_buffer[out_buffer_len] = *cur_char;
        out_buffer_len++;
    }

    printf(out_buffer);

    w_terminal_reset_color();
}

void w_terminal_writeln(w_castr_t text)
{
    w_terminal_write(text);
    w_terminal_write("\n");
}

void w_terminal_set_out_color(short color)
{
    printf("\033[0;%dm", color);
}

void w_terminal_reset_color(void)
{
    printf("\033[0m");
}