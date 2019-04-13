package com.example.tin;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;


public class Main extends Application {
    public void start(Stage primaryStage) throws Exception {


        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("../tin/sample.fxml"));
        AnchorPane root = fxmlLoader.load();

        Scene scene = new Scene(root);
        primaryStage.setScene(scene);
        final MainWindow controller = fxmlLoader.getController();
        primaryStage.setResizable(false);
        primaryStage.setTitle("TIN Basic client");
        primaryStage.setOnHidden(e -> controller.disconnect());
        primaryStage.show();

        /*
        Connection connection = new Connection();
        connection.connect();
        connection.sendMessage("Witam serdecznie i milego dnia! \n");
        connection.recieveMessage();
        System.out.println("Koncze");
        connection.disconnect();
        */

    }
}
