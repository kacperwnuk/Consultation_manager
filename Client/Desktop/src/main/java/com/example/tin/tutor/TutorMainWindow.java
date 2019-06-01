package com.example.tin.tutor;

import com.example.tin.LoginWindow;
import com.example.tin.Serializer;
import com.example.tin.YourConsultationsWindow;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class TutorMainWindow {
    @FXML
    Button yourConsultationsButton;
    @FXML
    Button usersButton;
    @FXML
    Button logoutButton;
    @FXML
    Button requestsButton;
    @FXML
    Button reconnectButton;
    @FXML
    TextArea console;
    @FXML
    Button cancelConsultationButton;


    private Serializer serializer;

    @FXML
    private void initialize() {
    }

    public void disconnect() {
        System.out.println("MW: Disconnecting...");
        if (serializer.isConnected())
            serializer.disconnect();
    }

    public void setSerializer(Serializer serializer){
        this.serializer = serializer;
        if (!serializer.isConnected()) {           
            console.appendText("Problem z połączeniem z serwerem");
        }
        else
            console.appendText("Połączono pomyślnie");
    }


    public void btnYourConsultationsClicked(ActionEvent actionEvent) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/tutornewconsultation.fxml"));
            AnchorPane root = fxmlLoader.load();
            final TutorNewConsultation controller = fxmlLoader.getController();
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

    public void btnUsersClicked(ActionEvent actionEvent) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/tutorusers.fxml"));
            AnchorPane root = fxmlLoader.load();
            final TutorUsersWindow controller = fxmlLoader.getController();
            controller.setSerializer(serializer);
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Nieaktywni użytkownicy");
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
            Stage oldstage = (Stage) logoutButton.getScene().getWindow();
            oldstage.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void btnreconnectClicked(ActionEvent actionEvent) {
    }

    public void btnCancelConsultationClicked(ActionEvent actionEvent) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/yourconsultations.fxml"));
            AnchorPane root = fxmlLoader.load();
            final YourConsultationsWindow controller = fxmlLoader.getController();
            controller.setSerializer(serializer);
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Twoje konsultacje");
            stage.show();


        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public void btnRequestsClicked(ActionEvent actionEvent) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/tutorrequests.fxml"));
            AnchorPane root = fxmlLoader.load();
            final TutorConsultationRequests controller = fxmlLoader.getController();
            controller.setSerializer(serializer);
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Propozycje konsultacji");
            stage.show();


        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
