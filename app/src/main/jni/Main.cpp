#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"
#include <android/log.h>
#include <cmath>
#include "Includes/Macros.h"

//Target lib here
#define targetLibName OBFUSCATE("libil2cpp.so")
#define  LOG_TAG    "Features"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


bool isCoolDown;
float attackInput, critRateInput, critDmgInput, skillDmgInput;
int sliderAtkSpd = 1, sliderMovSpd = 1;
void *instanceBtn;


//Hook attack
float (*old_get_damage)(void *instance);
float get_damage(void *instance) {
    if (instance != NULL && attackInput > 1) {
        float originalDMG = old_get_damage(instance);
        return originalDMG * attackInput;
    }
    return old_get_damage(instance);
}

//Hook CritRate
float (*old_get_critRate)(void *instance);
float get_critRate(void *instance) {
    if (instance != NULL && critRateInput > 1) {
        float originalCR = old_get_critRate(instance);
        float additionalCR = critRateInput / 100.0f;
        return (float) originalCR + additionalCR;
    }
    return old_get_critRate(instance);
}

//Hook CritDmg
float (*old_get_critDamageRate)(void *instance);
float get_critDamageRate(void *instance) {
    if (instance != NULL && critDmgInput > 1) {
        return old_get_critDamageRate(instance) + critDmgInput;
    }
    return old_get_critDamageRate(instance);
}

//Hook skillDMG
float (*old_GetDamage)(void *instance);
float GetDamage(void *instance) {
    if (instance != NULL && skillDmgInput > 1) {
        float originalSkillDMG = old_GetDamage(instance);
        float modifiedSkillDMG = originalSkillDMG * (float) skillDmgInput;
        return modifiedSkillDMG;
    }
    return old_GetDamage(instance);
}

//Hook AtkSpd
float (*old_get_attackSpeed)(void *instance);
float get_attackSpeed(void *instance) {
    if (instance != NULL && sliderAtkSpd > 1) {
        float originalAtkSpd = old_get_attackSpeed(instance);
        return originalAtkSpd + (float) sliderAtkSpd;
    }
    return old_get_attackSpeed(instance);
}

// Hook MovSpd
float (*old_get_moveSpeed)(void *instance);
float get_moveSpeed(void *instance) {
    if (instance != NULL && sliderMovSpd > 1) {
        float originalMovSpd = old_get_moveSpeed(instance);
        return originalMovSpd + (float) sliderMovSpd;
    }
    return old_get_moveSpeed(instance);
}


/*bool feature1, feature2, featureHookToggle, Health;
int sliderValue = 1, level = 0;

// Hooking examples. Assuming you know how to write hook
void (*AddMoneyExample)(void *instance, int amount);

bool (*old_get_BoolExample)(void *instance);
bool get_BoolExample(void *instance) {
    if (instance != NULL && featureHookToggle) {
        return true;
    }
    return old_get_BoolExample(instance);
}

float (*old_get_FloatExample)(void *instance);
float get_FloatExample(void *instance) {
    if (instance != NULL && sliderValue > 1) {
        return (float) sliderValue;
    }
    return old_get_FloatExample(instance);
}

int (*old_Level)(void *instance);
int Level(void *instance) {
    if (instance != NULL && level) {
        return (int) level;
    }
    return old_Level(instance);
}

void (*old_FunctionExample)(void *instance);
void FunctionExample(void *instance) {
    instanceBtn = instance;
    if (instance != NULL) {
        if (Health) {
            *(int *) ((uint64_t) instance + 0x48) = 999;
        }
    }
    return old_FunctionExample(instance);
}
*/

// we will run our hacks in a new thread so our while loop doesn't block process main thread
void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));

    //Check if target lib is loaded
    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));

    //Anti-lib rename
    /*
    do {
        sleep(1);
    } while (!isLibraryLoaded("libYOURNAME.so"));*/

    LOGI(OBFUSCATE("%s has been loaded"), (const char *) targetLibName);

#if defined(__aarch64__) //To compile this code for arm64 lib only. Do not worry about greyed out highlighting code, it still works
    // Hook example. Comment out if you don't use hook
    // Strings in macros are automatically obfuscated. No need to obfuscate!
    /*HOOK("str", FunctionExample, old_FunctionExample);
    HOOK_LIB("libFileB.so", "0x123456", FunctionExample, old_FunctionExample);
    HOOK_NO_ORIG("0x123456", FunctionExample);
    HOOK_LIB_NO_ORIG("libFileC.so", "0x123456", FunctionExample);
    HOOKSYM("__SymbolNameExample", FunctionExample, old_FunctionExample);
    HOOKSYM_LIB("libFileB.so", "__SymbolNameExample", FunctionExample, old_FunctionExample);
    HOOKSYM_NO_ORIG("__SymbolNameExample", FunctionExample);
    HOOKSYM_LIB_NO_ORIG("libFileB.so", "__SymbolNameExample", FunctionExample);

    // Patching offsets directly. Strings are automatically obfuscated too!
    PATCH("0x20D3A8", "00 00 A0 E3 1E FF 2F E1");
    PATCH_LIB("libFileB.so", "0x20D3A8", "00 00 A0 E3 1E FF 2F E1");

    AddMoneyExample = (void(*)(void *,int))getAbsoluteAddress(targetLibName, 0x123456);

    LOGI(OBFUSCATE("Done"));*/

#else //To compile this code for armv7 lib only.

    // Hook example. Comment out if you don't use hook
    // Strings in macros are automatically obfuscated. No need to obfuscate!
    /*HOOK("str", FunctionExample, old_FunctionExample);
    HOOK_LIB("libFileB.so", "0x123456", FunctionExample, old_FunctionExample);
    HOOK_NO_ORIG("0x123456", FunctionExample);
    HOOK_LIB_NO_ORIG("libFileC.so", "0x123456", FunctionExample);
    HOOKSYM("__SymbolNameExample", FunctionExample, old_FunctionExample);
    HOOKSYM_LIB("libFileB.so", "__SymbolNameExample", FunctionExample, old_FunctionExample);
    HOOKSYM_NO_ORIG("__SymbolNameExample", FunctionExample);
    HOOKSYM_LIB_NO_ORIG("libFileB.so", "__SymbolNameExample", FunctionExample);

    // Patching offsets directly. Strings are automatically obfuscated too!
    PATCH("0x20D3A8", "00 00 A0 E3 1E FF 2F E1");
    PATCH_LIB("libFileB.so", "0x20D3A8", "00 00 A0 E3 1E FF 2F E1");

    //Restore changes to original
    RESTORE("0x20D3A8");
    RESTORE_LIB("libFileB.so", "0x20D3A8");

    AddMoneyExample = (void (*)(void *, int)) getAbsoluteAddress(targetLibName, 0x123456);*/

    //Hook Attack
    HOOK("0x18E4534", get_damage, old_get_damage);
    //Hook CritRate
    HOOK("0x18E477C", get_critRate, old_get_critRate);
    //Hook CritDMG
    HOOK("0x18E4840", get_critDamageRate, old_get_critDamageRate);
    //Hook SkillDMG
    HOOK("0x10141AC", GetDamage, old_GetDamage);
    //Hook AtkSpd
    HOOK("0x18E46A8", get_attackSpeed, old_get_attackSpeed);
    //Hook MovSpd
    HOOK("0x18E5054", get_moveSpeed, old_get_moveSpeed);

    LOGI(OBFUSCATE("Done"));
#endif

    //Anti-leech
    /*if (!iconValid || !initValid || !settingsValid) {
        //Bad function to make it crash
        sleep(5);
        int *p = 0;
        *p = 0;
    }*/

    return nullptr;
}

// Do not change or translate the first text unless you know what you are doing
// Assigning feature numbers is optional. Without it, it will automatically count for you, starting from 0
// Assigned feature numbers can be like any numbers 1,3,200,10... instead in order 0,1,2,3,4,5...
// ButtonLink, Category, RichTextView and RichWebView is not counted. They can't have feature number assigned
// Toggle, ButtonOnOff and Checkbox can be switched on by default, if you add True_. Example: CheckBox_True_The Check Box
// To learn HTML, go to this page: https://www.w3schools.com/

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("0_Toggle_NoSkill CD"),
            OBFUSCATE("1_InputValue_1000_HeroAtk Multiplier"),
            OBFUSCATE("2_InputValue_1000_CritRate+"),
            OBFUSCATE("3_InputValue_1000_CritDmg+"),
            OBFUSCATE("4_InputValue_1000_SkillDmg Multiplier"),
            OBFUSCATE("5_SeekBar_AtkSpd+_1_20"),
            OBFUSCATE("6_SeekBar_MovSpd+_1_20")

            /*OBFUSCATE("100_Toggle_True_The toggle 2"), //This one have feature number assigned, and switched on by default
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
            OBFUSCATE("InputText_Input text"),
            OBFUSCATE("RadioButton_Radio buttons_OFF,Mod 1,Mod 2,Mod 3"),

            //Create new collapse
            OBFUSCATE("Collapse_Collapse 1"),
            OBFUSCATE("CollapseAdd_Toggle_The toggle"),
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
                      "</body></html>")*/
    };

    //Now you dont have to manually update the number everytime;
    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; ++i)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj,
             jint featNum, jstring featName, jint value,
             jboolean boolean, jstring str) {

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         env->GetStringUTFChars(featName, nullptr), static_cast<int>(value),
         boolean, str != nullptr ? env->GetStringUTFChars(str, nullptr) : "");

    //BE CAREFUL NOT TO ACCIDENTALLY REMOVE break;

    switch (featNum) {
        case 0:
            isCoolDown = boolean;
            PATCH_LIB_SWITCH("libil2cpp.so", "0x18E4904", "00 00 A0 E3 1E FF 2F E1", boolean);
            break;
        case 1:
            attackInput = value;
            break;
        case 2:
            critRateInput = value;
            break;
        case 3:
            critDmgInput = value;
            break;
        case 4:
            skillDmgInput = value;
            break;
        case 5:
            if (value >= 1) {
                sliderAtkSpd = value;
            }
            break;
        case 6:
            if (value >= 1) {
                sliderMovSpd = value;
            }
            break;
    }
    /*switch (featNum) {
        case 0:
            // A much simpler way to patch hex via KittyMemory without need to specify the struct and len. Spaces or without spaces are fine
            // ARMv7 assembly example
            // MOV R0, #0x0 = 00 00 A0 E3
            // BX LR = 1E FF 2F E1
            PATCH_LIB_SWITCH("libil2cpp.so", "0x100000", "00 00 A0 E3 1E FF 2F E1", boolean);
            break;
        case 100:
            //Reminder that the strings are auto obfuscated
            //Switchable patch
            PATCH_SWITCH("0x400000", "00 00 A0 E3 1E FF 2F E1", boolean);
            PATCH_LIB_SWITCH("libil2cpp.so", "0x200000", "00 00 A0 E3 1E FF 2F E1", boolean);
            PATCH_SYM_SWITCH("_SymbolExample", "00 00 A0 E3 1E FF 2F E1", boolean);
            PATCH_LIB_SYM_SWITCH("libNativeGame.so", "_SymbolExample", "00 00 A0 E3 1E FF 2F E1", boolean);

            //Restore patched offset to original
            RESTORE("0x400000");
            RESTORE_LIB("libil2cpp.so", "0x400000");
            RESTORE_SYM("_SymbolExample");
            RESTORE_LIB_SYM("libil2cpp.so", "_SymbolExample");
            break;
        case 110:
            break;
        case 1:
            if (value >= 1) {
                sliderValue = value;
            }
            break;
        case 2:
            switch (value) {
                //For noobies
                case 0:
                    RESTORE("0x0");
                    break;
                case 1:
                    PATCH("0x0", "01 00 A0 E3 1E FF 2F E1");
                    break;
                case 2:
                    PATCH("0x0", "02 00 A0 E3 1E FF 2F E1");
                    break;
            }
            break;
        case 3:
            switch (value) {
                case 0:
                    LOGD(OBFUSCATE("Selected item 1"));
                    break;
                case 1:
                    LOGD(OBFUSCATE("Selected item 2"));
                    break;
                case 2:
                    LOGD(OBFUSCATE("Selected item 3"));
                    break;
            }
            break;
        case 4:
            // Since we have instanceBtn as a field, we can call it out of Update hook function
            if (instanceBtn != NULL)
                AddMoneyExample(instanceBtn, 999999);
            // Toast(env, obj, OBFUSCATE("Button pressed"), ToastLength::LENGTH_SHORT);
            break;
        case 5:
            break;
        case 6:
            featureHookToggle = boolean;
            break;
        case 7:
            level = value;
            break;
        case 8:
            break;
        case 9:
            break;
    }*/

}

__attribute__((constructor))
void lib_main() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
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
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void *>(Changes)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Preferences"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void *>(CheckOverlayPermission)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Main"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_OK;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (RegisterMenu(env) != 0)
        return JNI_ERR;
    if (RegisterPreferences(env) != 0)
        return JNI_ERR;
    if (RegisterMain(env) != 0)
        return JNI_ERR;
    return JNI_VERSION_1_6;
}
