package com.example.tin;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.sql.SQLOutput;

public class Connection {

    String serverAddress = "192.168.0.164";
    int portNumber = 9994;
    Socket socket;
    DataOutputStream outToServer;
    DataInputStream inFromServer;
    boolean isConnected = false;


    private void changePort(int port)
    {
        portNumber = port;
        connect();
    }

    public boolean connect()
    {
        try {
            System.out.println("Lacze z serwerem...");
            socket = new Socket(serverAddress, portNumber);
            //socket.connect(new InetSocketAddress(serverAddress, portNumber));
            System.out.println("Polaczono");
            isConnected = true;
            outToServer = new DataOutputStream(socket.getOutputStream());
            inFromServer = new DataInputStream(socket.getInputStream());
            return true;
        } catch(Exception ex)
        {
            System.out.println("Unable to connect with server!");
            isConnected = false;
            return false;
        }
    }

    public void disconnect()
    {
        try {
            socket.close();
        }
        catch (IOException ex)
        {
            System.out.println("Problem with disconnecting");
        }
    }

    public int sendMessage(String message) throws IOException
    {

        System.out.println("Pisze info");
        outToServer.writeBytes(message);
        System.out.println("Napisalem info");
        return 0;
    }

    public String recieveMessage() throws IOException
    {

        try {
            System.out.println("Czekam na wiadomosc");
            ByteBuffer buffer = ByteBuffer.allocate(1024);
            inFromServer.read(buffer.array());
            String message = new String(buffer.array());
            System.out.println("Wiadomosc: " + message);
            return message;
        } catch(IOException ex)
        {
            disconnect();
            System.out.println("Problem with receivig message! Disconnecting...");
            return "";
        }
    }

    public boolean getConnected()
    {
        return isConnected;
    }
}
