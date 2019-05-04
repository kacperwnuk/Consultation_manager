package com.example.tin;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;


public class Main extends Application {
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("../tin/login.fxml"));
        AnchorPane root = fxmlLoader.load();
        Scene scene = new Scene(root);
        primaryStage.setScene(scene);
        final LoginWindow controller = fxmlLoader.getController();
        primaryStage.setResizable(false);
        primaryStage.setTitle("Login Window");
        //primaryStage.setOnHidden(e -> controller.disconnect());
        primaryStage.show();
    }
}
