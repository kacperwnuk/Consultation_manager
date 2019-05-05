package com.example.tin;

import java.io.IOException;

public class ConnectionController {
    private Connection connection = new Connection();

    public void send(String message) throws IOException {
        connection.connect();
        connection.sendMessage( getLenghtWithZeros(message.length()) + message);
    }

    public String receive() throws IOException {
        return connection.recieveMessage();
    }

    private String getLenghtWithZeros(int lenght){
        return String.format("%04d", lenght);
    }
}
