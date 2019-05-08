package Weteoes.Model.security;


import android.util.Base64;
import java.security.Key;
import java.security.KeyFactory;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import javax.crypto.Cipher;

import Decoder.BASE64Decoder;

public class RsaClass {
    //构建Cipher实例时所传入的的字符串，默认为"RSA/NONE/PKCS1Padding"
    private String B_PublicKey = ("MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA0pf6nAbz1e0q6gKxbdZUNvFsi5wn4hIPsb82dnac7o4Crfoz4KFc/MNavirwsjkCsNBTBPuFle5560yrPL5roXog4nfol/xAKi7D+zqJil+DUmNYqkN5gHnrPIT+r89WadJM4EKaOE/sKJ1dUF94VJnR+mD2k9WXa3YmW+eGxvPHbUh1aHFh1k1vgZOIBtNyXDDXH/sULQE1b+ZddMLdeIlrO0Wdvkg23mM76dSQmLH2WMF9XMgUUuHTUllMRwJdWQf/XAI8GLvEtMP88ZYsJso3c5z1VVi6Fmzqc/tJXKLBU4qT3NYUtBSkDP3lM2QV3W9zzlRIiplvQ8Fd90ZqVQIDAQAB");
    private String A_PrivateKey = ("MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQCn6L5afDofSb/ahgTO4kvz5UvZi9m8iczvmVydsP4lUZ5CoSlfhbSo7bzeiUl4oUwSdZ0W6GwXSjE+9PKqNbTu2dpQy8iX54dE/N18+9CHxrQec5YzNrFeOi72+Euo2OwJou7oKaNvbdnWQM8OHfWsjiKikK0Q3bQRvohcVkQEodbIERjgw7opFoPJxIlOV7duhvsC/krX2f+qoIP1ZUWUNtMEiLHGwnRj6eCKAcim5s8EGHlN+RAU9sgFGZsbQpm50QicpY8XAEPVMLq5CNGNmqFsx0Altj9De8lszBsIYpxkICFciRMw+cSp03ZuaIp/9TV+fI+5JfbF02JJNu5tAgMBAAECggEAQtQbjyAKchGETpEwsLbYzAXjHn7O9n9SFbrQZeLgBDJr7tD+CorI0MNufJPfridkg6RUFZ4EB3D8ELalLqGZlccXYTj6aZs493g9H1WKNcAcSFJw4YlPJtW5g4pncpiDuYIj3DtWVS8/mErLHi9GbJtVpaY3e5MB7F4NH9Ml10F9T6C+Iru38422hgWELxZgBO9tCnvBMBbSEyLecp5UesusmZ1Xr/H8RhlPnkuuNwtNBO74aqDj9hvT7Vl0ArSHHfZp0YdVDpIXH9tmynlfmrN6OUcn4zLk9db9OUdez2GY2JUSJEHHuGmIC2m4on0vxEBcVBgofymmtzv4gEfo8QKBgQDbk57DNezfhws/ndl0VHJh7DHTB47M1usk1LZh5b+WeVB5R1uM5pjpN11z5eb8dObqp/6w91xS2FBXJSuMWuQ6HZzCr8xMwlujAjdrYrDPe5rWYXjMwGeAwKBjmwPTgdYwbrfJof2Qrg6Av8rtAHNDofyhhpG3CdSa205LcJl04wKBgQDDwwzL9MhhfZixE0OWKudYTZ1pDYaKLNK5mrRfpFkZ1gA6M8tXEt3uVp4IxemaRZ0UXqcO3m5tyfrxZKWdGT40Fo5BDsucfLHDUAY9LojnI4RlmDp1BX3GAI+ZoxlYiVTyv5sJeZL4ESM+DjYxc2WmU/B8NodchOX4d6ocp2HAbwKBgHNpeSZkHrgy1B/BCT5S8Lg1nM6uB0n1oSz/vUlhqD0gUMMeVamOv0q99hnn+mwxyfoHCSDdM6K73iaf++7PC2zcibvvCTRDaEUa8iQ4gHTeJDmQjB0a+Iw9M1CHdxBiC0HzwBh0U8ILKsZTiQbfmLYw24fPIqIRwbUPlmyip5Y/AoGBALRDG7mDwjDjsoL8NjRFdZp+fgCKj+UUuUZoCsg3UkTUJolxwECCAxLBd+ykMiP5Dlf/gN3UPOOkJgu6njY3VGwqiPunYB7NQ/OR8OzNuQr+TaAvuUSgtdxqD9Ftup0oeKy/e0gSRx9eyJEQDR8kH+o1STFYFPVA+3L83gxcpUrJAoGBANTmKUgbMe60Q7vKyGkW/7Dyid2P4+RrOuKxEVhKTJNJGwugsTMaSp8xTcnbfV44gDTwWqChjZyV6rqU/tS4ZRdBbkhlu3yrammQItniP/vDQZXcrKO0wkdNNM0oUGIXYlFzswY9mYoxNZyk/ODWr9wm8JgfALXkj6/M7kds2lid");
    private int sBase64Mode = Base64.DEFAULT; //进行Base64转码时的flag设置，默认为Base64.DEFAULT

    private PublicKey getPublicKey(String key){
        try{
            byte[] keyBytes;
            keyBytes = (new BASE64Decoder()).decodeBuffer(key);
            X509EncodedKeySpec keySpec = new X509EncodedKeySpec(keyBytes);
            KeyFactory keyFactory = KeyFactory.getInstance("RSA");
            PublicKey publicKey = keyFactory.generatePublic(keySpec);
            return publicKey;
        }
        catch (Exception error){
            error.printStackTrace();
            return null;
        }
    }
    private PrivateKey getPrivateKey(String key){
        try{
            byte[] keyBytes;
            keyBytes = (new BASE64Decoder()).decodeBuffer(key);
            PKCS8EncodedKeySpec keySpec = new PKCS8EncodedKeySpec(keyBytes);
            KeyFactory keyFactory = KeyFactory.getInstance("RSA");
            PrivateKey privateKey = keyFactory.generatePrivate(keySpec);
            return privateKey;
        }
        catch (Exception error){
            error.printStackTrace();
            return null;
        }
    }
    /*
        产生密钥对
        @param keyLength
        密钥长度，小于1024长度的密钥已经被证实是不安全的，通常设置为1024或者2048，建议2048
     */
    public KeyPair getNewKey(int keyLength){
        KeyPair keyPair = null;
        try {
            KeyPairGenerator keyPairGenerator = KeyPairGenerator.getInstance("RSA");
            //设置密钥长度
            keyPairGenerator.initialize(keyLength);
            //产生密钥对
            keyPair = keyPairGenerator.generateKeyPair();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return keyPair;
    }

    private String RSA_w(String data, Key key, int encode){ //1加密 0解密
        String result = null;
        try{
            byte[] dataByte = data.getBytes();
            if (encode == 2) { //解密
                dataByte = Base64.decode(data, sBase64Mode);
            }
            Cipher cipher = Cipher.getInstance("RSA/ECB/PKCS1Padding");
            cipher.init(encode,key);  //初始化Cipher，mode指定是加密还是解密，key为公钥或私钥
            byte[] end = cipher.doFinal(dataByte);
            if (encode == 2) { //解密
                result = new String(end);
            }else{
                result = new String(Base64.encode(end, sBase64Mode));
            }
        }
        catch (Exception error){
            error.printStackTrace();
        }
        return result;
    }
    public String byPublicAsEncode(String data,String key){
        if(key == null || key == ""){ key = B_PublicKey; }
        PublicKey key_ = getPublicKey(key);
        return RSA_w(data, key_,1);
    }
    public String byPrivateAsUnEncode(String data,String key){
        if(key == null || key == ""){ key = A_PrivateKey; }
        PrivateKey key_ = getPrivateKey(key);
        return RSA_w(data, key_,2);
    }
}
