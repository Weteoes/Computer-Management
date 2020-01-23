(function() {
  let w = window;
  if (typeof w.Weteoes == "undefined") {
    w.Weteoes = {};
  }
  
  /* obj 全局js调用函数 */
  let obj = w.Weteoes;



  /* Module */
  if (typeof obj.module == "undefined") {
    obj.module = {};
  }
  let obj_module = obj.module;
  // 配置module
  obj_module.config = function() { return api.require("config"); }



  /* app */
  if (typeof obj.app == "undefined") {
    obj.app = {};
  }
  let obj_app = obj.app;
  // Toast 
  obj_app.dlg_Toast = function(data) {
    api.toast({ msg: data });
  };


  
  /* URL */
  if (typeof obj.url == "undefined") {
    let serverAPI = "https://computer.weteoes.cn";
    obj.url = {
      login: "/html/client/login/index.html?", //登录界面
      main: "/html/client/main/index.html?", //控制中心
      mainComputer: "/html/client/mainComputer/index.html?", //电脑管理
      mainConsole: "/html/client/mainConsole/index.html?", //电脑管理控制台
      operating_sign_in: serverAPI + "/operating/Login/sign_in?w_Type=3", //登录API
      operating_getComputerList: serverAPI + "/operating/App/getComputerList?", //获取控制中心电脑列表（在线）
      operating_getUserInfo: serverAPI + "/operating/User/get?", //获取用户信息（也被用于判断是否登录）
      mainComputer_getMenu: serverAPI + "/client_apk/console/getConsoleMenu?", //获取电脑管理页的菜单
      mainConsole_get: serverAPI + "/client_apk/console/getConsoleList?", //获取电脑管理控制台的控制菜单
      operating_app_sumbit: serverAPI + "/operating/app/sumbit?" //提交控制命令
    };
  }




  /* Android */
  /* 需要先打开开关 */
  if (typeof obj.android == "undefined") {
    obj.android = {};
  } //android调用js
  let obj_android = obj.android;
  /* 下拉刷新函数 */
  // default
  let obj_android_finishRefresh = function() {};
  obj_android.finishRefresh = obj_android_finishRefresh;
  /* 上拉刷新函数 */
  // default
  let obj_android_finishLoadMore = function() {};
  obj_android.finishLoadMore = obj_android_finishLoadMore;
  /* 程序返回函数, 返回0表示无需android处理 1表示返回前一个网页 2表示正常返回 */
  // default
  let obj_android_software_onBackPressed = function() {
    return 2;
  };
  obj_android.software_onBackPressed = obj_android_software_onBackPressed;
  // function(通用函数)
  if (typeof obj.function == "undefined") {
    obj.function = {};
  }
  let obj_function = obj.function;
  // 初始化窗口
  obj_function.ready = () => {
    // Android
    // 禁止上拉下拉刷新
    //obj_app.dlg_setPullToRefreshLayout(false, false);
    obj_android.finishRefresh = obj_android_finishRefresh;
    obj_android.finishLoadMore = obj_android_finishLoadMore;
    // 捕捉返回按钮
    obj_android.software_onBackPressed = obj_android_software_onBackPressed;
  };
  // 初始化窗口 End
  // 判断是否登录
  obj_function.isLogin = (success, error) => {
    let w = obj;
    // 优先使用url参数
    let session = w.JS_Basic.GetQueryString("w");
    if (session == null) {
      session = window.localStorage.getItem("w");
      if (session == null) {
        error();
        return;
      }
    }
    console.log(session);
    w.JS_Basic.Ajax(
      w.url.operating_getUserInfo,
      { w: session },
      function(result) {
        if (result.status != 200) {
          debug("服务器开小差了");
          error();
          return;
        }
        if (result.data.code != 0) {
          debug("自动登录失败 w:" + session);
          error();
          return;
        }
        window.localStorage.setItem("w", session);
        debug("自动登录成功 w:" + session);
        success();
        return;
      },
      function() {
        error();
        return;
      }
    );
    // 输出
    function debug(data) {
      window.console.log(data);
    }
  };
  // 判断是否登录 End
  // 消息
  //// Type 1 单独console
  //// Type 2 console + 提示客户端
  obj_function.msg = (data, type) => {
    // console
    let console_ = () => {
      window.console.log(data);
    };
    // console End
    // 客户端信息
    let dlg_Toast_ = () => {
      obj.app.dlg_Toast(data);
    };
    // 客户端信息 End
    if (type == undefined) {
      type = 1;
    }
    switch (type) {
      case 1:
        console_();
        break;
      case 2:
        console_();
        dlg_Toast_(data);
        break;
    }
  };
  // 消息 End
})();
