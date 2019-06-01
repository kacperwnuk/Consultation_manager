package com.example.tin;

import com.example.tin.entity.Consultation;
import com.example.tin.dto.ConsultationReservationRequest;
import com.example.tin.dto.ConsultationsRequest;
import com.example.tin.dto.ConsultationsResponse;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.stage.Stage;

import java.time.LocalDate;
import java.util.List;

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
    private ObservableList<Consultation> observableList;

    @FXML
    private void initialize() {
        dateBox.valueProperty().addListener((ov, oldValue, newValue) -> {
            setConsultations();
        });
    }
    public void setSerializer(Serializer serializer){
        this.serializer = serializer;
        dateBox.setValue(LocalDate.now());
        setConsultations();
    }

    public void filterButtonClicked(ActionEvent actionEvent) {
    }

    public void refreshButtonClicked(ActionEvent actionEvent) {
        setConsultations();
    }

    public void reserveButtonClicked(ActionEvent actionEvent) {
        Consultation con = consultationList.getSelectionModel().getSelectedItem();
        try{
            serializer.serializeAndSend(new ConsultationReservationRequest(con.getId()));
            if (!serializer.deserialize()){
                showDialog();
            }
            else{
                ((Stage)reserveButton.getScene().getWindow()).close();
            }
        }catch (Exception e){
            e.printStackTrace();
            showDialog();
        }
    }

    public void backButtonClicked(ActionEvent actionEvent) {
        ((Stage)backButton.getScene().getWindow()).close();
    }

    private void setConsultations() {
        try{
            serializer.serializeAndSend(new ConsultationsRequest(dateBox.getValue().toEpochDay()*86400000));
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
        alert.setHeaderText("Rezerwacja konsultacji nie powiodła się!");
        alert.showAndWait();
    }
}
