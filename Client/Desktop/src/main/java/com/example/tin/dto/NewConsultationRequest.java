package com.example.tin.dto;

public class NewConsultationRequest {
    long consultationDateStart;
    long consultationDateEnd;
    int consultationType = 1;
    String consultationCreatorLogin;
    int room;
    String type = "NewConsultationRequest";

    public NewConsultationRequest(long consultationDateStart, long consultationDateEnd, int consultationType, String consultationCreatorLogin, int room) {
        this.consultationDateStart = consultationDateStart;
        this.consultationDateEnd = consultationDateEnd;
        this.consultationType = consultationType;
        this.consultationCreatorLogin = consultationCreatorLogin;
        this.room = room;
    }

    public long getConsultationDateStart() {
        return consultationDateStart;
    }

    public void setConsultationDateStart(long consultationDateStart) {
        this.consultationDateStart = consultationDateStart;
    }

    public long getConsultationDateEnd() {
        return consultationDateEnd;
    }

    public void setConsultationDateEnd(long consultationDateEnd) {
        this.consultationDateEnd = consultationDateEnd;
    }

    public int getConsultationType() {
        return consultationType;
    }

    public void setConsultationType(int consultationType) {
        this.consultationType = consultationType;
    }

    public String getConsultationCreatorLogin() {
        return consultationCreatorLogin;
    }

    public void setConsultationCreatorLogin(String consultationCreatorLogin) {
        this.consultationCreatorLogin = consultationCreatorLogin;
    }

    public int getRoom() {
        return room;
    }

    public void setRoom(int room) {
        this.room = room;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}
