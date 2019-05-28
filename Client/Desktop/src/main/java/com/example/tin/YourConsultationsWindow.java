package com.example.tin;

import com.example.tin.dto.Consultation;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;

public class YourConsultationsWindow {

    @FXML
    ListView<Consultation> consultationList;
    @FXML
    Button cancelButton;

    private Serializer serializer;

    public void setSerializer(Serializer serializer) {
        this.serializer = serializer;
    }

    public void btnCancelClicked(ActionEvent actionEvent) {

    }
}
