package com.example.tin.dto;

public class LoginRequest {
    private int type = 1;
    private String login;
    private String password;

    public LoginRequest(String login, String password){
        this.login = login;
        this.password = password;
    }

    public String getLogin() {
        return login;
    }

    public String getPassword() {
        return password;
    }

    public int getType() {
        return type;
    }
}
