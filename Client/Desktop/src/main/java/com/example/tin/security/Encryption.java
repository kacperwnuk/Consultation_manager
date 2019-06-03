package com.example.tin.security;

import java.util.Arrays;
import java.util.Base64;

public class Encryption {
    String key = "adamsobieski1234adamsobieski1234";
    Aes256 aes = new Aes256();

    public Encryption()
    {

    }
    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
        System.out.println("Mam nowy klucz: " + key);
    }

    public String encrypt(String message)
    {
        try {

            String encrypted = aes.encrypt(message, key, key.getBytes());
            System.out.println(encrypted);
            return encrypted;
        } catch( Exception e) {
            e.printStackTrace();
            return "";
        }
    }
/*
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
*/

    public String decrypt(String message)
    {
        final byte[] inBytes = Base64.getDecoder().decode(message);
        message = inBytes.toString();
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < inBytes.length; i++)
            sb.append((char)(inBytes[i] ^ key.charAt(i % (key.length()))));
        String res = sb.toString();
        return(res);
    }


}
