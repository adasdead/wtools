/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class me_adasdead_WTools_wMessageBox */

#ifndef _Included_me_adasdead_WTools_wMessageBox
#define _Included_me_adasdead_WTools_wMessageBox
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     me_adasdead_WTools_wMessageBox
 * Method:    rawAlert
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_me_adasdead_WTools_wMessageBox_rawAlert
  (JNIEnv *, jclass, jstring, jstring, jstring);

/*
 * Class:     me_adasdead_WTools_wMessageBox
 * Method:    rawConfirm
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_me_adasdead_WTools_wMessageBox_rawConfirm
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring);

/*
 * Class:     me_adasdead_WTools_wMessageBox
 * Method:    rawPrompt
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_me_adasdead_WTools_wMessageBox_rawPrompt
  (JNIEnv *, jclass, jstring, jstring, jstring, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
