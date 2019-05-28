package com.example.tin.dto;

public class ConsultationsRequest {
    long consultationDateStart;
    String type = "DailyConsultationsListRequest";

    public long getConsultationDateStart() {
        return consultationDateStart;
    }

    public void setConsultationDateStart(long consultationDateStart) {
        this.consultationDateStart = consultationDateStart;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public ConsultationsRequest(long consultationDateStart) {
        this.consultationDateStart = consultationDateStart;
    }

    public ConsultationsRequest() {
    }
}
