package com.example.tin.dto;

public class ConsultationReservationRequest {
    String id;
    String type = "ConsultationReservationRequest";
    String login;

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

    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public ConsultationReservationRequest(String id, String login) {
        this.id = id;
        this.login = login;
    }
}
