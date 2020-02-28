<template>
  <router-view/>
</template>

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

<script>
export default {
  methods: {
    // ready_
    ready_: function() {
      let w = window;
      if (typeof w.Weteoes == "undefined") {
        w.Weteoes = {};
      }
      let obj = w.Weteoes;

      // URL
      if (typeof obj.url == "undefined") {
        let serverAPI;
        if (this.debug) {
          serverAPI = "http://127.0.0.1";
        } else {
          serverAPI = "https://computer.weteoes.cn";
        }
        obj.url = {
          login: "/console/login", //登录界面
          management: "/console/management", //控制中心
          operating_sign_in: serverAPI + "/operating/Login/sign_in?w_Type=2", //登录API
          operating_getUserInfo: serverAPI + "/operating/User/get?", //获取用户信息（也被用于判断是否登录）
        };
        // 管理台API
        obj.url.management_ = {
          users: obj.url.management + "/w/users", //子页面
          management: obj.url.management + "/w/management", //子页面
          // W值
          w: {
            operating_getList: serverAPI + "/operatingManagement/ManagementW/getList", //获取W值列表
            operating_remove: serverAPI + "/operatingManagement/ManagementW/remove", //删除W值
            operating_removeUseless: serverAPI + "/operatingManagement/ManagementW/removeUseless", //删除无用（过期）的W值
            operating_removeAll: serverAPI + "/operatingManagement/ManagementW/removeAll", //删除所有W值
          }
          // W值 End
        }
        // 管理台API End
      }
      // URL End

      // function(通用函数)
      if (typeof obj.function == "undefined") {
        obj.function = {};
      } 
      let obj_function = obj.function;
      // 消息
      //// Type 1 单独console
      //// Type 2 console + 提示客户端
      //// e_type element type(Type == 2)
      obj_function.msg = (data, type, e_type) => {
        // console
        let console_ = () => {
          window.console.log(data);
        };
        // console End
        // 客户端信息
        let dlg_Toast_ = () => {
          this.$message({
            showClose: true,
            message: data,
            type: e_type
          });
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
              obj_function.msg("服务器开小差了", 1);
              error();
              return;
            }
            if (result.data.code == 0 && result.data.management > 0) {
              window.localStorage.setItem("w", session);
              obj_function.msg("自动登录成功 w:" + session, 1);
              success();
              return;
            }
            obj_function.msg("自动登录失败 w:" + session, 1);
            error();
          },
          function() {
            error();
            return;
          }
        );
      };
      // 判断是否登录 End
    }
    // ready_ End
  },
  created() {
    this.ready_();
  }
};
</script>
