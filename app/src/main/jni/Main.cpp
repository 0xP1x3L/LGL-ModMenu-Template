#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <android/log.h>

#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"
#include "Includes/Macros.h"

#define targetLibName OBFUSCATE("libil2cpp.so")

// --- Variables ---
bool isVerified = false; 
bool mapHack, autoRetri;
float attackMultiplier = 1.0f;
std::string masterKey = "NUI-2024"; 

// --- Hooking Functions ---
float (*old_get_damage)(void *instance);
float get_damage(void *instance) {
    if (instance != NULL && isVerified && attackMultiplier > 1.0f) {
        return old_get_damage(instance) * attackMultiplier;
    }
    return old_get_damage(instance);
}

void *hack_thread(void *) {
    do { sleep(1); } while (!isLibraryLoaded(targetLibName));
    HOOK("0x18E4534", get_damage, old_get_damage);
    return nullptr;
}

// --- Menu Features ---
jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;
    const char *features[] = {
            OBFUSCATE("Category_NUI MYANMAR (Key Required)"),
            OBFUSCATE("InputText_Enter Key Here"),
            OBFUSCATE("Button_Verify Key"),
            OBFUSCATE("Category_HACK FEATURES"),
            OBFUSCATE("0_Toggle_Map Hack"),
            OBFUSCATE("1_SeekBar_Drone View_1_5"),
            OBFUSCATE("2_Toggle_Auto Retri"),
            OBFUSCATE("3_InputValue_10_Damage Multiplier"),
            OBFUSCATE("RichTextView_Created by <b>NUI Myanmar</b>")
    };

    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")), env->NewStringUTF(""));
    for (int i = 0; i < Total_Feature; ++i)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return (ret);
}

// --- Logic Handling ---
void Changes(JNIEnv *env, jclass clazz, jobject obj, jint featNum, jstring featName, jint value, jboolean boolean, jstring str) {
    
    const char* name = env->GetStringUTFChars(featName, nullptr);

    if (strcmp(name, "Verify Key") == 0) {
        if (str != nullptr) {
            std::string inputKey = env->GetStringUTFChars(str, nullptr);
            if (inputKey == masterKey) {
                isVerified = true;
                LOGI("Key Verified Successfully!");
            }
        }
        return;
    }

    if (!isVerified) return; 

    switch (featNum) {
        case 0:
            PATCH_LIB_SWITCH("libil2cpp.so", "0x123456", "00 00 A0 E3 1E FF 2F E1", boolean);
            break;
        case 2:
            autoRetri = boolean;
            break;
        case 3:
            attackMultiplier = (float)value;
            break;
    }
}

// --- JNI Standard Parts ---
__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, nullptr, hack_thread, nullptr);
}

int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(Icon)},
            {OBFUSCATE("IconWebViewData"),  OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(IconWebViewData)},
            {OBFUSCATE("IsGameLibLoaded"),  OBFUSCATE("()Z"), reinterpret_cast<void *>(isGameLibLoaded)},
            {OBFUSCATE("Init"),  OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), reinterpret_cast<void *>(Init)},
            {OBFUSCATE("SettingsList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(SettingsList)},
            {OBFUSCATE("GetFeatureList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(GetFeatureList)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Menu"));
    if (!clazz) return JNI_ERR;
    env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0]));
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void *>(Changes)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Preferences"));
    if (!clazz) return JNI_ERR;
    env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0]));
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void *>(CheckOverlayPermission)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Main"));
    if (!clazz) return JNI_ERR;
    env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0]));
    return JNI_OK;
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    RegisterMenu(env);
    RegisterPreferences(env);
    RegisterMain(env);
    return JNI_VERSION_1_6;
}
