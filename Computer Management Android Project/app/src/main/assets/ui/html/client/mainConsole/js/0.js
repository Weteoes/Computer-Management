(function() {
  ready();
  function ready() {
    new Vue({
      el: "#app",
      data() {
        return {
          // 全局函数
          w: window.Weteoes,
          // 窗口大小
          ready: { w: window.screen.width, h: window.screen.height },
          // session
          session: "",
          //Data
          model: "", //用于model图片
          // 菜单
          features: {
            row: [
              {
                column: [{ title: "Loading", data: "" }]
              }
            ]
          }
          // 菜单 End
        };
      },
      methods: {
        // ready_
        ready_: function() {
          let w = this.w; // 全局函数
          let this_ = this; // 全局this
          // 获取控制列表
          (() => {
            let data = w.JS_Basic.GetQueryString("data");
            w.JS_Basic.Ajax(
              w.url.mainConsole_get,
              { w: this_.session, features: data },
              function(result) {
                if (result == null) {
                  w.function.msg("获取控制列表失败", 2);
                  return;
                }
                if (result.status != 200) {
                  w.function.msg("获取控制列表失败,code -1", 2);
                  return;
                }
                let resultData = result.data;
                if (resultData.code != 0) {
                  w.function.msg("获取控制列表失败,功能不存在", 2);
                  return;
                }
                /* Vue */
                this_.model = resultData.model;
                this_.features.row = resultData.row;
              }
            );
          })();
          // 获取控制列表 End
        },
        // ready_ End
        // android_ready(无调用)
        android_ready: function () {
          // let a = w.android;
          // a.software_onBackPressed = software_onBackPressed; //客户端返回按钮
          // function software_onBackPressed() {
          //   return 1;
          // }
        },
        // get_modelUrl
        get_modelUrl: function(data) {
          return "../../../image/client/main/all/image/model/{data}_1.png".format(
            {
              data: data
            }
          );
        },
        // get_modelUrl End
        // 按钮点击事件
        featuresClick: function(rowNumber, columnNumber) {
          // 存储全局函数
          let w = this.w;
          // 存储全局this
          let this_ = this;
          // data
          let now = this.features.row[rowNumber].column[columnNumber];
          let data = now.data;
          let computerName = w.JS_Basic.GetQueryString("computerName");
          if (computerName == "") {
            w.function.msg("发送指令失败,computerName is null", 2);
            return;
          }
          w.function.msg(
            "Console Send Data Success \ncomputerName:{computerName}\nshell:{shell}".format(
              {
                computerName: computerName,
                shell: data
              }
            ),
            1
          );
          w.JS_Basic.Ajax(
            w.url.operating_app_sumbit,
            { w: this_.session, computerName: computerName, shell: data },
            function(result) {
              if (result.status != 200) {
                w.function.msg("发送指令失败", 2);
                return;
              }
              let resultData = result.data;
              if (resultData.code != 0) {
                w.function.msg(
                  "发送指令失败".format({ msg: resultData.msg }),
                  2
                );
                return;
              }
              w.function.msg("发送指令成功", 1);
            }
          );
        },
        // 按钮点击事件 End
        // 返回按钮点击事件
        callbackClick: function() {
          window.history.go(-1);
        }
        // 返回按钮点击事件 End
      },
      mounted() {
        // 初始化
        this.w.function.ready();
        //loadingScreen
        (() => {
          if (this.debug) {
            this.ready.w = 360;
            this.ready.h = 640;
          }
          let body_ = document.getElementsByClassName("w_data")[0];
          // body_.width = w;
          // body_.height = h;
          body_.style.position = "relative";
          let msg = "Photo width:{w} height:{h}".format({
            w: this.ready.w,
            h: this.ready.h
          });
          this.w.function.msg(msg, 1);
        })();
        // loadingScreen End
        // 判断是否登录
        this.w.function.isLogin(
          () => {
            // 设置全局session
            this.session = window.localStorage.getItem("w");
            this.ready_();
          },
          () => {
            // 登录失败
            location.href = this.w.url.login;
          }
        );
        // 判断是否登录 End
      }
    });
  }
})();
