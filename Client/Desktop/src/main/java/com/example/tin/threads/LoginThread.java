package com.example.tin.threads;

import com.example.tin.LoginWindow;
import com.example.tin.MainPage;
import com.example.tin.Serializer;
import com.example.tin.dto.*;
import com.example.tin.entity.Login;
import com.example.tin.entity.Participant;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginThread extends Thread  {
    private Serializer serializer;
    private Stage oldstage;
    private String login;
    private String password;
    private LoginResponse response;
    private LoginWindow window;

    public LoginResponse getResponse(){
        return response;
    }

    public LoginThread(Serializer serializer, Stage oldstage, String login, String password, LoginWindow window){
        this.serializer = serializer;
        this.oldstage = oldstage;
        this.login = login;
        this.password = password;
        this.window = window;
    }

    public void run(){
        try {
            serializer.serializeAndSend(new LoginRequest(login, password));
            response = serializer.deserializeLoginResponse();
            Platform.runLater( () -> {
                if (response.isValid())
                    if (response.isLecturer())
                        showTutorMainWindow();
                    else
                        showMainWindow();
                else
                    showDialog();
                window.indicator.setVisible(false);
            });
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
    private void showMainWindow() {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("/main.fxml"));
            AnchorPane root = fxmlLoader.load();
            final MainPage controller = fxmlLoader.getController();
            controller.setSerializer(serializer);
            Scene scene = new Scene(root);
            Stage stage = new Stage();
            stage.setScene(scene);
            stage.setTitle("TIN Main menu");
            stage.setOnHidden(e -> controller.disconnect());
            stage.show();
            oldstage.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    private void showTutorMainWindow(){
        System.out.println("TODO: Wyświetlenie okna tutora");
        TESTDEBUG();
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
            //NIEAKTYWNI UZYTKOWNICY
            serializer.serializeAndSend(new InactiveUsersRequest(2)); //rola = 1 - lecturer;     rola = 2 - student
            InactiveUsersResponse list = serializer.deserializeInactiveUsersResponse();
            for (Participant user : list.getInactiveAccounts()){
                System.out.print(user.getName() + "" + user.getSurname());
            }
            //AKCEPTACJA I ODRZUCENIE UZYTKOWNIKOW
            // w przypadku RejectAccountsRequest dokładnie tak samo jak w AcceptAccountRequest
            // w akcetacji i odrzucaniu kont mozliwe wysylanie kilku loginow na raz - w jednym zapytaniu
            AcceptAccountsRequest acceptRequest = new AcceptAccountsRequest();
            acceptRequest.getLogins().add(new Login(list.getInactiveAccounts().get(/*przykladowy index*/0).getLogin()));
            serializer.serializeAndSend(acceptRequest);
            if (serializer.deserialize())
                System.out.println("Udało się akceptować");

            //AKCEPTACJA I ODRZUCENIE KONSULTACJI ZAPROPONOWANYCH PRZEZ STUDENTOW
            // "AcceptConsultationRequest" i "RejectConsultationRequest"
            serializer.serializeAndSend(new MenageConsultationRequest("5cf181d6e695bf2295443083", "RejectConsultationRequest"));
            serializer.serializeAndSend(new MenageConsultationRequest("to_jest_id_konsultacji", "AcceptConsultationRequest"));
        }
        catch (Exception e){
            System.out.print("COŚ SIĘ ZJEBAŁO:  ");
            e.printStackTrace();
        }

    }
}
