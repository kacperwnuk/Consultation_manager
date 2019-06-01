package com.example.tin.dto;

import com.example.tin.entity.Consultation;

import java.util.ArrayList;
import java.util.List;

public class UnconfirmedConsultationsResponse {
    List<Consultation> consultations =  new ArrayList<>();

    public List<Consultation> getConsultations() {
        return consultations;
    }
}

