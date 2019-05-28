<?php
namespace app\client_apk\controller;
class Console 
{
    /* 获取控制按钮列表 */
    public function getConsoleList() {
        // 跨域请求
        addHeader();
        //获取w
        $w = request()->param('w');
        /* 判断是否已经登录 */
        include_once(Define_Weteoes_PATH."Session.php");
        $SessionClass_ = new \Weteoes\SessionClass();
        if(!$SessionClass_->Session_PD($w)){
            $json = array('code'=>-1,'msg'=>'No Login');
            goto result;
        }
        /* 获取数据 */
        $features = request()->param('features');
        if($features == "") {
            $json = array('code'=>-1,'msg'=>'NULL');
            goto result;
        }
        /* switch */
        switch($features) {
            case "1": // 网易云音乐
                $json = $this->console_Music_CloudMusic();
                break;
            case "2": // 通用音乐
                $json = $this->console_Music();
                break;
            case "3": // 系统操作
                $json = $this->console_System();
                break;
            case "4": // 学校操作
                $json = $this->console_School();
                break;
            default: 
                $json = array('code'=>-1,'msg'=>'features is not found');
                break;
        }

        /* result */
        result:
		return json($json);
    }

    /* 获取控制菜单 */
    public function getConsoleMenu() {
        // 跨域请求
        addHeader();
        //获取w
        $w = request()->param('w');
        /* 判断是否已经登录 */
        include_once(Define_Weteoes_PATH."Session.php");
        $SessionClass_ = new \Weteoes\SessionClass();
        if(!$SessionClass_->Session_PD($w)){
            $json = array('code'=>-1,'msg'=>'No Login');
            goto result;
        }

        $json = array(
            'code'=>0,
            'menu'=>array(
                array('title'=>'网易云音乐', 'png'=>"Music_CloudMusic", 'data'=>"1" ),
                array('title'=>'通用音乐', 'png'=>"Music", 'data'=>"2" ),
                array('title'=>'系统操作', 'png'=>"System", 'data'=>"3" ),
                array('title'=>'学校操作', 'png'=>"System", 'data'=>"4" ),
            )
        );
        
        /* result */
        result:
		return json($json);
    }

    // 生成随机码
    public function addConsole() {
        include_once(Define_Weteoes_PATH."Operating.php");
        $OperatingClass_ = new \Weteoes\OperatingClass();
        return $OperatingClass_->getOperatingCode();
    }

    // Private

    /* 网易云音乐 */
    private function console_Music_CloudMusic() {
        $result = array(
            'code'=>0,
            'model'=>"Music_CloudMusic", //用于model图片
            'row'=>array(
                array(
                    'column'=>array(
                        array('title'=>'上一首','data'=>'GdHpHz'),
                        array('title'=>'暂停/播放','data'=>'sqEvAt'),
                        array('title'=>'喜欢','data'=>'ItxqHm'),
                        array('title'=>'下一首','data'=>'nnJotw'),
                    )
                ),
                array(
                    'column'=>array(
                        array('title'=>'音量+','data'=>'cxaaHu'),
                        array('title'=>'音量-','data'=>'wxmEIe'),
                    )
                ),
            )   
        );
        return $result;
    }

    /* 通用音乐 */
    private function console_Music() {
        $result = array(
            'code'=>0,
            'model'=>"Music", //用于model图片
            'row'=>array(
                array(
                    'column'=>array(
                        array('title'=>'上一首','data'=>'qJgjHF'),
                        array('title'=>'暂停/播放','data'=>'nrzbyj'),
                        array('title'=>'下一首','data'=>'CqznGI'),
                    )
                ),
                array(
                    'column'=>array(
                        array('title'=>'音量+','data'=>'cxaaHu'),
                        array('title'=>'音量-','data'=>'wxmEIe'),
                    )
                ),
            )
        );
        return $result;
    }

    /* 系统操作 */
    private function console_System() {
        $result = array(
            'code'=>0,
            'model'=>"System", //用于model图片
            'row'=>array(
                array(
                    'column'=>array(
                        array('title'=>'关机','data'=>'qdixoa'),
                        array('title'=>'重启','data'=>'Gdoenq'),
                        array('title'=>'锁屏','data'=>'tjrIqg'),
                    )
                ),
                array(
                    'column'=>array(
                        array('title'=>'关机(30分钟)','data'=>'pyBalA'),
                        array('title'=>'关机(1小时)','data'=>'EexBxB'),
                        array('title'=>'计划取消','data'=>'zpiwBh'),
                    )
                ),
            )
        );
        return $result;
    }

    /* 学校操作 */
    private function console_School() {
        $result = array(
            'code'=>0,
            'model'=>"System", //用于model图片
            'row'=>array(
                array(
                    'column'=>array(
                        array('title'=>'解除YiStart','data'=>'iAzsFD'),
                        array('title'=>'启动YiStart','data'=>'cwyeIA'),
                    ),
                ),
            )   
        );
        return $result;
    }
}
