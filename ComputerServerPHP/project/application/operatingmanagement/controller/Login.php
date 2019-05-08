<?php
namespace app\operatingManagement\controller;
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

		if($SessionClass_->Session_PD() && !($LoginClass_ ->sumbit_GetManagement() > 0)){ 
			$json = array('code'=>0,'msg'=>'Has Login');
			goto result;
		}
		$user = request()->param('user');
		$pass = request()->param('pass');
		if($user == "" || $pass == ""){
			$json = array('code'=>1,'msg'=>'NULL');
			goto result;
		}
		try{
			$json = array('code'=>2,'msg'=>'User or Password is Error');
			/* 登录 */
			$Management = $LoginClass_->sumbit($user, $pass); // 权限
			if($Management > 0){ // 登录成功
				// Session
				$LoginClass_->sumbit_session($user, $pass, "2", $Management); 

				// result
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