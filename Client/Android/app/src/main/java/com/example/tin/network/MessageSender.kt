package com.example.tin.network

import android.util.Log
import java.io.OutputStreamWriter
import java.util.concurrent.BlockingQueue
import java.util.concurrent.TimeUnit

class MessageSender(private var outputStreamWriter: OutputStreamWriter, private var queue: BlockingQueue<String>) : Runnable {

    private var isRunning = true
    override fun run() {
        while (isRunning) {
            val message = queue.poll(200, TimeUnit.MILLISECONDS)
            if (message != null) {
                outputStreamWriter.write(message)
                outputStreamWriter.flush()
            }
        }
        Log.d("MessageSender", "Stopped")
    }

    fun stop() {
        isRunning = false
    }
}