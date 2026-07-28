#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Macros.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"
#include <android/log.h>
#include <cmath>
#include <cstring>
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <jni.h>
#include <list>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <vector>

#define targetLibName OBFUSCATE("libil2cpp.so")

/*
// Example Logic: NoSkill CD, AtkSpd...
/*
bool isCoolDown;
float attackInput, critRateInput, critDmgInput, skillDmgInput;
int sliderAtkSpd = 1, sliderMovSpd = 1;

float (*old_get_damage)(void *instance);
float get_damage(void *instance) {
  if (instance != nullptr && attackInput > 1) {
    float originalDMG = old_get_damage(instance);
    return originalDMG * attackInput;
  }
  return old_get_damage(instance);
}
... (and more)
*/

// Example hack_thread using ElfScanner (if available in your project)
/*
void *hack_thread_example(void *) {
    do {
        sleep(1);
        g_il2cppELF = ElfScanner::createWithPath(targetLibName);
    } while (!g_il2cppELF.isValid());

    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName);

#if defined(__aarch64__)
    uintptr_t il2cppBase = g_il2cppELF.base();
    HOOK(targetLibName, str2Offset(OBFUSCATE("0x107A2E0")), AddScore, old_AddScore);
#endif
    return nullptr;
}

// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
// To learn HTML, go to this page: https://www.w3schools.com/

jobjectArray GetFeatureList_Example(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Toggle_No death"),
            OBFUSCATE("Button_Start Invcibility (30 sec duration)"),
            OBFUSCATE("SeekBar_Score multiplier_1_100"),
            OBFUSCATE("SeekBar_Coins multiplier_1_1000"),
            OBFUSCATE("Category_Examples"), //Not counted
            OBFUSCATE("Toggle_The toggle"),
            OBFUSCATE(
                    "100_Toggle_True_The toggle 2"), //This one have feature number assigned, and switched on by default
            OBFUSCATE("110_Toggle_The toggle 3"), //This one too
            OBFUSCATE("SeekBar_The slider_1_100"),
            OBFUSCATE("SeekBar_Kittymemory slider example_1_5"),
            OBFUSCATE("Spinner_The spinner_Items 1,Items 2,Items 3"),
            OBFUSCATE("Button_The button"),
            OBFUSCATE("ButtonLink_The button with link_https://www.youtube.com/"), //Not counted
            OBFUSCATE("ButtonOnOff_The On/Off button"),
            OBFUSCATE("CheckBox_The Check Box"),
            OBFUSCATE("InputValue_Input number"),
            OBFUSCATE("InputValue_1000_Input number 2"), //Max value
			OBFUSCATE("1111_InputLValue_Input long number"),
            OBFUSCATE("InputLValue_1000000000000_Input long number 2"), //Max value
            OBFUSCATE("InputText_Input text"),
            OBFUSCATE("RadioButton_Radio buttons_OFF,Mod 1,Mod 2,Mod 3"),

            //Create new collapse
            OBFUSCATE("Collapse_Collapse 1"),
            OBFUSCATE("CollapseAdd_Toggle_The toggle"),
            OBFUSCATE("123_CollapseAdd_Toggle_The toggle"),
            OBFUSCATE("122_CollapseAdd_CheckBox_Check box"),
            OBFUSCATE("CollapseAdd_Button_The button"),

            //Create new collapse again
            OBFUSCATE("Collapse_Collapse 2_True"),
            OBFUSCATE("CollapseAdd_SeekBar_The slider_1_100"),
            OBFUSCATE("CollapseAdd_InputValue_Input number"),

            OBFUSCATE("RichTextView_This is text view, not fully HTML."
                      "<b>Bold</b> <i>italic</i> <u>underline</u>"
                      "<br />New line <font color='red'>Support colors</font>"
                      "<br/><big>bigger Text</big>"),
            OBFUSCATE("RichWebView_<html><head><style>body{color: white;}</style></head><body>"
                      "This is WebView, with REAL HTML support!"
                      "<div style=\"background-color: darkblue; text-align: center;\">Support CSS</div>"
                      "<marquee style=\"color: green; font-weight:bold;\" direction=\"left\" scrollamount=\"5\" behavior=\"scroll\">This is <u>scrollable</u> text</marquee>"
                      "</body></html>")
    };

    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

void Changes_Example(JNIEnv *env, jclass clazz, jobject obj, jint featNum, jstring featName, jint value, jlong Lvalue, jboolean boolean, jstring text) {

    switch (featNum) {
        case 0:
        {
            if (boolean)
                // gPatches.noDeath.Modify();
            else
                // gPatches.noDeath.Restore();
            break;
        }
        case 1:
            // btnPressed = true;
            break;
        case 2:
            // scoreMul = value;
            break;
        case 3:
            // coinsMul = value;
            break;
    }
}
-------------------------- */



void *hack_thread(void *) {
  LOGD(OBFUSCATE("pthread created"));

  do {
    sleep(1);
  } while (!isLibraryLoaded(targetLibName));

  LOGD(OBFUSCATE("%s has been loaded"), (const char *)targetLibName);

#if defined(__aarch64__)
  
#else

  LOGD(OBFUSCATE("Done"));
#endif

  return nullptr;
}

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
  jobjectArray ret;

  const char *features[] = {
          
  };

  int Total_Feature = (sizeof features / sizeof features[0]);
  ret = (jobjectArray)env->NewObjectArray(
      Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
      env->NewStringUTF(""));

  for (int i = 0; i < Total_Feature; ++i)
    env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

  return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj, jint featNum,
             jstring featName, jint value, jboolean boolean, jstring str) {

  const char *name = env->GetStringUTFChars(featName, nullptr);
  const char *text = str != nullptr ? env->GetStringUTFChars(str, nullptr) : "";

  LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"),
       featNum, name, static_cast<int>(value), boolean, text);

  switch (featNum) {
      break;
  }
}

__attribute__((constructor)) void lib_main() {
  pthread_t ptid;
  pthread_create(&ptid, nullptr, hack_thread, nullptr);
}

int RegisterMenu(JNIEnv *env) {
  JNINativeMethod methods[] = {
      {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"),
       reinterpret_cast<void *>(Icon)},
      {OBFUSCATE("IconWebViewData"), OBFUSCATE("()Ljava/lang/String;"),
       reinterpret_cast<void *>(IconWebViewData)},
      {OBFUSCATE("IsGameLibLoaded"), OBFUSCATE("()Z"),
       reinterpret_cast<void *>(isGameLibLoaded)},
      {OBFUSCATE("Init"),
       OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/"
                 "widget/TextView;)V"),
       reinterpret_cast<void *>(Init)},
      {OBFUSCATE("SettingsList"), OBFUSCATE("()[Ljava/lang/String;"),
       reinterpret_cast<void *>(SettingsList)},
      {OBFUSCATE("GetFeatureList"), OBFUSCATE("()[Ljava/lang/String;"),
       reinterpret_cast<void *>(GetFeatureList)},
  };

  jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Menu"));
  if (!clazz)
    return JNI_ERR;
  if (env->RegisterNatives(clazz, methods,
                           sizeof(methods) / sizeof(methods[0])) != 0)
    return JNI_ERR;
  return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
  JNINativeMethod methods[] = {
      {OBFUSCATE("Changes"),
       OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/"
                 "String;)V"),
       reinterpret_cast<void *>(Changes)},
  };
  jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Preferences"));
  if (!clazz)
    return JNI_ERR;
  if (env->RegisterNatives(clazz, methods,
                           sizeof(methods) / sizeof(methods[0])) != 0)
    return JNI_ERR;
  return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
  JNINativeMethod methods[] = {
      {OBFUSCATE("CheckOverlayPermission"),
       OBFUSCATE("(Landroid/content/Context;)V"),
       reinterpret_cast<void *>(CheckOverlayPermission)},
  };
  jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Main"));
  if (!clazz)
    return JNI_ERR;
  if (env->RegisterNatives(clazz, methods,
                           sizeof(methods) / sizeof(methods[0])) != 0)
    return JNI_ERR;

  return JNI_OK;
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
  JNIEnv *env;
  if (vm->GetEnv((void **)&env, JNI_VERSION_1_6) != JNI_OK)
    return JNI_ERR;

  if (RegisterMenu(env) != 0)
    return JNI_ERR;
  if (RegisterPreferences(env) != 0)
    return JNI_ERR;
  if (RegisterMain(env) != 0)
    return JNI_ERR;
  return JNI_VERSION_1_6;
}
