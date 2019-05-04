package entity;


import java.time.LocalDateTime;

public class Consultation {

    private String id;
    private User tutor;
    private User student;
    private LocalDateTime date;
    private LocalDateTime consultationStartTime;
    private LocalDateTime consultationEndTime;
    private String room;

    public Consultation(){

    }

    public Consultation(String id, User tutor, User student, LocalDateTime date, LocalDateTime consultationStartTime, LocalDateTime consultationEndTime, String room) {
        this.id = id;
        this.tutor = tutor;
        this.student = student;
        this.date = date;
        this.consultationStartTime = consultationStartTime;
        this.consultationEndTime = consultationEndTime;
        this.room = room;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public User getTutor() {
        return tutor;
    }

    public void setTutor(User tutor) {
        this.tutor = tutor;
    }

    public User getStudent() {
        return student;
    }

    public void setStudent(User student) {
        this.student = student;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public LocalDateTime getConsultationStartTime() {
        return consultationStartTime;
    }

    public void setConsultationStartTime(LocalDateTime consultationStartTime) {
        this.consultationStartTime = consultationStartTime;
    }

    public LocalDateTime getConsultationEndTime() {
        return consultationEndTime;
    }

    public void setConsultationEndTime(LocalDateTime consultationEndTime) {
        this.consultationEndTime = consultationEndTime;
    }


    public String getRoom() {
        return room;
    }

    public void setRoom(String room) {
        this.room = room;
    }


    @Override
    public String toString() {
        return "Consultation{" +
                "id='" + id + '\'' +
                ", tutor='" + tutor + '\'' +
                ", student='" + student + '\'' +
                ", date=" + date +
                ", consultationStartTime=" + consultationStartTime +
                ", consultationEndTime=" + consultationEndTime +
                ", room=" + room +
                '}';
    }


}
