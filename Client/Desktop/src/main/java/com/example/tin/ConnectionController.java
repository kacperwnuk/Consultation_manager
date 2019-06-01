package com.example.tin;

import java.io.IOException;

public class ConnectionController {
    private Connection connection = new Connection();

    public void send(String message) throws IOException {
        if (!connection.isConnected)
            connection.connect();
        if (connection.isConnected)
            connection.sendMessage( getLenghtWithZeros(message.length()) + message);
    }

    public String receive() throws IOException {
        if (connection.isConnected)
            return connection.receiveMessage();
        throw new IOException("Nie połączono z serwerem");
    }

    private String getLenghtWithZeros(int lenght){
        return String.format("%04d", lenght);
    }

    public boolean isConnected(){
        return connection.isConnected;
    }

    public void disconnect(){
        connection.disconnect();
    }
}
