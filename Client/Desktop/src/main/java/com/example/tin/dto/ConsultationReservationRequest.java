package com.example.tin.dto;

public class ConsultationReservationRequest {
    String id;
    String type = "ConsultationReservationRequest";

    public ConsultationReservationRequest() {
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

    public ConsultationReservationRequest(String id) {
        this.id = id;
    }
}
