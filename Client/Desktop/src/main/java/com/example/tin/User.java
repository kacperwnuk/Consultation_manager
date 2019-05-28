package com.example.tin;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.LinkedHashMap;
import java.util.Map;
import org.json.JSONArray;
import org.json.JSONObject;

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

}
