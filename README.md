# Introduction
LGL Mod Menu Template modified and updated version by me. (Updated in 4/2025)

# How to mod and hook
Main file to create function in mod menu is "Main.cpp" file, you can read how i use HOOK.

List of tutorial you need to watch before you make mod.

[Video-1](https://www.youtube.com/watch?v=ieMclBtL6Ig&t)

[Video-2](https://www.youtube.com/watch?v=eMQTR3dSNpw&t)

[LIST-MODDING-TUTORIAL](https://platinmods.com/threads/list-of-platinmods-modding-tutorials.19773)

Tutorial in video is quite old, but some ways still work.

About tutorial below, you can read how to inject mod in to apk file.

# How to inject mod menu in to Game APKs.

Decompile the game's APK file if you haven't done so already.

After you build your app by Android Studio, nevigate to lib app foulder.

PLEASE REMEMBER TO COPY FILE lib .so of app to lib game. 

Make sure you copy correct Architectures lib app to lib game.

## Step 1: Edit the game's AndroidManifest.xml file

Open the AndroidManifest.xml file of the game you want to inject the mod.

Add the following line inside the <manifest> tag if it does not exist:
```XML
<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW"/>
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE"/>
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE"/>
```
Add this line in bottom, you can follow video to know where to add.
```XML
<service android:name="com.android.support.Launcher" android:enabled="true" android:exported="false" android:stopWithTask="true"/>
```
You can find these line in your app ```AndroidManifest.xml``` file.

Note this <application> tag, if the decomplie fails due to full dex classes, need to create a new smali_classesX:
```XML
<application android:appCategory="game" android:appComponentFactory="androidx.core.app.CoreComponentFactory" android:hardwareAccelerated="true" android:icon="@mipmap/app_icon" android:isGame="true" android:label="@string/app_name" android:name="androidx.multidex.MultiDexApplication" android:networkSecurityConfig="@xml/tp_network_security_config" android:roundIcon="@mipmap/app_icon_round" android:supportsRtl="true" android:theme="@android:style/Theme.NoTitleBar.Fullscreen" android:usesCleartextTraffic="true">
```
Need to change to ```android:name="androidx.multidex.MultiDexApplication"``` and then create a folder named smali_classesX (where X is a zero in the existing folders)

## Step 2: Edit the smali file of the MainActivity in the game

Decompile the game's APK file if you haven't done so already.

Find the smali file corresponding to the game's MainActivity. 

Example:

GameDecompiledAPK/smali/com/some_path/some_path/MainActivity.smali.

Open the Main smali file with a text editor.

Search for the onCreate method. It should look like this:

```Smali
.method protected onCreate(Landroid/os/Bundle;)V
.locals 1
.param p1, "savedInstanceState" # Landroid/os/Bundle;

# [We need add code here]

return-void
.end method
```
Add the following line of code right after the invoke-super line in the onCreate method:

```Smali
invoke-static {p0}, Lcom/android/support/Main;->StartWithoutPermission(Landroid/content/Context;)V
```
Step 3: Recompile and re-sign the game APK

Use apktool to recompile the edited smali files into DEX files.
Re-sign the edited APK using jarsigner or Android Studio.
Important Note:

Make sure you have backed up the original game APK file before making any changes.

Good luck with your mod injection!

# License
**GNU General Public License 3**

# Disclaimer
This template is created by LGL TEAM, not me, i'm just update template and share it.

This project is for Educational Use only. I do not condone this project being used to gain an advantage against other people. This project was made for fun.

I strongly refrain you from buying any source codes on Telegram even if the author can be trusted, there is always a risk getting scammed. I will not be responsible for that. This project is always FREE to use
