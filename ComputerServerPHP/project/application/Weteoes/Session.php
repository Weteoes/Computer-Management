<?php
namespace Weteoes;
class SessionClass{
    private $session_Prefix = "sess_";

    public function session_Time($SessionName){ // 是否过期
        include_once(Define_Weteoes_PATH."Login.php");
        $LoginClass_ = new \Weteoes\LoginClass();
        /* 判断是是手机，手机不会过期 */
        if(!$LoginClass_->isExpired($LoginClass_->sumbit_GetType())){ // 如果会过期
            /* 判断时间是否过期 */
            $w_StartTime = $LoginClass_->sumbit_GetLoginTime(); // 获取登录时间
            if (time() - $w_StartTime > 3600) {
                /* 销毁session */
                $this->sessionRemove();
                return false;
            }
        }
        return true;
    }
    public function Session_PD($SessionName = NULL){ //判断Session是否有效
        /* $SessionName Not NULL */
        if(is_null($SessionName)){
            $SessionName = cookie('w');  //如果$SessionName为空则取cookie
        }
        if(is_null($SessionName)) { return false; } //执行前判断是否为NUL
        $SessFile = $this->Get_SessionFileName($SessionName);
        if(!file_exists($SessFile)) { return false; } //ToKen文件如果不存在
        $this->Session_Init($SessionName); //初始化session
        if(!$this->session_Time($SessionName)){ return false; } //是否过期
        if(!$this->session_UP($SessionName)){ return false; } //用户名密码判断
        return true;
    }
    // 初始化Session
    public function Session_Init($id = NULL) 
    {
        $config = array(
            'name' => "w",
            'expire' => 0,
            'path' => Define_SESSION_PATH,
            'use_cookies' => false
        );
        if($id != NULL){
            $config['id'] = $id;
        }
        session_abort();
        session($config);
        session_start();
        
        // Cookie
        cookie("w", session_id());
    }

    // 删除Session
    public function sessionRemove($id = NULL) {
        // 如果不为空就先设置Session
        if($id != NULL) {
            $this->Session_Init($id);
        }

        // 销毁session
        session_destroy();

        // REMOVE FILE(一般用不到，会自动删除)
        $SessFile = $this->Get_SessionFileName($id);
        if(file_exists($SessFile)) { unlink($SessFile); }

        // Cookie
        cookie('w', null);
    }

    // 获取Session列表
    public function sessionList() {
        $path = Define_SESSION_PATH;
        $PathFilesArray = array(); //result
        $PathFiles = scandir($path);
        foreach($PathFiles as $PathFile) {
            if($PathFile=='.'||$PathFile=='..') { continue; }
            // 文件夹
            if(is_dir($path.'/'.$PathFile)) { continue; }
            // 文件
            else {
                // 取第一位，判断是不是无用文件，例如.gitignore
                if(substr($PathFile, 0, 1) == ".") { continue; }
                
                // 判断文件名是否存在session前缀
                $TEMP = substr($PathFile, 0, strlen($this->session_Prefix));
                if($TEMP != $this->session_Prefix) { continue; };

                // 去掉session前缀
                $result = substr($PathFile, strlen($this->session_Prefix));
                
                // 添加数组
                array_push($PathFilesArray,$result);
            } 
        }
        return $PathFilesArray;
    }

    //获取session文件位置
    private function Get_SessionFileName($SessionName){
        $SessFile = Define_SESSION_PATH.'/sess_'.$SessionName;
        return $SessFile;
    }


    private function session_UP(){ //用户名密码判断
        include_once(Define_Weteoes_PATH."Login.php");
        $LoginClass_ = new \Weteoes\LoginClass();
        $user = $LoginClass_->sumbit_GetUser();
        $pass = $LoginClass_->sumbit_GetPass();
        if($user == "" || $pass == "") return false;
        if($LoginClass_->sumbit($user,$pass) != -1) return true;
        return false;
    }
}