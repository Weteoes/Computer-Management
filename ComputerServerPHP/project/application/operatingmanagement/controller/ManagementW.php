<?php
namespace app\operatingManagement\controller;
class ManagementW
{
	private $Management = false; // 是否有权限执行
	private $w = ""; // session
	
	public function __construct() {
		try {
			$this->w = request()->param('w');
			$SessionClass_ = new \Weteoes\SessionClass();
			$LoginClass_ = new \Weteoes\LoginClass();
			if($SessionClass_->Session_PD($this->w) && $LoginClass_ ->sumbit_GetManagement() > 0){ 
				$this->Management = true;
			}
			
		} catch(\Exception $e) {}
	}

	// 获取用户Session信息
  	public function getList()
  	{
		// 跨域请求
		addHeader();

		// 判断权限
		if(!$this->Management) {
			$json = array('code'=>-1,'msg'=>'No Login');
			goto result;
		}
		
		// 实例化
		$SessionClass_ = new \Weteoes\SessionClass();
		$LoginClass_ = new \Weteoes\LoginClass();
		include_once(operating_Management_path."w/Users.php");
		$Management_W_UserClass_ = new \Weteoes\Management_W_UserClass();
		
		// 获取用户列表
		$result = $Management_W_UserClass_->getList();
		$json = array('code'=>0, 'list'=>$result);

		// 设置回session
		$SessionClass_->Session_PD($this->w);

		result:
		return json($json);
	}

	// 删除用户Session信息
  	public function remove()
  	{
		// 跨域请求
		addHeader();

		// 判断权限
		if(!$this->Management) {
			$json = array('code'=>-1,'msg'=>'No Login');
			goto result;
		}
		
		// 实例化
		$SessionClass_ = new \Weteoes\SessionClass();
		$LoginClass_ = new \Weteoes\LoginClass();
		include_once(operating_Management_path."w/Users.php");
		$Management_W_UserClass_ = new \Weteoes\Management_W_UserClass();

		// 参数
		$removeId = request()->param('removeId');

		// 判断是否为空
		if($removeId == "") {
			$json = array('code'=>-1,'msg'=>'NULL');
			goto result;
		}

		// 获取用户列表
		$result = $Management_W_UserClass_->remove($removeId);
		$json = array('code' => 0, 'msg'=> "ok");

		// 设置回session
		$SessionClass_->Session_PD($this->w);

		result:
		return json($json);
	}

	// 删除无用(过期)的session
	public function removeUseless() {
        // 跨域请求
		addHeader();

		// 判断权限
		if(!$this->Management) {
			$json = array('code'=>-1,'msg'=>'No Login');
			goto result;
		}
		
		// 实例化
		$SessionClass_ = new \Weteoes\SessionClass();
		$LoginClass_ = new \Weteoes\LoginClass();
		include_once(operating_Management_path."w/Users.php");
		$Management_W_UserClass_ = new \Weteoes\Management_W_UserClass();

		// 操作
		$Management_W_UserClass_->removeUseless();
		$json = array('code' => 0, 'msg'=> "ok");

		// 设置回session
		$SessionClass_->Session_PD($this->w);

		result:
		return json($json);
	}

	// 删除所有session
	public function removeAll() {
		// 跨域请求
		addHeader();

		// 判断权限
		if(!$this->Management) {
			$json = array('code'=>-1,'msg'=>'No Login');
			goto result;
		}

		// 实例化
		$SessionClass_ = new \Weteoes\SessionClass();
		$LoginClass_ = new \Weteoes\LoginClass();
		include_once(operating_Management_path."w/Users.php");
		$Management_W_UserClass_ = new \Weteoes\Management_W_UserClass();

		// 操作
		$Management_W_UserClass_->removeAll();
		$json = array('code' => 0, 'msg'=> "ok");

		// 设置回session
		$SessionClass_->Session_PD($this->w);

		result:
		return json($json);
	}
}
