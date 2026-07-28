package com.android.support;

import android.app.ActivityManager;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Intent;
import android.content.pm.ServiceInfo;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.view.View;

public class Launcher extends Service {

    private static final String CHANNEL_ID = "ModMenuChannel";
    private static final int NOTIFICATION_ID = 1;
    Menu menu;

    //When this Class is called the code in this function will be executed
    @Override
    public void onCreate() {
        super.onCreate();

        // Create notification channel for Android 8+
        createNotificationChannel();
        
        // Start as foreground service with proper type for Android 14+
        startAsForeground();

        menu = new Menu(this);
        menu.SetWindowManagerWindowService();
        menu.ShowMenu();

        //Create a handler for this Class
        final Handler handler = new Handler();
        handler.post(new Runnable() {
            public void run() {
                Thread();
                handler.postDelayed(this, 1000);
            }
        });
    }

    private void createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel channel = new NotificationChannel(
                CHANNEL_ID,
                "Mod Menu Service",
                NotificationManager.IMPORTANCE_LOW // Low importance = no sound
            );
            channel.setDescription("ModMenu is running");
            channel.setShowBadge(false);
            
            NotificationManager manager = getSystemService(NotificationManager.class);
            if (manager != null) {
                manager.createNotificationChannel(channel);
            }
        }
    }

    private void startAsForeground() {
        Notification.Builder builder;
        
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            builder = new Notification.Builder(this, CHANNEL_ID);
        } else {
            builder = new Notification.Builder(this);
        }

        Notification notification = builder
            .setContentTitle("ModMenu")
            .setContentText("Running...")
            .setSmallIcon(android.R.drawable.ic_menu_info_details)
            .setOngoing(true)
            .build();

        // Android 14 (UPSIDE_DOWN_CAKE) requires specifying foreground service type
        if (Build.VERSION.SDK_INT >= 34) { // Build.VERSION_CODES.UPSIDE_DOWN_CAKE
            startForeground(NOTIFICATION_ID, notification, 
                ServiceInfo.FOREGROUND_SERVICE_TYPE_SPECIAL_USE);
        } else {
            startForeground(NOTIFICATION_ID, notification);
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    //Check if we are still in the game. If now our menu and menu button will dissapear
    private boolean isNotInGame() {
        ActivityManager.RunningAppProcessInfo runningAppProcessInfo = new ActivityManager.RunningAppProcessInfo();
        ActivityManager.getMyMemoryState(runningAppProcessInfo);
        return runningAppProcessInfo.importance != 100;
    }

    private void Thread() {
        if (isNotInGame()) {
            menu.setVisibility(View.INVISIBLE);
        } else {
            menu.setVisibility(View.VISIBLE);
        }
    }

    //Destroy our View
    public void onDestroy() {
        super.onDestroy();
        menu.onDestroy();
        stopForeground(true);
    }

    //Same as above so it wont crash in the background and therefore use alot of Battery life
    public void onTaskRemoved(Intent intent) {
        super.onTaskRemoved(intent);
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        stopForeground(true);
        stopSelf();
    }

    //Override our Start Command so the Service doesnt try to recreate itself when the App is closed
    public int onStartCommand(Intent intent, int i, int i2) {
        return Service.START_NOT_STICKY;
    }
}
