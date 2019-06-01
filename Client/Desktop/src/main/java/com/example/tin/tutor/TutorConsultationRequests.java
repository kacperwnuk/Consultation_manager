package com.example.tin.tutor;

import com.example.tin.Serializer;
import com.example.tin.dto.*;
import com.example.tin.entity.Consultation;
import com.example.tin.entity.Login;
import com.example.tin.entity.Participant;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;

import java.util.ArrayList;
import java.util.List;

public class TutorConsultationRequests {
    @FXML
    ListView<Consultation> consultationList;
    @FXML
    Button acceptButton;
    @FXML
    Button declineButton;

    private Serializer serializer;
    private ObservableList<Consultation> observableList;


    public void setSerializer(Serializer serializer) {
        this.serializer = serializer;

        try{
            setConsultations();
        }
        catch (Exception e){
            e.printStackTrace();
        }

    }

    private void setConsultations() {
        try{
            serializer.serializeAndSend(new UnconfirmedConsultationsRequest());
            UnconfirmedConsultationsResponse response = serializer.deserializeUnconfirmedConsultations();
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
        alert.setHeaderText("Przetwarzanie konsultacji nie powiodło się!");
        alert.showAndWait();
    }
    public void btnAcceptClicked(ActionEvent actionEvent) {
        Consultation con = consultationList.getSelectionModel().getSelectedItem();
        MenageConsultationRequest request = new MenageConsultationRequest();
        request.setType("AcceptConsultationRequest");
        request.setId(con.getId());
        try{
            serializer.serializeAndSend(request);
        }catch (Exception e){
            e.printStackTrace();
            showDialog();
        }


    }

    public void btnDeclineClicked(ActionEvent actionEvent) {
        Consultation con = consultationList.getSelectionModel().getSelectedItem();
        MenageConsultationRequest request = new MenageConsultationRequest();
        request.setType("RejectConsultationRequest");
        request.setId(con.getId());
        try{
            serializer.serializeAndSend(request);
        }catch (Exception e){
            e.printStackTrace();
            showDialog();
        }
    }


}
