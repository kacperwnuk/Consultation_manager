package com.example.tin;

import javafx.fxml.FXMLLoader;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

import java.io.IOException;

public class MainWindow {
    @FXML
    TextField messageArea;
    @FXML
    Button sendButton;
    @FXML
    TextArea serverConsole;

    @FXML
    Button reconnectButton;

    private Connection connection = new Connection();

    @FXML
    private void reconnect(){
        serverConsole.clear();
        sendButton.setDisable(false);
        messageArea.setDisable(false);
        initialize();
    }

    @FXML
    private void initialize() {
        if(!connection.connect())
        {
            messageArea.setDisable(true);
            sendButton.setDisable(true);
            serverConsole.appendText("Unable to connect with server!");
        }
    }


    @FXML
    private void btnSendClicked() throws IOException, InterruptedException
    {
        String message = messageArea.getText();
        messageArea.clear();
        if(message.length()!=0) {
            connection.sendMessage(message);
            //Thread.sleep(200);
            serverConsole.appendText("Client says: " + message + "\n");
            handleServerMessage();
        }
    }

    private void handleServerMessage() throws IOException
    {
        String message = connection.recieveMessage();
        serverConsole.appendText("Server says: " + message + "\n");
    }

    public void disconnect()
    {
        System.out.println("MW: Disconnecting...");
        if(connection.getConnected())
            connection.disconnect();
    }
}