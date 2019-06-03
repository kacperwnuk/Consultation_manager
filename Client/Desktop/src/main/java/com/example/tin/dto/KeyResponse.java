package com.example.tin.dto;

public class KeyResponse {

    public KeyResponse(boolean valid, String tokey)
    {
        isValid = valid;
        key = tokey;
    }

    public boolean isValid() {
        return isValid;
    }

    public void setValid(boolean valid) {
        isValid = valid;
    }

    boolean isValid;
    String key;

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }
}
