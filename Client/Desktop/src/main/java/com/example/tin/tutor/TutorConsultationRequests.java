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
import javafx.scene.control.SelectionMode;

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
        alert.setHeaderText("Anulowanie konsultacji nie powiodło się!");
        alert.showAndWait();
    }
    public void btnAcceptClicked(ActionEvent actionEvent) {
        /*
        List<Login> logins = new ArrayList<Login>();
        List<Participant> selectedUsers = userList.getSelectionModel().getSelectedItems();
        if(selectedUsers != null && selectedUsers.size() != 0) {
            for(Participant p : selectedUsers){
                logins.add(new Login(p.getLogin()));
            }
        }
        AcceptAccountsRequest request = new AcceptAccountsRequest();
        request.setLogins(logins);
        try{
            serializer.serializeAndSend(request);
        } catch (Exception e){
            e.printStackTrace();
        }
*/
    }

    public void btnDeclineClicked(ActionEvent actionEvent) {
        /*
        List<Login> logins = new ArrayList<Login>();
        List<Participant> selectedUsers = userList.getSelectionModel().getSelectedItems();
        if(selectedUsers != null && selectedUsers.size() != 0) {
            for(Participant p : selectedUsers){
                logins.add(new Login(p.getLogin()));
            }
        }
        RejectAccountsRequest request = new RejectAccountsRequest();
        request.setLogins(logins);
        try{
            serializer.serializeAndSend(request);
        } catch (Exception e){
            e.printStackTrace();
        }
*/
    }


}
