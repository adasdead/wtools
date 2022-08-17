#include "me_adasdead_WTools_wMouse.h"

#include "wtools/wmouse.h"

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wMouse_click
  (JNIEnv *env, jclass clz, jshort button)
{
    w_mouse_click(button);
}

JNIEXPORT jintArray JNICALL Java_me_adasdead_WTools_wMouse__1getPosition
  (JNIEnv *env, jclass clz)
{
    w_pos_t pos = w_mouse_get_cursor_pos();
    int array[2] = { pos.x, pos.y };

    jintArray jarr = (*env)->NewIntArray(env, 2);
    (*env)->SetIntArrayRegion(env, jarr, 0, 2, (const jint*) array);

    return jarr;
}

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wMouse_setPosition
  (JNIEnv *env, jclass clz, jint x, jint y)
{
    w_mouse_set_cursor_pos((w_pos_t) { x, y });
}