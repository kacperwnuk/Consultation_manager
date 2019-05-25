package com.example.tin;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.ListView;

public class SearchWindow {
    @FXML
    ListView<String> consultationList;
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

    public void setSerializer(Serializer serializer){
        this.serializer = serializer;
    }

    public void filterButtonClicked(ActionEvent actionEvent) {
    }

    public void refreshButtonClicked(ActionEvent actionEvent) {
    }

    public void reserveButtonClicked(ActionEvent actionEvent) {
    }

    public void backButtonClicked(ActionEvent actionEvent) {
    }
}
