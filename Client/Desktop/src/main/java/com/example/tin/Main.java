package com.example.tin;

import javafx.application.Application;
import javafx.stage.Stage;


public class Main extends Application {
    public void start(Stage primaryStage) throws Exception {
        //primaryStage.show();

        Connection connection = new Connection();
        connection.connect();
        connection.sendMessage("Witam serdecznie i milego dnia! \n");
        //TimeUnit.SECONDS.sleep(1);
        connection.recieveMessage();
        System.out.println("Koncze");
        connection.disconnect();

    }
}
