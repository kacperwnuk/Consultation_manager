package com.example.tin;

import com.example.tin.security.Encryption;

import java.io.IOException;

public class ConnectionController {
    private Connection connection = new Connection();
    private Encryption encryption = new Encryption();

/*
    public void send(String message) throws IOException {
        if (!connection.isConnected)
            connection.connect();
        if (connection.isConnected)
            connection.sendMessage( getLenghtWithZeros(message.length()) + message);
    } */
/*
    public String receive() throws IOException {
        if (connection.isConnected)
            return connection.receiveMessage();
        throw new IOException("Nie połączono z serwerem");
    } */

    public ConnectionController(){
    }


    public void send(String message) throws IOException {
        if (!connection.isConnected)
            connection.connect();
        if (connection.isConnected) {
            String encryptedMessage = encryption.encrypt(message);
            if(encryptedMessage != null && encryptedMessage.length() !=0)
                connection.sendMessage(getLenghtWithZeros(encryptedMessage.length()) + encryptedMessage);
            else
                throw new IOException("Pusta wiadomosc! - problem z szyfrowaniem...?");
        }
    }

    public String receive() throws IOException {
        if (connection.isConnected) {
            String received = connection.receiveMessage();
            return encryption.decrypt(received);
        }
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

    public void setKey(String key) {
        encryption.setKey(key);
    }
}
