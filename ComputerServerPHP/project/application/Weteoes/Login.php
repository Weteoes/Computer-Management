<?php
namespace Weteoes;
class LoginClass {
    public function getTypeList() {
        $typeList = array(-1=>"旧版设备", 0=>"电脑", 1=>"手机", 2=>"后台", 3=>"APICloud");
        return $typeList;
    }
    public function setType($i) {
        session('type', $i);
    }
    public function getType($i) {
        $typeList = $this->getTypeList();
        $result = "未知";
        if (array_key_exists($i, $typeList)) {
            $result = $typeList[$i];
        }
        return $result;
    }
    // 是否过期
    public function isExpired($i) {
        // 0 电脑
        // 1 手机
        if($i == "0" || $i == "1"){ return true; }
        return false;
    }
    public function sumbit($user, $pass) { //登录
        /* sql */
        try{
            $condition = array(
                "user"=> $user,
                "pass" => $pass
            );
            $m = db("login");
            $m = $m->where($condition)->select();
            if(count($m) > 0){
                if($m[0]['pass'] == $pass){ //比较大小写,密码正确
                    $result = array(
                        "user" => $m[0]['user'],
                        "pass" => $m[0]['pass'],
                        "management" => $m[0]['management'] //权限
                    );
                    return $result;
                }
            }
        }
        catch(\Exception $Error) { }
		return NULL;
    }
    public function sumbit_session($user, $pass, $type, $management = NULL) { //登录后session操作
        include_once(Define_Weteoes_PATH."Session.php");
        $sessionClass = new \Weteoes\SessionClass();
        $sessionClass->Session_Init();
        session('user', $user);
        session('pass', $pass);
        session('w_LoginTime',time());
        if($type == "") $type = "-1";
        session('type', $type);
        session('management', $management);
    }
    public function sumbit_GetLoginTime() { //获取登录时间
        return $this->getSessionData('w_LoginTime');
    }
    public function sumbit_GetUser() { //获取用户
        return $this->getSessionData('user');
    }
    public function sumbit_GetPass() { //获取密码
        return $this->getSessionData('pass');
    }
    public function sumbit_GetType() { //获取设备类型
        return $this->getSessionData('type');
    }
    private function getSessionData($data) {
        try {
            $TEMP = session($data);
            if($TEMP ==  NULL) $TEMP = $_SESSION[$data];
            return $TEMP;
        }
        catch(\Exception $error) {
            return "";
        }
    }
    public function sumbit_GetManagement() { //获取权限 0为无权限
        $TEMP = session('management');
        if($TEMP == NULL) { $TEMP = 0; }
        return $TEMP;
    }
}