<?php
namespace Weteoes;
class Management_W_UserClass {
    // 获取session列表
    public function getList() {
		// 实例化
        $SessionClass_ = new \Weteoes\SessionClass();
        $LoginClass_ = new \Weteoes\LoginClass();
        // 获取Session列表
        $sessionList = $SessionClass_ -> sessionList();
        // result
        $result = array();
        // 获取自己的信息
        $management = $LoginClass_ -> sumbit_GetManagement();
        $sessionID = session_id();
        // 遍历
        foreach($sessionList as $session) {
            // 自己不会出现在列表中
            if($session == $sessionID) { continue; }
            $SessionClass_ -> Session_Init($session);
            // 权限比自己大就不显示在列表中（不能被管理）
            $sessionData_Management = $LoginClass_ -> sumbit_GetManagement();
            if($sessionData_Management > $management) { continue; }
            // 数组
            $sessionData = array(
                'ID' => count($result) + 1,
                'User' => $LoginClass_ -> sumbit_GetUser(),
                'LoginTime' => $LoginClass_ -> sumbit_GetLoginTime(),
                'Type' => $LoginClass_ -> sumbit_GetType(),
                'w' => $session,
            );
            array_push($result, $sessionData);
        }
        // result
        return $result;
    }

    // 删除session
    public function remove($sessionId) {
		// 实例化
        $SessionClass_ = new \Weteoes\SessionClass();
        $LoginClass_ = new \Weteoes\LoginClass();
        // 获取自己的权限
        $management = $LoginClass_ -> sumbit_GetManagement();
        $SessionClass_ -> Session_Init($sessionId);
        // 权限比自己大就不显示在列表中（不能被管理）
        $sessionData_Management = $LoginClass_ -> sumbit_GetManagement();
        if($sessionData_Management > $management) { return; }
        // 删除Session
        $SessionClass_ -> sessionRemove($sessionId);
    }

    // 删除无用(过期)的session
    public function removeUseless() {
        // 实例化
        $SessionClass_ = new \Weteoes\SessionClass();
        $LoginClass_ = new \Weteoes\LoginClass();
        // 获取Session列表
        $sessionList = $SessionClass_ -> sessionList();
        // 遍历
        foreach($sessionList as $session) {
            // 设置一遍，设置时会判断是否过期
            $SessionClass_ -> Session_PD($session);
            // 如果登录时间为空，删除
            if($LoginClass_ -> sumbit_GetLoginTime() == "") {
                $SessionClass_ -> sessionRemove($session);
            }
        }
    }
    
    // 删除无用(过期)的session
    public function removeAll() {
        // 实例化
        $SessionClass_ = new \Weteoes\SessionClass();
        $LoginClass_ = new \Weteoes\LoginClass();
        // 获取Session列表
        $sessionList = $SessionClass_ -> sessionList();
        // 遍历
        foreach($sessionList as $session) {
            // 删除
            $SessionClass_ -> sessionRemove($session);
        }
    }
}