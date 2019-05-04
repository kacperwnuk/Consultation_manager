package com.example.tin;

import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;


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
    private int role;

    @FXML
    private void initialize()
    {
    }

    @FXML
    private void btnRegisterClicked()
    {
        login = loginTextField.getText();
        name = nameTextField.getText();
        surname = surnameTextField.getText();
        password = passwordTextField.getText();
        password2 = password2TextField.getText();
        email = emailTextField.getText();
        if(studentRadioButton.isSelected())
            role = 0;
        else if(lecturerRadioButton.isSelected())
            role = 1;

        int validationResult = validate();
        System.out.println(validationResult);
        if(validationResult == 0) {
            registerUser();
            //Tutaj sprawdzenie czy jest dobrze zarejestrowany - tylko wtedy wchodzi do showLoginWindow
            showLoginWindow();
        }
        else
            handleRegisterError(validationResult);
    }

    @FXML
    private void studentSelected()
    {
        lecturerRadioButton.setSelected(false);
    }

    @FXML
    private void lecturerSelected()
    {
        studentRadioButton.setSelected(false);
    }

    private int validate()
    {
        //LOGIN Validation
        if(login.length() < 8)
            return 1;   //Wrong login
        //Name validation
        else if(name.length() < 3)
            return 2;   //Wronh name
        //Surname validation
         else if(surname.length() < 3)
            return 3;   //Wrong surname
        //EMAIL Validation
        Pattern pattern = Pattern.compile("^.+@.+\\..+$");
        Matcher matcher = pattern.matcher(email);
        if(!matcher.find())
            return 4;   //Wrong email
        //Password lenght validation
        else if(password.length() < 8)
            return 5;   //Pass to short
        //Two identical passwords validation
        else if(!password.equals(password2))
            return 6;   //Passwords not the same
        //Role validation
        else if((!studentRadioButton.isSelected() && !lecturerRadioButton.isSelected()))
            return 7;   //Role not selected
        else
            return 0;   //Status OK
    }

    private void registerUser()     //Ma być bool - zwracać status rejestracji
    {
        User newUser = new User(login, name, surname, email, password, role);
        //parsuj do jsona
        //wyślij do serwera
        //przetwórz odpowiedź
        //zwróć status
    }

    private void handleRegisterError(int error)
    {
        String messageToUser = "";
        System.out.println("Erorr type: " + error);
        switch (error)
        {
            case 1: { messageToUser =  "Wprowadź poprawny login! (Min. 8 znaków)";
            loginTextField.clear(); break; }
            case 2: { messageToUser = "Wprowadź imię!";
            nameTextField.clear(); break;}
            case 3: { messageToUser = "Wprowadź nazwisko!";
            surnameTextField.clear(); break;}
            case 4: { messageToUser = "Niepoprawny adres e-mail!";
            emailTextField.clear(); break; }
            case 5: { messageToUser = "Hasło zbyt krótkie (Min. 8 znaków)"; break; }
            case 6: { messageToUser = "Wprowadzone hasła nie są identyczne"; break; }
            case 7: { messageToUser = "Wybierz rolę"; break;}
        }
        passwordTextField.clear();
        password2TextField.clear();
        showErrorPopup(messageToUser);
    }

    private void showErrorPopup(String message)
    {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Błąd rejestracji");
        alert.setContentText(message);
        alert.setHeaderText(null);
        alert.showAndWait();
    }

    private void showLoginWindow()
    {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("../tin/login.fxml"));
            AnchorPane root = fxmlLoader.load();
            final LoginWindow controller = fxmlLoader.getController();
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("Login Window");
            stage.show();
            Stage oldstage = (Stage) registerButton.getScene().getWindow();
            oldstage.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }







}
