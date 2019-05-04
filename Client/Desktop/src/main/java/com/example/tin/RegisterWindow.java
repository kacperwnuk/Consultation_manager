package com.example.tin;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;


public class RegisterWindow {
    @FXML
    TextField loginTextField;
    @FXML
    TextField nameTextField;
    @FXML
    TextField surnameTextField;
    @FXML
    TextField emailTextField;
    @FXML
    PasswordField passwordTextField;
    @FXML
    PasswordField password2TextField;
    @FXML
    RadioButton studentRadioButton;
    @FXML
    RadioButton lecturerRadioButton;
    @FXML
    Button registerButton;

    private String login, name, surname, email, password, password2;
    private boolean isStudent;

    @FXML
    private void initialize() {
    }

    @FXML
    private void btnRegisterClicked() {
        System.out.println("Register!");
        login = loginTextField.getText();
        name = nameTextField.getText();
        surname = surnameTextField.getText();
        password = passwordTextField.getText();
        password2 = password2TextField.getText();
        email = emailTextField.getText();
        if (studentRadioButton.isPressed())
            isStudent = true;
        else if (lecturerRadioButton.isPressed())
            isStudent = false;
        showLoginWindow();
    }

    @FXML
    private void studentSelected() {
        lecturerRadioButton.setSelected(false);
    }

    @FXML
    private void lecturerSelected() {
        studentRadioButton.setSelected(false);
    }

    private void showLoginWindow() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/login.fxml"));
            AnchorPane root = fxmlLoader.load();
            final LoginWindow controller = fxmlLoader.getController();
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Login Window");
            stage.show();
            Stage oldstage = (Stage) registerButton.getScene().getWindow();
            oldstage.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}
