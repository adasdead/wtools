#include "me_adasdead_WTools_wNotifications.h"

#include "wtools/wnotifications.h"

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wNotifications_notify
  (JNIEnv *env, jclass clz, jstring msg, jstring text)
{
    w_castr_t message = (*env)->GetStringUTFChars(env, msg, NULL);
    w_castr_t _text = (*env)->GetStringUTFChars(env, text, NULL);

    if (message && _text)
        w_notifications_notify(message, _text);
}