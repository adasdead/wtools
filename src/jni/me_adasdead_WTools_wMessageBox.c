#include "me_adasdead_WTools_wMessageBox.h"

#include "wtools/wmsgbox.h"

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wMessageBox_rawAlert
  (JNIEnv *env, jclass clz, jstring text, jstring title, jstring btn)
{
    w_castr_t _title = (*env)->GetStringUTFChars(env, title, NULL);
    w_castr_t _text = (*env)->GetStringUTFChars(env, text, NULL);
    w_castr_t _btn = (*env)->GetStringUTFChars(env, btn, NULL);

    if (_title && _text && _btn)
        w_msgbox_alert(_text, _title, _btn);
}

JNIEXPORT jint JNICALL Java_me_adasdead_WTools_wMessageBox_rawConfirm
  (JNIEnv *env, jclass clz, jstring text, jstring title, jstring btn1, jstring btn2)
{
    w_castr_t _title = (*env)->GetStringUTFChars(env, title, NULL);
    w_castr_t _text = (*env)->GetStringUTFChars(env, text, NULL);
    w_castr_t _btn1 = (*env)->GetStringUTFChars(env, btn1, NULL);
    w_castr_t _btn2 = (*env)->GetStringUTFChars(env, btn2, NULL);

    if (_title && _text && _btn1 && _btn2)
    {
        w_astr_2_t btns;
        strncpy(btns[0], _btn1, W_MSGBOX_BUTTON_TEXT_SIZE);
        strncpy(btns[1], _btn2, W_MSGBOX_BUTTON_TEXT_SIZE);

        return w_msgbox_confirm(_text, _title, btns);
    }

    return W_ERR;
}

JNIEXPORT jstring JNICALL Java_me_adasdead_WTools_wMessageBox_rawPrompt
  (JNIEnv *env, jclass clz, jstring text, jstring title, jstring def,
   jstring btn1, jstring btn2)
{
    w_castr_t _title = (*env)->GetStringUTFChars(env, title, NULL);
    w_castr_t _text = (*env)->GetStringUTFChars(env, text, NULL);
    w_castr_t _def = (*env)->GetStringUTFChars(env, def, NULL);
    w_castr_t _btn1 = (*env)->GetStringUTFChars(env, btn1, NULL);
    w_castr_t _btn2 = (*env)->GetStringUTFChars(env, btn2, NULL);

    if (_title && _text && _def && _btn1 && _btn2)
    {
        w_astr_2_t btns;
        char output[W_MSGBOX_INPUT_SIZE];

        strncpy(btns[0], _btn1, W_MSGBOX_BUTTON_TEXT_SIZE);
        strncpy(btns[1], _btn2, W_MSGBOX_BUTTON_TEXT_SIZE);

        w_msgbox_prompt_ex(_text, _title, _def, btns,
                           output, W_MSGBOX_INPUT_SIZE);

        return (*env)->NewStringUTF(env, output);
    }

    return NULL;
}