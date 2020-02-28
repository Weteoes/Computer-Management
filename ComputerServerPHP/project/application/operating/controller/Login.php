<?php
namespace app\operating\controller;
class Login 
{
	// 登录请求
	public function sign_in()
	{
		// 跨域请求
		addHeader();
		/* 判断是否已经登录 */
		$SessionClass_ = new \Weteoes\SessionClass();
		$LoginClass_ = new \Weteoes\LoginClass();

		if($SessionClass_->Session_PD()){ 
			$json = array('code'=>0,'msg'=>'Has Login','w'=>session_id(), 'user' => $LoginClass_->sumbit_GetUser());
			goto result;
		}
		$user = request()->param('user');
		$pass = request()->param('pass');
		$w_Type = request()->param('w_Type'); //Type 登录设备
    	if($user == "" || $pass == ""){
			$json = array('code' => 1,'msg' => 'NULL');
			goto result;
		}
		try{
			$json = array('code'=>2,'msg'=>'User or Password is Error');
			$loginResult = $LoginClass_->sumbit($user, $pass); // 用户信息
			if($loginResult != NULL){ //登录成功
				// Session
				$LoginClass_->sumbit_session($loginResult["user"], $loginResult["pass"], $w_Type, $loginResult["management"]); 

				/* result */
				$json = array('code'=>0, 'msg'=>'Ok', 'w' => session_id(), 'user' => $LoginClass_->sumbit_GetUser());
				goto result;
			}
		}
		catch(\Exception $Error) {
			$json = array('code'=>3,'msg'=>'System Error');
			goto result;
		}
		result:
		return json($json);
	}
}
