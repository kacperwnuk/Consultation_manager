package com.example.tin.dto;

import com.example.tin.entity.Participant;

import java.util.ArrayList;
import java.util.List;

public class AllTutorsResponse {

    List<Participant> tutorsAccounts =  new ArrayList<>();

    public List<Participant> getTutorsAccounts() {
        return tutorsAccounts;
    }
}
