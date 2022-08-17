#include "me_adasdead_WTools_wTerminal.h"

#include "wtools/wterminal.h"

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wTerminal_write
  (JNIEnv *env, jclass clz, jstring text)
{
    w_castr_t str = (*env)->GetStringUTFChars(env, text, NULL);

    if (str)
        w_terminal_write(str);
}

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wTerminal_writeLine
  (JNIEnv *env, jclass clz, jstring text)
{
    w_castr_t str = (*env)->GetStringUTFChars(env, text, NULL);

    if (str)
        w_terminal_writeln(str);
}

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wTerminal_setOutColor
  (JNIEnv *env, jclass clz, jshort color)
{
    w_terminal_set_out_color(color);
}

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wTerminal_resetColor
  (JNIEnv *env, jclass text)
{
    w_terminal_reset_color();
}