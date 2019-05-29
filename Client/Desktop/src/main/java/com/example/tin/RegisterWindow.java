package com.example.tin;

import com.example.tin.dto.RegisterRequest;
import com.example.tin.entity.User;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import org.json.JSONException;

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
    Serializer serializer;

    public void setSerializer(Serializer serializer) {
        this.serializer = serializer;
    }

    @FXML
    private void initialize() {
    }

    @FXML
    private void btnRegisterClicked() throws IOException, JSONException {
        readValuesFromIputs();
        if(studentRadioButton.isSelected())
            role = 2;
        else if(lecturerRadioButton.isSelected())
            role = 1;
        int validationResult = validate();
        System.out.println(validationResult);
        if(validationResult == 0) {
            registerUser();
            if (serializer.deserialize())
                showLoginWindow();
            else
                showDialog();
        }
        else
            handleRegisterError(validationResult);
        if (studentRadioButton.isPressed())
            role = 2;
        else if (lecturerRadioButton.isPressed())
            role = 1;
    }

    @FXML
    private void studentSelected() {
        lecturerRadioButton.setSelected(false);
    }

    @FXML
    private void lecturerSelected() {
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

    private void registerUser() throws IOException     //Ma być bool - zwracać status rejestracji
    {
        User newUser = new User(login, name, surname, email, password, role);
        serializer.serializeAndSend(new RegisterRequest(login,password,email,name,surname,role));
    }

    private void handleRegisterError(int error)
    {
        String messageToUser = "";
        System.out.println("Error type: " + error);
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

    private void showDialog(){
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Ups");
        alert.setHeaderText("Coś poszło nie tak!");
        alert.showAndWait();
    }

    private  void readValuesFromIputs(){
        login = loginTextField.getText();
        name = nameTextField.getText();
        surname = surnameTextField.getText();
        password = passwordTextField.getText();
        password2 = password2TextField.getText();
        email = emailTextField.getText();
    }
}
