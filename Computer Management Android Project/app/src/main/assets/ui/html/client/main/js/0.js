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
          // session
          session: "",
          // data
          allComputer: 0
        };
      },
      methods: {
        // ready_
        ready_: function() {
          // android
          (() => {
            // 设置下拉刷新
            this.w.app.dlg_setPullToRefreshLayout(false, true);
            // 设置下拉刷新的事件
            var a = this.w.android;
            /* android调用重新获取 */
            a.finishRefresh = () => {
              this.w.function.msg("重新获取设备列表", 1);
              // 调用刷新
              this.getComputer();
            };
          })();
          // android End
          // 获取电脑列表
          this.getComputer();
        },
        // ready_ End
        // getComputer
        getComputer: function() {
          let w = this.w;
          let this_ = this;
          let ff_init = () => {
            this.allComputer = [];
          };
          w.JS_Basic.Ajax(
            w.url.operating_getComputerList,
            { w: this_.session },
            function(result) {
              if (result.status != 200) {
                w.function.msg("服务器开小差啦", 2);
                ff_init();
                return;
              }
              let resultData = result.data;
              if (resultData.code == -1) {
                w.function.msg(
                  "获取设备信息失败 msg:{msg}".format({ msg: resultData.msg }),
                  2
                );
                ff_init();
                return;
              }
              // if(result.user.length === 0){ w.function.msg("当前没有电脑在线", 2); }
              var allComputer = []; // 临时存放数据
              for (let computer of resultData.computer) {
                allComputer.push({ name: computer.name });
              }
              /* Vue */
              this_.allComputer = allComputer;
            }
          );
        },
        // getComputer End
        // 电脑点击事件
        click_computer: function(computerName) {
          let url = "{url}computerName={computerName}".format({
            url: this.w.url.mainComputer,
            computerName: computerName
          });
          location.href = url;
          //location.href = this.w.url.mainComputer + "computerName=" + computerName;
        }
        // 电脑点击事件 End
      },
      mounted() {
        // 初始化
        this.w.function.ready();
        // loadingScreen
        (() => {
          if (this.debug) {
            this.ready.w = 360;
            this.ready.h = 640;
          }
          let body_ = document.getElementsByClassName("w_data")[0];
          // body_.width = w;
          // body_.height = h;
          //body_.style.position = "relative";
          body_.style.display = "block";
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
            // 登录成功
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
