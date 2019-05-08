<?php
namespace app\client_apk\controller;

class Update 
{
    public function index()
    {
      include_once(Define_Weteoes_PATH."UpdateList.php");
      $a = (new \Weteoes\UpdateListClass())->GetUpdateList("",2);
		  return json($a);
    }
}
