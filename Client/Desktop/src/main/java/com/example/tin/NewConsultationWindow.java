package com.example.tin;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextField;

public class NewConsultationWindow {

    @FXML
    DatePicker dateBox;
    @FXML
    TextField startTimeBox;
    @FXML
    TextField endTimeBox;
    @FXML
    TextField roomBox;
    @FXML
    Button addButton;

    private Serializer serializer;

    public void setSerializer(Serializer serializer){
        this.serializer = serializer;
    }

    public void addButtonClicked(ActionEvent actionEvent) {
    }
}
