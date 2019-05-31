package com.example.tin.dto;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class MenageConsultationRequest {
    String id;
    //"AcceptConsultationRequest" lub "RejectConsultationRequest" lub "CancelConsultationRequest"
    String type;

    public MenageConsultationRequest(String id, String type) throws Exception {
        List<String> dopuszczalne = new ArrayList<>(Arrays.asList("AcceptConsultationRequest", "RejectConsultationRequest", "CancelConsultationRequest"));
        this.id = id;
        if (! dopuszczalne.contains(type))
            throw new Exception("Nie można przypisać takiego typu");
        this.type = type;
    }

    public MenageConsultationRequest() {
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}
