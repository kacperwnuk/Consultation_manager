package com.example.tin.security;

public class Encryption {
    String key = "adamsobieski1234";
    Aes256 aes = new Aes256();

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }

    public String encrypt(String message)
    {
        try {
            System.out.println("Szyfruję wiadomosc: ");
            System.out.println(message);
            String encrypted = aes.encrypt(message, key);
            System.out.println("Szyfrogram: ");
            System.out.println(encrypted);
            return encrypted;
        } catch( Exception e) {
            e.printStackTrace();
            return "";
        }
    }

    public String decrypt(String message)
    {
        try {
            String decrypted =  aes.decrypt(message, key);
            System.out.println("Odszyfrowana wiadomosc: " + decrypted);
            return decrypted;


        } catch (Exception e) {
            e.printStackTrace();
            return "";
        }
    }



}
