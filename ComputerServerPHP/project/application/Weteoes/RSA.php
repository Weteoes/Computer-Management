<?php
namespace Weteoes;
class RsaClass{
    private static $PRIVATE_KEY;
    private static $B_PUBLIC_KEY = "-----BEGIN PUBLIC KEY-----\nMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA0pf6nAbz1e0q6gKxbdZU\nNvFsi5wn4hIPsb82dnac7o4Crfoz4KFc/MNavirwsjkCsNBTBPuFle5560yrPL5r\noXog4nfol/xAKi7D+zqJil+DUmNYqkN5gHnrPIT+r89WadJM4EKaOE/sKJ1dUF94\nVJnR+mD2k9WXa3YmW+eGxvPHbUh1aHFh1k1vgZOIBtNyXDDXH/sULQE1b+ZddMLd\neIlrO0Wdvkg23mM76dSQmLH2WMF9XMgUUuHTUllMRwJdWQf/XAI8GLvEtMP88ZYs\nJso3c5z1VVi6Fmzqc/tJXKLBU4qT3NYUtBSkDP3lM2QV3W9zzlRIiplvQ8Fd90Zq\nVQIDAQAB\n-----END PUBLIC KEY-----";
    // function __construct($pubKey = '123', $privKey = '') {
    //     self::$B_PUBLIC_KEY = $pubKey;
    //     self::$PRIVATE_KEY = $privKey;
    // }

    /**
     * Decode a string with URL-safe Base64.
     *
     * @param string $input A Base64 encoded string
     *
     * @return string A decoded string
     */
    public static function urlsafeB64Decode($input)
    {
        // $remainder = strlen($input) % 4;
        // if ($remainder) {
        //     $padlen = 4 - $remainder;
        //     $input .= str_repeat('=', $padlen);
        // }
        return base64_decode($input);
        //return base64_decode(strtr($input, '-_', '+/'));
    }

    /**
     * Encode a string with URL-safe Base64.
     *
     * @param string $input The string you want encoded
     *
     * @return string The base64 encode of what you passed in
     */
    public static function urlsafeB64Encode($input)
    {
        return base64_encode($input);
        // return str_replace('=', '', strtr(base64_encode($input), '+/', '-_'));
    }

    /**
    *返回对应的私钥(内部类调用)
    */
    private static function getPrivateKey(){
        $privKey = self::$PRIVATE_KEY;
        return openssl_pkey_get_private($privKey);      
    }

    /**
    *返回对应的公钥(内部类调用)
    */
    private static function getPublicKey(){
        $pubKey = self::$B_PUBLIC_KEY;
        return openssl_pkey_get_public($pubKey);      
    }
 
    /**
     * 私钥加密
     */
    public static function privEncrypt($data)
    {
        if(!is_string($data)){
            return null;
        }
        return openssl_private_encrypt($data,$encrypted,self::getPrivateKey())? self::urlsafeB64Encode($encrypted) : null;
    }
    
    /**
     * 私钥解密
     */
    public static function privDecrypt($encrypted)
    {
        if(!is_string($encrypted)){
            return null;
        }
        return (openssl_private_decrypt(self::urlsafeB64Decode($encrypted), $decrypted, self::getPrivateKey()))? $decrypted : null;
    }

    /**
     * 公钥加密
     */
    public static function pubEncrypt($data)
    {
        if(!is_string($data)){
            return null;
        }
        return openssl_public_encrypt($data,$encrypted,self::getPublicKey())? self::urlsafeB64Encode($encrypted) : null;
    }
    
    /**
     * 公钥解密
     */
    public static function pubDecrypt($encrypted)
    {
        if(!is_string($encrypted)){
            return null;
        }
        return (openssl_public_decrypt(self::urlsafeB64Decode($encrypted), $decrypted, self::getPublicKey()))? $decrypted : null;
    }
}