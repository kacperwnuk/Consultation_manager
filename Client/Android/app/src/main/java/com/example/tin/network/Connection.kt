package com.example.tin.network

import java.io.DataInputStream
import java.io.IOException
import java.io.OutputStreamWriter
import java.net.Socket
import java.net.UnknownHostException
import java.nio.charset.StandardCharsets

object Connection : Runnable {

    interface NetworkEventListener {
        fun incomingMessage(message: String)
    }

    private var serverAddress = "192.168.0.11"
    private var portNumber = 9999
    private lateinit var socket: Socket
    private lateinit var outToServer: OutputStreamWriter
    private lateinit var inFromServer: DataInputStream
    private var isRunning = true
    private var isConnected = false
    private var networkEventListener: NetworkEventListener? = null
    private var shouldReconnect = true
    private var lock = Object()

    fun setNetworkEventListener(networkEventListener: NetworkEventListener) {
        this.networkEventListener = networkEventListener
    }

    init {

    }

    private fun tryConnect(): Boolean {
        try {
            socket = Socket(serverAddress, portNumber)
            outToServer = OutputStreamWriter(socket.getOutputStream())
            inFromServer = DataInputStream(socket.getInputStream())
        } catch (e: UnknownHostException) {
            return false
        } catch (e: IOException) {
            return false
        }
        return true
    }

    private fun connect() {
        while (!tryConnect());
        isConnected = true
    }

    @Synchronized
    override fun run() {
        connect()

        while (isRunning) {
            if (!isConnected) {
                if (shouldReconnect) {
                    connect()
                } else {
                    synchronized(lock) {
                        lock.wait()
                    }
                }
            }
            try {
                val readMessage = readMessage()
                try {
                    networkEventListener!!.incomingMessage(readMessage)
                } catch (e: NullPointerException) {

                }
            } catch (e: IOException) {
                print(e)
            }
        }
    }

    private fun readMessage(): String {
        if (!isConnected) {
            connect()
        }
        try {
            val messageSize = Integer.parseInt(read(4))
            return read(messageSize)
        } catch (e: IOException) {
            throw e
        } catch (e: NumberFormatException) {
            throw IOException()
        }
    }

    private fun read(bytesToRead: Int): String {
        val messageBuffer = ByteArray(bytesToRead)
        var bytesRead = 0
        try {
            while (bytesRead != bytesToRead) {
                val result = inFromServer.read(messageBuffer, bytesRead, bytesToRead - bytesRead)
                if (result == -1) {
                    isConnected = false
                    throw IOException()
                }
                bytesRead += result
            }
        } catch (e: IOException) {
            throw e
        }
        return String(messageBuffer, StandardCharsets.UTF_8)
    }

    fun disconnect() {
        isConnected = false
        shouldReconnect = false
        socket.close()
    }

    fun isConnected(): Boolean {
        return isConnected
    }

    fun sendMessage(message: String) {
        if (!isConnected) {
            connect()
        }
        val seizedMessage = String.format("%04d$message", message.length)
        outToServer.write(seizedMessage)
        outToServer.flush()
    }

    fun reconnect() {
        shouldReconnect = true
        synchronized(lock) {
            lock.notify()
        }
    }
}