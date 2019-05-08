<?php
namespace Weteoes;
class UpdateListClass{
    private $AllServerPath; //在服务器中的文件具体路径
    private $ServerPath; //记录检查目录在网页中的相对路径

    /* $NowPath 记录当前遍历的文件夹相对路径 */
    public function GetUpdateList($NowPath, $type = 1){
        /* 放入全局变量 */
        switch($type){ //
            case 1: $this->ServerPath = "Update/Computer"; break;
            case 2: $this->ServerPath = "Update/ClientApk"; break;
        }
        $this->AllServerPath = ROOT_PATH."public/".$this->ServerPath;
        $PathFilesArray = array(); //result

        /* 遍历文件夹 */
        $PathFiles = scandir($this->AllServerPath.$NowPath);
        foreach($PathFiles as $PathFile)
        {
            if($PathFile=='.'||$PathFile=='..') { continue; }
            /* 如果是文件夹则递归 */
            if(is_dir($this->AllServerPath.$NowPath."/".$PathFile)) { 
                $TempPathFilesArray = self::GetUpdateList($NowPath."/".$PathFile,$type);
                foreach($TempPathFilesArray as $TempOnlyPathFile){
                    array_push($PathFilesArray,$TempOnlyPathFile);
                }
            } else { /* 是文件则添加 */
                switch($type){ //
                    case 1:  $OnlyPathFile = self::GetComputerList($PathFile,$NowPath); break;
                    case 2:  $OnlyPathFile = self::GetComputerAPKList($PathFile,$NowPath); break;
                }
                array_push($PathFilesArray,$OnlyPathFile);
            } 
        }   
        return $PathFilesArray;
    }
    /* 
        获取Computer Update List
        $PathFile 为文件
        $NowPath 为递归路径
     */
    private function GetComputerList($PathFile,$NowPath){
        /* File Name */
        $FileName = substr($NowPath."\\".$PathFile,1);
        $FileName = str_replace("/","\\",$FileName);

        /* Url */
        $FileDownload = $_SERVER['REQUEST_SCHEME'].":\\\\".$_SERVER['SERVER_NAME']."\\".$this->ServerPath.$NowPath."\\".$PathFile;
        $FileDownload = str_replace("\\","/",$FileDownload);

        /* Array */
        $OnlyPathFile["FileName"] = $FileName;
        $OnlyPathFile["FileMD5"] = md5_file($this->AllServerPath.$NowPath."//".$PathFile);
        $OnlyPathFile["FileDownload"] = $FileDownload."?Weteoes=".rand();
        return $OnlyPathFile;
    }
    private function GetComputerAPKList($PathFile,$NowPath){
        /* File Name */
        $FileName = substr($NowPath."\\".$PathFile,1);
        $FileName = str_replace("/","\\",$FileName);

        /* Url */
        $FileDownload = $_SERVER['REQUEST_SCHEME'].":\\\\".$_SERVER['SERVER_NAME']."\\".$this->ServerPath.$NowPath."\\".$PathFile;
        $FileDownload = str_replace("\\","/",$FileDownload);

        /* Array */
        $OnlyPathFile["FileName"] = $FileName;
        $OnlyPathFile["FileVersion"] = substr($FileName,0,strpos($FileName,".apk"));
        $OnlyPathFile["FileDownload"] = $FileDownload."?Weteoes=".rand();
        return $OnlyPathFile;
    }
}