package com.example.tin.dto;

import com.example.tin.entity.Login;

import java.util.ArrayList;
import java.util.List;

public class RejectAccountsRequest {
        String type = "RejectAccountsRequest";
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

