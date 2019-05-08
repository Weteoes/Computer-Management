<?php
namespace app\operatingManagement\controller;
class ManagementW
{
	// 获取用户Session信息
  	public function getList()
  	{
		// 跨域请求
		addHeader();
		// 实例化
		$SessionClass_ = new \Weteoes\SessionClass();
		$LoginClass_ = new \Weteoes\LoginClass();
		include_once(operating_Management_path."w/Users.php");
		$Management_W_UserClass_ = new \Weteoes\Management_W_UserClass();
		

		//获取w
		$w = request()->param('w');
		/* 判断是否已经登录 */
		if(!$SessionClass_->Session_PD($w) && !($LoginClass_ ->sumbit_GetManagement() > 0)){ 
			$json = array('code'=>-1,'msg'=>'No Login');
			goto result;
		}
		// 获取用户列表
		$result = $Management_W_UserClass_->getList();
		$json = array('code'=>0, 'list'=>$result);
		goto result;

		result:
		// 设置回session
		$SessionClass_->Session_PD($w);
		return json($json);
	}

	// 删除用户Session信息
  	public function remove()
  	{
		// 跨域请求
		addHeader();
		// 实例化
		$SessionClass_ = new \Weteoes\SessionClass();
		$LoginClass_ = new \Weteoes\LoginClass();
		include_once(operating_Management_path."w/Users.php");
		$Management_W_UserClass_ = new \Weteoes\Management_W_UserClass();
		// 获取w
		$w = request()->param('w');
		$removeId = request()->param('removeId');
		// 判断是否为空
		if($removeId == "") {
			$json = array('code'=>-1,'msg'=>'NULL');
			goto result;
		}
		// 判断是否已经登录
		if(!$SessionClass_->Session_PD($w) && !($LoginClass_ ->sumbit_GetManagement() > 0)){ 
			$json = array('code'=>-1,'msg'=>'No Login');
			goto result;
		}
		// 获取用户列表
		$result = $Management_W_UserClass_->remove($removeId);
		$json = array('code' => 0, 'msg'=> "ok");
		goto result;

		result:
		// 设置回session
		$SessionClass_->Session_PD($w);
		return json($json);
	}

	// 删除无用(过期)的session
	public function removeUseless() {
        // 跨域请求
		addHeader();
		// 实例化
		$SessionClass_ = new \Weteoes\SessionClass();
		$LoginClass_ = new \Weteoes\LoginClass();
		include_once(operating_Management_path."w/Users.php");
		$Management_W_UserClass_ = new \Weteoes\Management_W_UserClass();
		// 获取w
		$w = request()->param('w');
		// 判断是否已经登录
		if(!$SessionClass_->Session_PD($w) && !($LoginClass_ ->sumbit_GetManagement() > 0)){ 
			$json = array('code'=>-1,'msg'=>'No Login');
			goto result;
		}
		$Management_W_UserClass_->removeUseless();
		$json = array('code' => 0, 'msg'=> "ok");
		goto result;

		result:
		// 设置回session
		$SessionClass_->Session_PD($w);
		return json($json);
	}

	// 删除所有session
	public function removeAll() {
		// 跨域请求
		addHeader();
		// 实例化
		$SessionClass_ = new \Weteoes\SessionClass();
		$LoginClass_ = new \Weteoes\LoginClass();
		include_once(operating_Management_path."w/Users.php");
		$Management_W_UserClass_ = new \Weteoes\Management_W_UserClass();
		// 获取w
		$w = request()->param('w');
		// 判断是否已经登录
		if(!$SessionClass_->Session_PD($w) && !($LoginClass_ ->sumbit_GetManagement() > 0)){ 
			$json = array('code'=>-1,'msg'=>'No Login');
			goto result;
		}
		$Management_W_UserClass_->removeAll();
		$json = array('code' => 0, 'msg'=> "ok");
		goto result;

		result:
		// 设置回session
		$SessionClass_->Session_PD($w);
		return json($json);
	}
}
