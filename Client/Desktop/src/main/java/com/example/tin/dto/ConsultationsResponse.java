package com.example.tin.dto;

import java.util.ArrayList;
import java.util.List;


public class ConsultationsResponse {
    List<Consultation> consultations =  new ArrayList<>();

    public List<Consultation> getConsultations() {
        return consultations;
    }
}
