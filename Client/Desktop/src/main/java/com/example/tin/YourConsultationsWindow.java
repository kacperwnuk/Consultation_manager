package com.example.tin;

import com.example.tin.dto.*;
import com.example.tin.entity.Consultation;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.stage.Stage;

import java.util.List;

public class YourConsultationsWindow {

    @FXML
    ListView<Consultation> consultationList;
    @FXML
    Button cancelButton;

    private Serializer serializer;
    private String login;
    private ObservableList<Consultation> observableList;

    @FXML
    private void initialize(){}
    public void setLogin(String login) {
        this.login = login;
        try{
            System.out.println(login);
            setConsultations();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    public void setSerializer(Serializer serializer) {
        this.serializer = serializer;
    }

    public void btnCancelClicked(ActionEvent actionEvent) {
        Consultation con = consultationList.getSelectionModel().getSelectedItem();
        try{
            serializer.serializeAndSend(new MenageConsultationRequest(con.getId(), "MenageConsultationRequest"));
            if (!serializer.deserialize()){
                showDialog();
            }
            else{
                ((Stage)cancelButton.getScene().getWindow()).close();
            }
        }catch (Exception e){
            e.printStackTrace();
            showDialog();
        }

    }

    private void setConsultations() {
        try{
            serializer.serializeAndSend(new UsersConsultationsRequest());
            ConsultationsResponse response = serializer.deserializeConsultations();
            if (response != null){
                List<Consultation> consList = response.getConsultations();
                if (consList != null && consList.size() != 0) {
                    observableList = FXCollections.observableList(consList);
                    consultationList.setItems(observableList);
                }
                else{
                    observableList.clear();
                }
            }
            else
                observableList.clear();
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }

    private void showDialog(){
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle("Błąd");
        alert.setHeaderText("Anulowanie konsultacji nie powiodło się!");
        alert.showAndWait();
    }
}
