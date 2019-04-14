package com.example.tin;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.nio.CharBuffer;

public class Connection {

    String serverAddress = "192.168.0.164";
    int portNumber = 9975;
    Socket socket;
    DataOutputStream outToServer;
    BufferedReader inFromServer;
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
            inFromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
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

        outToServer.writeBytes(message);
        return 0;
    }

    public String recieveMessage() throws IOException
    {

        try {
            CharBuffer buffer = CharBuffer.allocate(1024);
            inFromServer.read(buffer);
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
