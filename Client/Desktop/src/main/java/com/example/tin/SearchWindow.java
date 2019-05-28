package com.example.tin;

import com.example.tin.dto.Consultation;
import com.example.tin.dto.ConsultationsRequest;
import com.example.tin.dto.ConsultationsResponse;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.ListView;
import org.json.JSONException;

import java.io.IOException;
import java.time.LocalDate;

public class SearchWindow {
    @FXML
    ListView<Consultation> consultationList;
    @FXML
    Button filterButton;
    @FXML
    Button refreshButton;
    @FXML
    Button reserveButton;
    @FXML
    Button backButton;
    @FXML
    CheckBox showReservedCheckBox;
    @FXML
    DatePicker dateBox;

    private Serializer serializer;

    @FXML
    private void initialize() {
        dateBox.setValue(LocalDate.now());

    }

    public void setSerializer(Serializer serializer){
        this.serializer = serializer;
    }

    public void filterButtonClicked(ActionEvent actionEvent) {
    }

    public void refreshButtonClicked(ActionEvent actionEvent) {
        setConsultations();
    }

    public void reserveButtonClicked(ActionEvent actionEvent) {
    }

    public void backButtonClicked(ActionEvent actionEvent) {
    }

    private void setConsultations() {
        try{
            serializer.serializeAndSend(new ConsultationsRequest(dateBox.getValue().toEpochDay()*86400000));
            ConsultationsResponse response = serializer.deserializeConsultations();
            ObservableList<Consultation> observableList = FXCollections.observableList(response.getConsultations());
            consultationList.setItems(observableList);
        }
        catch(Exception e){
            e.printStackTrace();
        }

    }
}
