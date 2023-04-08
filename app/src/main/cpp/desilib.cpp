#include <jni.h>
#include <string>
#include "OpenGlInit.h"

//ESP espnatived_natived;
OpenGlInit OpenGlFun;
ImguiAndroidInput input;

int type=1,utype=2;

extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_surfaceDestroyed(JNIEnv *env, jclass clazz) {
    if (OpenGlFun.isValid()){
        OpenGlFun.onSurfaceDestroy();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_surfaceChange(JNIEnv *env, jclass clazz, jint width, jint high) {
    if (OpenGlFun.isValid()){
        OpenGlFun.onSurfaceChange(width, high);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_surfaceCreate(JNIEnv *env, jclass clazz, jobject holder, jint width, jint high) {
    OpenGlFun = OpenGlInit(env, holder, width, high);
    if (OpenGlFun.isValid()){
        OpenGlFun.onSurfaceCreate(width, high);
        OpenGlFun.setinput(&input);
    } else {
        LOGE("surfaceWidth=%s", "Error");
    }
}

extern "C" JNIEXPORT void JNICALL
Java_jiagu_natived_natived_Close(JNIEnv *,  jobject ) {
    Close();
}

extern "C"
JNIEXPORT jstring JNICALL
Java_jiagu_natived_natived_getAimX(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF(aimyy.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_jiagu_natived_natived_getAimY(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF(aimzz.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_jiagu_natived_natived_getAimZ(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF(aimxx.c_str());
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_jiagu_natived_natived_getReady(JNIEnv *env, jclass clazz, jstring val0, jstring val1,
                                    jstring val2) {
    const char *strsh1 = (*env).GetStringUTFChars(val0,0);
    const char *strsh256 = (*env).GetStringUTFChars(val1,0);
    const char *strmd5 = (*env).GetStringUTFChars(val2,0);

    int sockCheck=1;

    if (!Create()) {
        perror("Creation failed");
        return false;
    }
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&sockCheck, sizeof(int));
    if (!Bind()) {
        perror("Bind failed");
        return false;
    }

    if (!Listen()) {
        perror("Listen failed");
        return false;
    }
    if (Accept()) {
        SetValue sv{};
        sv.setmd5=strmd5;
        sv.setsha1=strsh1;
        sv.setsha256=strsh256;
        send((void*)&sv,sizeof(sv));
        // Close();
        return true;
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_senddata(JNIEnv *env, jclass clazz, jboolean val) {
    options.isChecking = val;
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_setAimForGlobal(JNIEnv *env, jclass clazz, jboolean val) {
    setAimForGlobal = val;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_jiagu_natived_natived_getEdit(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF(EDit.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_jiagu_natived_natived_getOr(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF(OR.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_surface_1touch_init(JNIEnv *env, jclass clazz) {
    input.funMshowinit(clazz, env);
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_setHP(JNIEnv *env, jclass clazz, jstring hp) {
    Dirpatch = (*env).GetStringUTFChars(hp,0);
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_MotionEventClick(JNIEnv *env, jclass clazz, jint event_get_action,
                                            jfloat pos_x, jfloat pos_y) {
    input.InputTouchEvent(event_get_action, pos_x, pos_y);
}
float winData[4];
extern "C"
JNIEXPORT jfloatArray JNICALL
Java_jiagu_natived_natived_GetWinsize(JNIEnv *env, jclass clazz) {
    jfloatArray newFloatArray = env->NewFloatArray(4);
    if (OpenGlFun.isValid()) {
        if (OpenGlFun.g_window) {
            winData[0] = OpenGlFun.g_window->Pos.x;
            winData[1] = OpenGlFun.g_window->Pos.y;
            winData[2] = OpenGlFun.g_window->Size.x;
            winData[3] = OpenGlFun.g_window->Size.y;
            env->SetFloatArrayRegion(newFloatArray, 0, 4, winData);
            env->ReleaseFloatArrayElements(newFloatArray, winData, JNI_COMMIT);
            return newFloatArray;
        }
    }
    env->ReleaseFloatArrayElements(newFloatArray, winData, JNI_COMMIT);
    return newFloatArray;
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_showView(JNIEnv *env, jclass clazz, jboolean val) {
    EspView = val;
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_function(JNIEnv *env, jclass clazz, jboolean val) {
    if (val != 0)
        options.openState = 0;
    else
        options.openState = -1;
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_getNReady(JNIEnv *env, jclass clazz, jstring sh1, jstring sh256,
                                     jstring md5) {
    Patchsh1 = (*env).GetStringUTFChars(sh1,0);
    Patchsh256 = (*env).GetStringUTFChars(sh256,0);
    Patchmd5 = (*env).GetStringUTFChars(md5,0);
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_setmOrientation(JNIEnv *env, jclass clazz, jint orientation) {
    if (orientation == 90){
        reverseTouch = true;
    } else {
        reverseTouch = false;
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_adjustCamera(JNIEnv *env, jclass clazz, jint x, jint y) {
    aimposx = -x;
    aimposy = y;
}
extern "C"
JNIEXPORT jint JNICALL
Java_jiagu_natived_natived_showadjustCamera(JNIEnv *env, jclass clazz) {
    if (AdjustCamera){
        return 1;
    } else {
        return 0;
    }
}
extern "C"
JNIEXPORT jint JNICALL
Java_jiagu_natived_natived_lockAimPos(JNIEnv *env, jclass clazz) {
    if (lockAimpost){
        return 1;
    } else {
        return 0;
    }
}
extern "C"
JNIEXPORT jint JNICALL
Java_jiagu_natived_natived_getFpsJni(JNIEnv *env, jclass clazz) {
    return fpsCount;
}
extern "C"
JNIEXPORT jint JNICALL
Java_jiagu_natived_natived_AutoShootPos(JNIEnv *env, jclass clazz) {
    if (AutoShootPos){
        return 1;
    } else {
        return 0;
    }
}
extern "C"
JNIEXPORT jint JNICALL
Java_jiagu_natived_natived_AutoShoot(JNIEnv *env, jclass clazz) {
    if (AutoShoot){
        return 1;
    } else {
        return 0;
    }
}
extern "C"
JNIEXPORT jint JNICALL
Java_jiagu_natived_natived_aimState(JNIEnv *env, jclass clazz) {
    if (aimObj == 0 || aimObj == 1){
        return 1;
    } else {
        return 0;
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_AutoShootPosXY(JNIEnv *env, jclass clazz, jint x, jint y) {
    AutoShootPosX = -x;
    AutoShootPosY = y;
}
extern "C"
JNIEXPORT void JNICALL
Java_jiagu_natived_natived_AutoShootButton(JNIEnv *env, jclass clazz, jboolean val) {
    options.shootLoop = val;
}
extern "C"
JNIEXPORT jstring JNICALL
Java_jiagu_surface_1touch_getJniString(JNIEnv *_env, jobject thiz) {
    jstring jstr = _env->NewStringUTF(fakeName);
    jclass clazz = _env->GetObjectClass(thiz);
    jmethodID realname = _env->GetMethodID(clazz, "realname", "(Ljava/lang/String;)Ljava/lang/String;");
    jobject result = _env->CallObjectMethod(thiz, realname, jstr);

    const char* str = _env->GetStringUTFChars((jstring) result, 0);
    LOGE("DATANAM %s", str);
    //realNM = str;

    return _env->NewStringUTF(str);
}