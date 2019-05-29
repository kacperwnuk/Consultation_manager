package com.example.tin.dto;

import java.util.ArrayList;
import java.util.List;

public class AcceptAccountsRequest {
    String type = "AcceptAccountsRequest";
    List<Login> logins = new ArrayList<>();

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public List<Login> getLogins() {
        return logins;
    }

    public void setLogins(List<Login> logins) {
        this.logins = logins;
    }
}
