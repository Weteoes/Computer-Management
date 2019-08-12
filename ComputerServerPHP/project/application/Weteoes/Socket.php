<?php
namespace Weteoes;
class SocketClass{
    private $debug = false;
    
    public function Socket_SendData($url, $data, $encode = false){
        include_once("RSA.php");
        $RSA = new \Weteoes\RsaClass();
        if($encode) $data = $RSA::pubEncrypt($data);
        if($this->debug){
            $host = '127.0.0.1';
            $host_port = 1;
        }else{
            $host = 'computer.weteoes.cn';
            $host_port = 6666;
        }
        if($data != null){
            $allurl = 'http://' . $host . ':' . $host_port . '/'.$url.'?'.$data; //因为是软件监听，不需要https
            $ch  = curl_init();
            curl_setopt($ch, CURLOPT_URL, $allurl);
            curl_setopt($ch, CURLOPT_POST, true);
            //curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
            curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 1);
            curl_setopt($ch, CURLOPT_TIMEOUT, 1);
            $result = curl_exec($ch);
            curl_close($ch);
            return $result;
        }
        return "";
    }
}