package com.example.tin.dto;

public class CancelConsultationRequest {
    String id;
    String login;
    String type = "CancelConsultationRequest";
    public CancelConsultationRequest(String id, String login) {
        this.id = id;
        this.login = login;
    }

    public CancelConsultationRequest() {
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}
