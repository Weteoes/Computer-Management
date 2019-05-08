<?php
namespace app\operatingManagement\controller;
class User 
{
	// 获取用户信息
	public function get()
	{
		// 跨域请求
		addHeader();
		// 获取w
		$w = request()->param('w');
		// 实例化
		$SessionClass_ = new \Weteoes\SessionClass();
		$LoginClass_ = new \Weteoes\LoginClass();

		/* 判断是否已经登录 */
		if(!$SessionClass_->Session_PD($w) && !($LoginClass_ ->sumbit_GetManagement() > 0)){ 
			$json = array('code'=>-1,'msg'=>'No Login');
			goto result;
		}

		// 获取用户
		$LoginClass_ = new \Weteoes\LoginClass();
		$user = $LoginClass_->sumbit_GetUser();
		$json = array('code'=>0, 'user'=>$user);
		goto result;

		result:
		return json($json);
	}
}
