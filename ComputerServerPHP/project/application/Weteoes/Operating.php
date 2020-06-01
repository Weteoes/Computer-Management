<?php
namespace Weteoes;
class OperatingClass{
    public function getOperating($i) {
        switch($i) {
            /* 网易云音乐 */
            case "GdHpHz": return "Music_163|S";
            case "sqEvAt": return "Music_163|P";
            case "ItxqHm": return "Music_163|Like";
            case "nnJotw": return "Music_163|N";
            /* 通用音乐 */
            case "qJgjHF": return "Music_Basics|S";
            case "nrzbyj": return "Music_Basics|P";
            case "CqznGI": return "Music_Basics|N";
            /* 系统音量 */
            case "cxaaHu": return "System_Up";
            case "wxmEIe": return "System_Down";
            /* CMD操作 */
            case "tjrIqg": return "CMD_rundll32.exe user32.dll,LockWorkStation";
            case "qdixoa": return "CMD_Shutdown -s -t 1";
            case "pyBalA": return "CMD_Shutdown -s -t 1800";
            case "EexBxB": return "CMD_Shutdown -s -t 3600";
            case "Gdoenq": return "CMD_Shutdown -r -t 1";
            case "zpiwBh": return "CMD_Shutdown -a";
            /* 学校操作 */
            case "iAzsFD": return "School_YiStart_Close";
            case "cwyeIA": return "School_YiStart_Start|C:\\Windows\\System32\\notepad.exe";
            /* Control */
            case "vceeDI": return "Control_Start";
            case "FdxBCI": return "Control_Stop";
            // EHhlvq hqjBFl CGIByo
            /* default */
            default: return "";
        }
    }
    public function getOperatingCode() {
        $pattern = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLOMNOPQRSTUVWXYZ';  
        $length = 6;
        $key = "";
        for($i=0;$i<$length;$i++) {   
            $key .= $pattern[mt_rand(0,35)];    //生成php随机数   
        }   
        return $key;
    }
}