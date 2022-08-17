#include "me_adasdead_WTools_wSystem.h"

#include "wtools/wsystem.h"

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wSystem_reboot
  (JNIEnv *env, jclass clz)
{
    w_system_reboot();
}

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wSystem_shutdown
  (JNIEnv *env, jclass clz)
{
    w_system_shutdown();
}

JNIEXPORT void JNICALL Java_me_adasdead_WTools_wSystem__1bsod
  (JNIEnv *env, jclass clz, jlong code)
{
    w_system_bsod((long) code);
}