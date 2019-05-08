<?php
namespace app\computer\controller;

class Update 
{
    public function index()
    {
      include_once(Define_Weteoes_PATH."UpdateList.php");
      $a = (new \Weteoes\UpdateListClass())->GetUpdateList("",1);
		  return json($a);
    }
}
