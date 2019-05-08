<template>
  <div class="main_computer">
    <!-- 设置宽高 -->
    <div class="w_data" :style="'width:'+this.ready.w+'px;'+'height:'+this.ready.h+'px;'">
      <div class="w_body">
        <div class="main_nav">
          <div class="one"></div>
          <div class="two main_nav_two">
            <div class="left main_nav_two main_nav_inline"></div>
            <div v-on:click="leftMenu_show" class="menu main_nav_menu main_nav_two main_nav_inline">
              <img class="main_nav_menu" src="/Weteoes/Client_apk/Main/computer/image/more.png">
            </div>
            <div class="title main_nav_two main_nav_inline">电脑管理</div>
          </div>
        </div>
        <div class="computer_data">
          <div class="data_png computer_data_png">
            <img
              src="/Weteoes/Client_apk/Main/computer/image/control_2.png"
              class="computer_data_png"
            >
          </div>
        </div>
      </div>
      <div class="w_background computer_background"></div>
    </div>
    <div class="leftMenu">
      <!-- 
                    设置leftMenu_background动态绑定class,如果要显示菜单就添加class
                    自动设置宽高，修复背景布全屏的情况
                    点击背景退出菜单
      -->
      <div
        class="leftMenu_background"
        v-on:click="leftMenu_close"
        :style="'width:'+leftMenu_Background.w+'px;height:'+leftMenu_Background.h+'px'"
        :class="{leftMenu_background_Visble:leftMenu_Visible}"
      ></div>
      <!-- 如果显示等于真则添加class -->
      <!-- 设置leftMenu_data动态绑定class,如果要显示菜单就添加class -->
      <div class="leftMenu_data" :class="{leftMenu_data_Visble:leftMenu_Visible}">
        <!-- 设置navMenu的高度，修复菜单下面空白的情况 -->
        <div class="navMenu" :style="'height:'+leftMenu_Background.h+'px'">
          <div class="top_">
            <div class="data">
              <div class="png only_"></div>
              <div class="more only_">
                <div class="moreData">
                  <div class="title" v-html="user.user"></div>
                  <div class="title twoTitle" v-html="user.computerName"></div>
                </div>
              </div>
            </div>
          </div>
          <div class="menu_">
            <div
              class="onlyMenu"
              v-for="(onlyMenu, number) in leftMenu" :key="number"
              :data="onlyMenu.data"
              v-on:click="leftMenu_click(number)"
            >
              <div class="onlyMenuData">
                <div
                  class="png only_"
                  :style="'background: url(\''+get_modelUrl(onlyMenu.png)+'\') 0/100% no-repeat;'"
                ></div>
                <div class="title only_" v-html="onlyMenu.title"></div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<!-- index.css -->
<style scoped>
.w_data {
  /* 设置不闪烁，默认不隐藏 */
  display: block;
}
.computer_background {
  background: #fff;
}
.computer_data {
  height: 260px;
  margin-top: 140px;
}
.computer_data_png {
  /* 图片大小 */
  width: 260px;
}
.computer_data .data_png {
  margin: 0 auto;
}
</style>

<!-- leftMenu.css -->
<style scoped>
.leftMenu {
  width: 0;
  height: 0;
  /* position: relative; */
  position: absolute;
  top: 0;
  z-index: 10;
}
.leftMenu .leftMenu_background {
  transition: background 0.5s; /* 背景渐变 */
}
.leftMenu .leftMenu_background_Visble {
  background: rgba(0, 0, 0, 0.5);
}
.leftMenu .leftMenu_data {
  position: absolute;
  top: 0;
  bottom: 0;
  left: -240px; /* 默认隐藏 */
  transition: left 0.5s; /* 滑动效果 */
}
.leftMenu .leftMenu_data_Visble {
  left: 0;
}
.leftMenu .navMenu {
  width: 240px;
  background: #fff;
}
.leftMenu .navMenu .top_ {
  width: 100%;
  height: 160px;
  background: url("/Weteoes/Client_apk/Main/computer/image/leftMenu/top.png")
    no-repeat;
  background-size: 100% 100%;
}
.leftMenu .navMenu .top_ .data {
  width: 180px;
  height: 70px;
  display: inline-block;
  margin: 60px 0 0 30px;
}
.leftMenu .navMenu .top_ .data .only_ {
  /* 统一属性 */
  height: 70px;
  display: inline-block;
  vertical-align: top;
}
.leftMenu .navMenu .top_ .data .png {
  /* only_ 统一属性 */
  width: 70px;
  background: url("/Weteoes/Client_apk/Main/computer/image/leftMenu/icon.png")
    no-repeat;
  background-size: 100% 100%;
}
.leftMenu .navMenu .top_ .data .more {
  /* only_ 统一属性 */
  width: 100px;
  padding-left: 5px;
}
.leftMenu .navMenu .top_ .data .more .moreData {
  width: 100%;
  height: 50px;
  margin-top: 10px;
}
.leftMenu .navMenu .top_ .data .more .moreData .title {
  /* 统一属性 */
  width: 100%;
  height: 25px;
  line-height: 25px;
  font-size: 16px;
  text-align: left;
  color: #fff;
  overflow: hidden;
  text-overflow: ellipsis;
}
.leftMenu .navMenu .top_ .data .more .moreData .twoTitle {
  font-size: 13px;
}
.leftMenu .navMenu .menu_ {
  width: 100%;
  height: auto;
  padding-top: 6px;
}
.leftMenu .navMenu .menu_ .onlyMenu {
  width: 100%;
  height: 44px;
}
.leftMenu .navMenu .menu_ .onlyMenu .onlyMenuData {
  width: 80%;
  height: 40px;
  margin: 2px 0 0 10px;
  overflow: hidden;
}
.leftMenu .navMenu .menu_ .onlyMenu .onlyMenuData .only_ {
  /* 统一属性 */
  height: 40px;
  line-height: 40px;
  display: inline-block;
  vertical-align: top;
}
.leftMenu .navMenu .menu_ .onlyMenu .onlyMenuData .png {
  width: 40px;
}
.leftMenu .navMenu .menu_ .onlyMenu .onlyMenuData .title {
  padding-left: 5px;
  color: #5cb5f9;
  font-size: 16px;
}
</style>


<script>
export default {
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

      // Android
      (() => {
        let a = w.android;
        a.software_onBackPressed = software_onBackPressed; //客户端返回按钮
        function software_onBackPressed() {
          return 1;
        }
      })();
      // Android End
      // 获取菜单列表
      (() => {
        w.JS_Basic.Ajax(w.url.mainComputer_getMenu, { w: this_.session }, function(result) {
          if(result.status != 200) { w.function.msg("服务器开小差啦", 2); return; }
          let resultData = result.data;
          if (resultData.code != 0) { w.function.msg("获取菜单列表失败", 2); return; }
          /* Vue */
          this_.leftMenu = resultData.menu;
        });
      })();
      // 获取菜单列表 End
      // 获取用户信息
      (() => {
        w.JS_Basic.Ajax(w.url.operating_getUserInfo, { w: this_.session }, function(result) {
          if(result.status != 200) { w.function.msg("服务器开小差啦", 2); return; }
          let resultData = result.data;
          if (resultData.code != 0) { w.function.msg("获取用户信息失败", 2); return; }
          /* Vue */
          this_.user.user = resultData.user;
        });
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
    // ready_ End
    // get_modelUrl
    //// 获取LeftMenu的图片URL(给html代码调用)
    get_modelUrl: function(data) {
      return "/Weteoes/Client_apk/Main/All/image/model/" + data + ".png";
    },
    // get_modelUrl End
    // leftMenu_click
    ///// leftMenu 点击事件
    leftMenu_click: function(number) {
      let data = this.leftMenu[number].data; //菜单code
      let computerName = this.w.JS_Basic.GetQueryString("computerName"); //电脑名称
      let url = "{url}data={data}&computerName={computerName}".format({
        url: this.w.url.mainConsole,
        data: data,
        computerName: computerName
      });
      this.$router.push(url);
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
        this.$router.push(this.w.url.login);
      }
    );
    // 判断是否登录 End
  }
};
</script>
