package com.example.tin;

public class User {
    private String login;
    private String name;
    private String surname;
    private String email;
    private String password;
    private int role; //0-student; 1-lecturer

    public User(String toLogin, String toName, String toSurname, String toEmail, String toPassword, int toRole)
    {
        login = toLogin;
        name = toName;
        surname = toSurname;
        email = toEmail;
        password = toPassword;
        role = toRole;
    }

    private boolean register(String json) {
        //kod rejestracji na serwerze
        return true;
    }

    private String parseToJson()
    {
        //kod parsowania do JSON
        return "Do zrobienia przez Sławka leniwego chuja";
    }
}
