package com.example.tin.dto;

public class LoginRequest {
    private String type = "LoginRequest";
    private String login;
    private String passwordHash;

    public LoginRequest(String login, String password){
        this.login = login;
        this.passwordHash = password;
    }

    public String getLogin() {
        return login;
    }

    public String getPasswordHash() {
        return passwordHash;
    }

    public String getType() {
        return type;
    }
}
