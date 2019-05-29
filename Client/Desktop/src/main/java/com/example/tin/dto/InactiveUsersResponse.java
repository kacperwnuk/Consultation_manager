package com.example.tin.dto;

import java.util.ArrayList;
import java.util.List;

public class InactiveUsersResponse {
    List<Participant> inactiveAccounts =  new ArrayList<>();

    public List<Participant> getInactiveAccounts() {
        return inactiveAccounts;
    }
}
