<?php
namespace app\operating\controller;

class App 
{
    // 提交控制亲求
    public function sumbit()
    {
      // 跨域请求
      addHeader();
      /* request */
      $computerName = request()->param('computerName');
      $shell = request()->param('shell');
      $w = request()->param('w');
      
      /* IS NULL ? */
      if($computerName == "" || $shell == ""){
        $json = array('code'=>1,'msg'=>'NULL');
        goto result;
      }

      /* 判断是否已经登录 */
      if(!(new \Weteoes\SessionClass())->Session_PD($w)) { 
        $json = array('code'=>-1,'msg'=>'No Login');
        goto result;
      }

      /* get shell */
      include_once(Define_Weteoes_PATH."Operating.php");
      $OperatingClass_ = new \Weteoes\OperatingClass();
      $shellCode = $OperatingClass_->getOperating($shell);
      if($shellCode == "") { 
        $json = array('code'=>-1,'msg'=>'ShellCode is Error');
        goto result;
      }

      /* 组合字符串 */
      include_once(Define_Weteoes_PATH."Socket.php");
      $Socket_Str = "Weteoes_Client_".$w."|".$computerName."|".$shellCode;
      /* Send */
      (new \Weteoes\SocketClass())->Socket_SendData("operating/entrance",$Socket_Str,true);
      $json = array('code'=>0,'msg'=>'ok');
      
      result:
      return json($json);
   }

  //  获取在线电脑列表
  public function getComputerList(){
    // 跨域请求
    addHeader();
    /* request */
    $w = request()->param('w');
    
    /* 判断是否已经登录 */
    if(!(new \Weteoes\SessionClass())->Session_PD($w)) { 
      $json = array('code'=>-1,'msg'=>'No Login');
      goto result;
    }

    /* 获取user */
    $LoginClass_ = new \Weteoes\LoginClass();
    $user = $LoginClass_->sumbit_GetUser();
    if($user == ""){
      $json = array('code'=>-2,'msg'=>'NULL');
      goto result;
    }

    /* 获取在线 */
    include_once(Define_Weteoes_PATH."Socket.php");
    $json = (new \Weteoes\SocketClass())->Socket_SendData("get/computerlist",$user);
    $json = json_decode($json, true);
    if($json != "") { $json = array_merge(array('code'=>0), $json); }

    /* 如果获取失败 */
    if($json == ""){
      $json = array('code'=>-3,'msg'=>'Server error');
      goto result;
    }
  
    result:
    return json($json); //因为原本就是json格式，不需要转
  }
}
