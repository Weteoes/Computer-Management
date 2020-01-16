(function () {
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
          // input
          input: {
            user: "",
            pass: ""
          }
        };
      },
      methods: {
        ready_: function() {
          // loadingScreen
          //// 不放在判断登录之前，因为有自动登录，所以等待操作完成再显示
          (() => {
            if (this.debug) {
              this.ready.w = 360;
              this.ready.h = 640;
            }
            let body_ = document.getElementsByClassName("w_data")[0];
            // body_.width = w;
            // body_.height = h;
            body_.style.position = "relative";
            body_.style.display = "block";
            let msg = "Photo width:{w} height:{h}".format({
              w: this.ready.w,
              h: this.ready.h
            });
            this.w.function.msg(msg, 1);
          })();
          // loadingScreen End
        },
        // sumbitKeydown
        sumbitKeydown: function(a) {
          if (a.keyCode == 13) {
            this.sumbitClick();
          }
        },
        // sumbitKeydown End
        // sumbitClick
        sumbitClick: function() {
          let user = this.input.user,
            pass = this.input.pass;
          let this_ = this;
          // 全局函数
          let w = this.w;
          if (!isnull(user, pass)) {
            return;
          }
          w.JS_Basic.Ajax(
            w.url.operating_sign_in,
            { user: user, pass: pass },
            function(result) {
              let resultData = result.data;
              if (resultData.code == 0) {
                // 手机存储
                w.app.login_setW(resultData.w);
                // Session
                console.log(resultData,resultData.w);
                window.localStorage.setItem("w", resultData.w);
                location.href = this_.w.url.main;
              } else {
                w.function.msg("用户名或密码错误", 2);
              }
            },
            function(error) {
              w.function.msg("意外的错误" + error, 2);
            }
          );
          // isnull
          function isnull(user, pass) {
            if (user == "" || pass == "") {
              w.function.msg("用户名或密码不能为空", 2);
              return false;
            } else if (user == undefined || pass == undefined) {
              w.function.msg("用户名密码获取失败", 2);
              return false;
            } else if (pass.length < 6) {
              w.function.msg("请输入正确的密码", 2);
              return false;
            }
            return true;
          }
          // isnull End
        }
        // sumbitClick End
      },
      mounted() {
        // 初始化
        this.w.function.ready();
        // 判断是否登录
        this.w.function.isLogin(
          () => {
            //登录成功
            location.href = this.w.url.main;
          },
          () => {
            //登录失败
            this.ready_();
          }
        );
        // 判断是否登录 End
      }
    });
  }
})();
