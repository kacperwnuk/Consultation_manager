package com.example.tin.security;

import java.util.Arrays;
import java.util.Base64;

public class Encryption {
    String key = "ABC123EF";
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
        System.out.println("Po basie: " + Arrays.toString(inBytes));
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < inBytes.length; i++)
            sb.append((char)(inBytes[i] ^ key.charAt(i % (key.length()))));
        String res = sb.toString();
        System.out.println("Wiadomość odszyfrowana: " + res);
        return(res);
    }


}
