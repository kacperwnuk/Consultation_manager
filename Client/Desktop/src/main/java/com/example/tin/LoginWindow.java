package com.example.tin;

import com.example.tin.dto.*;
import javafx.fxml.FXMLLoader;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.List;

public class LoginWindow {
    @FXML
    TextField loginTextField;
    @FXML
    PasswordField passwordTextField;
    @FXML
    Button loginButton;
    @FXML
    Button registerButton;

    private String login;
    private String password;
    private Serializer serializer = new Serializer();

    @FXML
    private void btnLoginClicked() {
        login = loginTextField.getText();
        password = passwordTextField.getText();
        System.out.println("Login: " + login);
        System.out.println("Password: " + password);
        try {
            serializer.serializeAndSend(new LoginRequest(login, password));
            LoginResponse response = serializer.deserializeLoginResponse();
            if (response.isValid())
                if (response.isLecturer())
                    showTutorMainWindow();
                else
                    showMainWindow();
            else
                showDialog();
        }
        catch (Exception e){
            e.printStackTrace();
        }

    }

    @FXML
    private void btnRegisterClicked() {
        System.out.println("Przycisk rejestracji");
        showRegisterWindow();
    }

    private void showRegisterWindow() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/register.fxml"));
            AnchorPane root = fxmlLoader.load();
            final RegisterWindow controller = fxmlLoader.getController();
            controller.setSerializer(serializer);
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Register Window");
            stage.show();
            Stage oldstage = (Stage) loginButton.getScene().getWindow();
            oldstage.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void showMainWindow() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/main.fxml"));
            AnchorPane root = fxmlLoader.load();
            final MainPage controller = fxmlLoader.getController();
            controller.setSerializer(serializer);
            controller.setLogin(login);
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("TIN Main menu");
            stage.setOnHidden(e -> controller.disconnect());
            stage.show();
            Stage oldstage = (Stage) loginButton.getScene().getWindow();
            oldstage.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private void showTutorMainWindow(){
        System.out.println("TODO: Wyświetlenie okna tutora");

        TESTDEBUG(); // TO REMOVE, JUST FOR TESTS
        //TODO
    }

    private void showDialog(){
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Błąd");
        alert.setHeaderText("Błąd logowania");
        alert.showAndWait();
    }

    private void TESTDEBUG(){
        try {
            serializer.serializeAndSend(new InactiveUsersRequest());
            InactiveUsersResponse list = serializer.deserializeInactiveUsersResponse();
            for (Participant user : list.getInactiveAccounts()){
                System.out.print(user.getName() + "" + user.getSurname());
            }
        }
        catch (Exception e){
            System.out.print("COŚ SIĘ ZJEBAŁO:  ");
            e.printStackTrace();
        }

    }

}
