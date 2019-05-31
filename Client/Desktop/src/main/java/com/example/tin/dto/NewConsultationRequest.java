package com.example.tin.dto;

public class NewConsultationRequest {
    long consultationDateStart;
    long consultationDateEnd;
    int room;
    String tutor; //login Tutora
    String type = "NewConsultationRequest";

    public NewConsultationRequest(long consultationDateStart, long consultationDateEnd, String tutor, int room) {
        this.consultationDateStart = consultationDateStart;
        this.consultationDateEnd = consultationDateEnd;
        this.room = room;
        this.tutor = tutor;
    }

    public String getTutor() {
        return tutor;
    }

    public void setTutor(String tutor) {
        this.tutor = tutor;
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
