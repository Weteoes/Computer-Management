<template>
  <router-view/>
</template>

<!-- index.css -->
<style>
* {
  margin: 0;
  padding: 0;
  -webkit-touch-callout: none; /* iOS Safari */
  -webkit-user-select: none; /* Chrome/Safari/Opera */
  -khtml-user-select: none; /* Konqueror */
  -moz-user-select: none; /* Firefox */
  -ms-user-select: none; /* Internet Explorer/Edge */
  user-select: none; /* Non-prefixed version, currently */
}
body {
  min-width: 360px;
  position: relative;
}
.w_data {
  width: 100%;
  height: auto;
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  display: none;
}
.w_body {
  width: 100%;
  height: auto;
  position: absolute;
  top: 0;
  bottom: 0;
  left: 0;
  right: 0;
  z-index: 1;
}
.w_background {
  background-size: 100% 100%;
  position: absolute;
  top: 0;
  right: 0;
  left: 0;
  bottom: 0;
}
</style>

<!-- SystemMenu.css -->
<style>
.systemMenu {
  width: 100%;
  height: 24px;
}
</style>


<script>
export default {
  methods: {
    ready_: function() {
      let w = window;
      if (typeof w.Weteoes == "undefined") {
        w.Weteoes = {};
      }
      if (typeof w.Weteoes.app == "undefined") {
        w.Weteoes.app = {};
      }

      /* 
        obj 全局js调用函数 obj_app
        全局js窗口方法调用函数 obj_app_ 
        android方法函数
    */
      let obj = w.Weteoes,
        obj_app = w.Weteoes.app,
        obj_app_ = w.Weteoes_App;

      /* Toast */
      obj_app.dlg_Toast = function(data) {
        if (
          typeof obj_app_ == "object" &&
          typeof obj_app_.dlg_Toast == "function"
        ) {
          obj_app_.dlg_Toast(data);
        }
      };

      /* login_setW */
      obj_app.login_setW = function(data) {
        if (
          typeof obj_app_ == "object" &&
          typeof obj_app_.login_setW == "function"
        ) {
          obj_app_.login_setW(data);
        }
      };

      /* dlg_setPullToRefreshLayout */
      obj_app.dlg_setPullToRefreshLayout = function(a, b) {
        if (
          typeof obj_app_ == "object" &&
          typeof obj_app_.dlg_setPullToRefreshLayout == "function"
        ) {
          obj_app_.dlg_setPullToRefreshLayout(a, b);
        }
      };

      /* URL */
      if (typeof obj.url == "undefined") {
        let serverAPI;
        if(this.debug) { serverAPI = "http://127.0.0.1"; }
        else { serverAPI = "https://computer.weteoes.cn"; }
        obj.url = {
          login: "/client_apk/login?", //登录界面
          main: "/client_apk/main?", //控制中心
          mainComputer: "/client_apk/Main/computer?", //电脑管理
          mainConsole: "/client_apk/Main/console?", //电脑管理控制台
          operating_sign_in: serverAPI + "/operating/Login/sign_in?w_Type=1", //登录API
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
        obj_app.dlg_setPullToRefreshLayout(false, false);
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
    }
  },
  created() {
    this.ready_();
  }
};
</script>
