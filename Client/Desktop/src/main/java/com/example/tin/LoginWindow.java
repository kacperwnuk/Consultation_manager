package com.example.tin;

import com.example.tin.dto.*;
import com.example.tin.entity.Login;
import com.example.tin.entity.Participant;
import com.example.tin.threads.LoginThread;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.json.JSONException;

import java.io.IOException;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class LoginWindow {
    @FXML
    TextField loginTextField;
    @FXML
    PasswordField passwordTextField;
    @FXML
    Button loginButton;
    @FXML
    Button registerButton;
    @FXML
    public ProgressIndicator indicator;

    private String login;
    private String password;
    private Serializer serializer = new Serializer();

    @FXML
    private void btnLoginClicked() {
        login = loginTextField.getText();
        password = passwordTextField.getText();
        System.out.println("Login: " + login);
        System.out.println("Password: " + password);

        LoginThread thread = new LoginThread(serializer, (Stage) loginButton.getScene().getWindow(), login, password, this);
        indicator.setVisible(true);
        thread.setDaemon(true);
        thread.start();
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
}
