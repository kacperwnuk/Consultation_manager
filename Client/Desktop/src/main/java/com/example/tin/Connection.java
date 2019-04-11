package com.example.tin;

import java.io.*;
import java.net.Socket;
import java.nio.CharBuffer;

public class Connection {

    String serverAddress = "192.168.0.220";
    int portNumber = 9975;
    Socket socket;


    private void changePort(int port)
    {
        portNumber = port;
    }

    public boolean connect()
    {
        try {
            socket = new Socket(serverAddress, portNumber);
            return true;
        } catch(IOException ex)
        {
            System.out.println("Unable to connect with server!");
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
        DataOutputStream outToServer = new DataOutputStream(socket.getOutputStream());
        outToServer.writeBytes(message);
        return 0;
    }

    public String recieveMessage() throws IOException
    {
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
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
}
