package com.example.tin;

import javafx.fxml.FXMLLoader;
import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

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

    @FXML
    private void btnLoginClicked()
    {
        login = loginTextField.getText();
        password = passwordTextField.getText();
        System.out.println("Login: " + login);
        System.out.println("Password: " + password);
        showMainWindow();
    }

    @FXML
    private void btnRegisterClicked()
    {
        System.out.println("Przycisk rejestracji");
        showRegisterWindow();
    }

    private void showRegisterWindow()
    {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/register.fxml"));
            AnchorPane root = fxmlLoader.load();
            final RegisterWindow controller = fxmlLoader.getController();

            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Register Window");
            stage.show();
            Stage oldstage = (Stage) loginButton.getScene().getWindow();
            oldstage.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void showMainWindow()
    {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/sample.fxml"));
            AnchorPane root = fxmlLoader.load();
            final MainWindow controller = fxmlLoader.getController();
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("TIN Main Window");
            stage.show();
            Stage oldstage = (Stage) loginButton.getScene().getWindow();
            oldstage.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

}
