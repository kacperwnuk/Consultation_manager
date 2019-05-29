package com.example.tin.entity;

import org.json.JSONObject;

public class Participant {
    String login;
    String name;
    String surname;

    public Participant() {
    }

    public Participant(JSONObject other) {
        try {
            login = other.getString("login");
            name = other.getString("name");
            surname = other.getString("surname");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public String getLogin() {
        return login;
    }

    public void setLogin(String login) {
        this.login = login;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }
}
