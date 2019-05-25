package com.example.tin;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class MainPage {
    @FXML
    Button yourConsultationsButton;
    @FXML
    Button searchButton;
    @FXML
    Button logoutButton;
    @FXML
    Button reconnectButton;
    @FXML
    TextArea console;


    private Connection connection = new Connection();
    private Serializer serializer;

    @FXML
    private void initialize() {
        if (!connection.connect()) {
            searchButton.setDisable(true);
            logoutButton.setDisable(true);
            yourConsultationsButton.setDisable(true);
            console.appendText("Problem z połączeniem z serwerem");
        }
        else
            console.appendText("Połączono pomyślnie");
    }

    public void disconnect() {
        System.out.println("MW: Disconnecting...");
        if (connection.getConnected())
            connection.disconnect();
    }

    public void setSerializer(Serializer serializer){
        this.serializer = serializer;
    }

    public void btnSearchClicked(ActionEvent actionEvent) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/search.fxml"));
            AnchorPane root = fxmlLoader.load();
            final SearchWindow controller = fxmlLoader.getController();
            controller.setSerializer(serializer);
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Wyszukaj konsultacje");
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
        
    }

    public void btnYourConsultationsClicked(ActionEvent actionEvent) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/newconsultation.fxml"));
            AnchorPane root = fxmlLoader.load();
            final NewConsultationWindow controller = fxmlLoader.getController();
            controller.setSerializer(serializer);
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Dodaj konsultację");
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void btnLogoutClicked(ActionEvent actionEvent) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/login.fxml"));
            AnchorPane root = fxmlLoader.load();
            final LoginWindow controller = fxmlLoader.getController();
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Login Window");
            stage.show();
            //serializer.connectionController.connection.disconnect();
            Stage oldstage = (Stage) logoutButton.getScene().getWindow();
            oldstage.close();


        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void btnreconnectClicked(ActionEvent actionEvent) {
        console.clear();
        searchButton.setDisable(false);
        logoutButton.setDisable(false);
        yourConsultationsButton.setDisable(false);
        initialize();
    }
}
