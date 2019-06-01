package com.example.tin.dto;

public class InactiveUsersRequest {
    String type = "InactiveUsersRequest";
    int rola; //1-lecturer ; 2-student

    public InactiveUsersRequest(int rola) {
        this.rola = rola;
    }

    public int getRola() {
        return rola;
    }

    public void setRola(int rola) {
        this.rola = rola;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}
