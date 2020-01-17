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
          user: { user: "", computerName: "" },
          /* leftMenu */
          leftMenu_Visible: false, //显示菜单
          leftMenu_Background: { w: 0, h: 0 }, //菜单背景长度
          leftMenu: [
            // { title:"网易云音乐", png:"Music_CloudMusic.png", data:"1" },
            // { title:"通用音乐", png:"Music.png", data:"2" },
            // { title:"系统操作", png:"System.png", data:"3" }
          ]
        };
      },
      methods: {
        // ready_
        ready_: function() {
          // 全局函数
          let w = this.w;
          let this_ = this;
          // 获取菜单列表
          (() => {
            w.JS_Basic.Ajax(
              w.url.mainComputer_getMenu,
              { w: this_.session },
              function(result) {
                if (result.status != 200) {
                  w.function.msg("服务器开小差啦", 2);
                  return;
                }
                let resultData = result.data;
                if (resultData.code != 0) {
                  w.function.msg("获取菜单列表失败", 2);
                  return;
                }
                /* Vue */
                this_.leftMenu = resultData.menu;
              }
            );
          })();
          // 获取菜单列表 End
          // 获取用户信息
          (() => {
            w.JS_Basic.Ajax(
              w.url.operating_getUserInfo,
              { w: this_.session },
              function(result) {
                if (result.status != 200) {
                  w.function.msg("服务器开小差啦", 2);
                  return;
                }
                let resultData = result.data;
                if (resultData.code != 0) {
                  w.function.msg("获取用户信息失败", 2);
                  return;
                }
                /* Vue */
                this_.user.user = resultData.user;
              }
            );
          })();
          // 获取用户信息 End
          // 获取电脑名称
          (() => {
            let computerName = w.JS_Basic.GetQueryString("computerName");
            if (computerName != null) {
              /* Vue */
              this.user.computerName = computerName;
            }
          })();
          // 获取电脑名称 End
        },
        // android_ready(无调用)
        android_ready: function() {
          // let a = w.android;
          // a.software_onBackPressed = software_onBackPressed; //客户端返回按钮
          // function software_onBackPressed() {
          //   return 1;
          // }
        },
        // ready_ End
        // get_modelUrl
        //// 获取LeftMenu的图片URL(给html代码调用)
        get_modelUrl: function(data) {
          return "../../../image/client/main/all/image/model/" + data + ".png";
        },
        // get_modelUrl End
        // leftMenu_click
        ///// leftMenu 点击事件
        leftMenu_click: function(number) {
          let data = this.leftMenu[number].data; //菜单code
          let computerName = this.w.JS_Basic.GetQueryString("computerName"); //电脑名称
          if (computerName == null) {
            computerName = "";
          }
          let url = "{url}data={data}&computerName={computerName}".format({
            url: this.w.url.mainConsole,
            data: data,
            computerName: computerName
          });
          this.w.app.openWeb(url);
          // location.href = url;
          // location.href = this.w.url.mainConsole + "data=" + data + "&computerName=" + computerName;

          /* 收起leftMenu */
          this.leftMenu_close();
        },
        // leftMenu_click End
        // leftMenu_show
        //// 展开leftMenu
        leftMenu_show: function() {
          (() => {
            /* 设置背景宽度和高度 */
            this.leftMenu_Background.w = this.ready.w;
            this.leftMenu_Background.h = this.ready.h;
          })();
          this.leftMenu_Visible = true; //显示菜单
        },
        // leftMenu_show End
        // leftMenu_close
        //// 收起leftMenu
        leftMenu_close: function() {
          /* 设置过渡结束事件 */
          let menu = document.getElementsByClassName("leftMenu_data")[0];
          let fun_transitionend = () => {
            /* 设置背景宽度和高度 */
            this.leftMenu_Background.w = 0;
            this.leftMenu_Background.h = 0;
            menu.removeEventListener("transitionend", fun_transitionend); //删除过渡结束事件
          };
          menu.addEventListener("transitionend", fun_transitionend); //添加过渡结束事件

          this.leftMenu_Visible = false; //设置为不可见
        }
        // leftMenu_close End
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
