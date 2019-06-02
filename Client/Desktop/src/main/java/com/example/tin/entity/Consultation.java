package com.example.tin.entity;

import java.time.LocalDateTime;
import java.time.ZoneOffset;

public class Consultation {
    String id;
    long consultationDateStart;
    long consultationDateEnd;
    int consultationType;

    public ConsultationStatus getStatus() {
        return status;
    }

    public void setStatus(ConsultationStatus status) {
        this.status = status;
    }

    ConsultationStatus status;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    int room;
    Participant lecturer;
    Participant student;

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

    public int getRoom() {
        return room;
    }

    public void setRoom(int room) {
        this.room = room;
    }

    public Participant getLecturer() {
        return lecturer;
    }

    public void setLecturer(Participant lecturer) {
        this.lecturer = lecturer;
    }

    public Participant getStudent() {
        return student;
    }

    public void setStudent(Participant student) {
        this.student = student;
    }

    public LocalDateTime getStartDate(){
        return LocalDateTime.ofEpochSecond(consultationDateStart/1000,0, ZoneOffset.UTC);
    }

    public LocalDateTime getEndDate(){
        return LocalDateTime.ofEpochSecond(consultationDateEnd/1000,0, ZoneOffset.UTC);
    }

    @Override
    public String toString() {
        return getStartDate().getDayOfMonth() + "." + String.format("%02d", getStartDate().getMonth().getValue()) +
                " od: " + getStartDate().getHour() + ":" + String.format("%02d", getStartDate().getMinute())+
                " do: " + getEndDate().getHour() + ":" + String.format("%02d", getEndDate().getMinute())+
                ", tutor: " + lecturer.getName() + " " + lecturer.getSurname() +
                ", pokój: " + room  +
                ", STATUS: " + status;
    }
}
