package com.example.tin.dto;

public class KeyConfirmationResponse {
    public KeyConfirmationResponse(boolean valid)
    {
        isValid = valid;

    }

    public boolean isValid() {
        return isValid;
    }

    public void setValid(boolean valid) {
        isValid = valid;
    }

    boolean isValid;

}
