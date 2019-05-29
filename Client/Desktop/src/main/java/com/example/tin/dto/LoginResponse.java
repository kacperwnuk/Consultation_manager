package com.example.tin.dto;

public class LoginResponse {
    boolean isValid;
    boolean isLecturer;

    public LoginResponse(boolean isValid, boolean isLecturer) {
        this.isValid = isValid;
        this.isLecturer = isLecturer;
    }

    public LoginResponse(boolean isValid) {
        this.isValid = isValid;
    }

    public boolean isValid() {
        return isValid;
    }

    public void setValid(boolean valid) {
        isValid = valid;
    }

    public boolean isLecturer() {
        return isLecturer;
    }

    public void setLecturer(boolean lecturer) {
        isLecturer = lecturer;
    }
}
