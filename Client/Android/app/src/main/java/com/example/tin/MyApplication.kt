package com.example.tin

import android.app.Application
import com.example.tin.network.Connection

class MyApplication: Application() {

    override fun onCreate() {
        super.onCreate()
        Thread(Connection).start()
    }
}