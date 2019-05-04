package com.example.tin.network

import java.io.BufferedInputStream
import java.io.OutputStreamWriter
import java.net.Inet4Address
import java.net.Socket
import java.net.SocketTimeoutException
import java.util.concurrent.ArrayBlockingQueue

class Client: Runnable {

    private lateinit var socket: Socket
    private var address = Inet4Address.getByName("192.168.0.11")
    private var queue = ArrayBlockingQueue<String>(10)
    private var isRunning = true

    override fun run() {
        socket = Socket(address, 9999)
        socket.soTimeout = 200
        val outStream = OutputStreamWriter(socket.getOutputStream())
        val inStream = BufferedInputStream(socket.getInputStream())
        val messageSender = MessageSender(outStream, queue)
        Thread(messageSender).start()
        while (isRunning) {
            try {
                inStream.read()
            } catch(e: SocketTimeoutException) {
//                Log.d("client", "timeout")
            }
        }
        messageSender.stop()
        socket.close()
    }

    fun stop() {
        isRunning = false
    }
}