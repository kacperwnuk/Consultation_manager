package com.example.tin.dto;

public class UsersConsultationsRequest {
    String login;
    String type = "UsersConsultationsRequest";

    public UsersConsultationsRequest(String login) {
        this.login = login;
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
