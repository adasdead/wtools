#include "wtools/wterminal.h"
#include "wtools/wmsgbox.h"

int main(int argc, char *argv[])
{
    char name[W_MSGBOX_INPUT_SIZE];

    w_msgbox_prompt_ex("Enter your name:", "Name", "Roman",
                       (w_castr_2_t) { "OK", "Cancel" },
                       name, W_MSGBOX_TITLE_SIZE);

    w_msgbox_alert(name, "Your name:", "Wow");

    w_terminal_writeln("\\aCompleted!");
    return 0;
}

W_WIN32_MAIN_ARGS(main)