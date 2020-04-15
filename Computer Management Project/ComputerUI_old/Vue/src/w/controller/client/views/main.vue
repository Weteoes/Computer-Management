<template>
  <div class="main">
    <div class="main_body">
      <div class="main_body_top">
        <div class="SystemMenu">
          <!-- <div class='menu exit' id='exit'>×</div> -->
          <div class="menu mini" id="mini" @click="f_systemMenuClick(1)" v-if="v_systemMenu_Mini">×</div>
        </div>
        <div class="top_data">
          <div class="top_data_body">
            <div class="top_data_body_one"></div>
            <div class="top_data_body_two">
              <div class="top_title_one">
                <span
                  id="Language_top_title_one"
                  v-text="v_languageConfig.id.Language_top_title_one"
                >Login User:</span>
                <span id="User" v-text="v_basic_user"></span>
              </div>
              <div
                class="top_title_two success"
                id="Language_top_title_two"
                v-text="v_languageConfig.id.Language_top_title_two"
              >Service connection success</div>
            </div>
          </div>
        </div>
        <div class="AppMenu">
          <div
            class="menu" v-for="(v_menu,v_menuKey) in v_menus" :key="v_menu.id"
            v-bind:class= "{ firstMenu: v_menuKey == 0, menu_now: v_menu_nowID == v_menu.id, menu_: v_menu_nowID != v_menu.id}"
            @click="f_menuClick(v_menu.id)"
          >
            <div
              class="title"
              id="Language_Menu_Setting"
              v-text="v_menu.title"
            ></div>
            <div class="background"></div>
          </div>
        </div>
      </div>
      <div class="main_body_data">
        <!-- Seteting -->
        <data_setting v-if="v_menu_nowID == 'data_setting'" v-bind:props_languageConfig="v_languageConfig"></data_setting>
        <!-- Control -->
        <data_control v-if="v_menu_nowID == 'data_control'" v-bind:props_languageConfig="v_languageConfig"></data_control>
        <!-- About -->
        <data_about v-if="v_menu_nowID == 'data_about'" v-bind:props_languageConfig="v_languageConfig"></data_about>
      </div>
    </div>
    <div class="login_background">
      <div class="login_background_img"></div>
    </div>
  </div>
</template>

<!-- AppMenu -->
<style scoped>
.main_body_top .AppMenu {
  width: 100%;
  height: 26px;
  position: absolute;
  right: 0;
  bottom: 0;
  left: 0;
}
.AppMenu .menu {
  width: 140px;
  height: 26px;
  line-height: 26px;
  margin-left: -3px;
  display: inline-block;
  position: relative;
}
.AppMenu .firstMenu { 
  /* 需要在.AppMenu .menu下 */
  margin-left: -16px;
}
.menu .background {
  line-height: 26px;
  color: #000;
  background: #4b93f4;
  text-align: center;
  transform: skew(50deg);
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  z-index: 0;
}
.menu .title {
  width: 100%;
  text-align: center;
  color: #fff;
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  z-index: 1;
}
.menu_:hover .background {
  background: #73b5f9;
}
.menu_ {
  cursor: pointer;
}
.menu_now {
  cursor: default;
}
.menu_now .background {
  background: #fff;
}
.menu_now .title {
  color: #000;
}
</style>

<!-- index -->
<style scoped>
* {
  margin: 0;
  padding: 0;
  font-family: "Microsoft YaHei Light";
}
.main {
  width: 800px;
  height: 450px;
  position: relative;
  -webkit-touch-callout: none; /* iOS Safari */
  -webkit-user-select: none; /* Chrome/Safari/Opera */
  -khtml-user-select: none; /* Konqueror */
  -moz-user-select: none; /* Firefox */
  -ms-user-select: none; /* Internet Explorer/Edge */
  user-select: none; /* Non-prefixed version, currently */
}
.main_body {
  width: 100%;
  position: absolute;
  top: 0;
  bottom: 0;
}
.main_body_top {
  width: 100%;
  height: 200px; /*.main_body_data的top一起修改*/
  background: url("/Weteoes/Client/Main/index/image/top.png");
  background-size: 100% 100%;
  position: relative;
}
.main_body_top .top_data {
  width: 100%;
  height: 80px;
  margin-top: 30px;
  overflow: hidden;
}
.top_data .top_data_body {
  width: 600px;
  height: 80px;
  margin-left: 80px;
}
.top_data_body .top_data_body_one {
  width: 80px;
  height: 80px;
  background: url("/Weteoes/Client/Main/index/image/computer.png");
  background-size: 100% 100%;
  display: inline-block;
  vertical-align: top;
}
.top_data_body .top_data_body_two {
  width: auto;
  height: 70px;
  min-width: 100px;
  margin-left: 15px;
  display: inline-block;
  vertical-align: top;
}
.top_data_body_two .top_title_one {
  width: auto;
  height: 40px;
  line-height: 50px;
  font-size: 21px;
  color: #fff;
}
.top_data_body_two .top_title_two {
  width: auto;
  height: 30px;
  line-height: 36px;
  font-size: 21px;
  color: #fff;
}
.top_data_body_two .success {
  color: #31fd6a;
}
.main_body_data {
  width: 100%;
  height: auto;
  position: absolute;
  top: 200px;
  right: 0;
  bottom: 0;
  left: 0;
}
</style>

<script>
import data_control from './main/control'
import data_setting from './main/setting'
import data_about from './main/about'

export default {
  data() {
    return {
      v_w: window.Weteoes,
      v_systemMenu_Mini: true, // 用于刷新Mini按钮
      v_menu_nowID: "data_setting", // 当前菜单
      // language
      v_languageNext: "zh_CN", // 下一个要切换的语言
      v_languageConfig: {}, // 语言配置
      // menu
      v_menus: [], // 菜单
      ////// basic
      v_basic_user: "Loading", // 登录用户
    };
  },
  components: {
    'data_control': data_control,
    'data_setting': data_setting,
    'data_about': data_about,
  },
  methods: {
    f_ready: function() {
      this.f_menu(); // 初始化菜单
      this.f_basic(); // 获取配置
    },
    // f_ready End
    // 初始化菜单
    f_menu: function() {
      this.v_menus.length = 0;
      this.v_menus.push({ id: "data_setting", title: this.v_languageConfig.id.Language_Menu_Setting });
      this.v_menus.push({ id: "data_control", title: this.v_languageConfig.id.Language_Menu_Control });
      this.v_menus.push({ id: "data_about", title: this.v_languageConfig.id.Language_Menu_About });
      this.v_menus.push({ id: "data_language", title: this.v_languageNext });
    },
    // f_menu End
    f_systemMenuClick: function(a) {
      switch (a) {
        case 0: // Exit
          this.v_w.app.SystemMenu.Exit();
          break;
        case 1: // Mini
          this.v_systemMenu_Mini = false;
          this.v_w.app.SystemMenu.Mini();
          setTimeout(() => {
            this.v_systemMenu_Mini = true;
          }, 100);
          break;
      }
    },
    // (最小化/关闭)f_systemMenuClick End
    // 切换页面
    f_menuClick: function(a) {
      switch (a) {
        case "data_language": // 如果是切换语言
          this.f_language(this.v_languageNext);
          this.f_menu(); // 初始化菜单
          break;
        default:
          // 切换页面
          this.v_menu_nowID = a;
          break;
      }
    },
    // f_menuClick End
    f_language: function(type) {
      let zh_CN_Config = () => {
        var a = {};
        a.Basic = {};
        a.Basic.Title = "简体中文";
        a.Basic.Code = "zh_CN";
        a.id = {};
        a.id.Language_top_title_one = "当前用户: ";
        a.id.Language_top_title_two = "服务器连接成功";
        a.id.Language_Menu_Setting = "设置";
        a.id.Language_Menu_Control = "远程控制";
        a.id.Language_Menu_About = "关于";
        a.id.Language_Setting_ComputerName = "电脑名称: ";
        a.id.Language_Setting_Reboot = "该操作需要重启软件才能生效";
        a.id.Language_Control_Title = "选择一个想要控制的电脑:";
        a.id.Language_About_Version = "版本: ";
        a.id.Language_About_Company = "公司: ";
        return a;
      };
      let en_US_Config = () => {
        var a = {};
        a.Basic = {};
        a.Basic.Title = "English";
        a.Basic.Code = "en_US";
        a.id = {};
        a.id.Language_top_title_one = "Login User: ";
        a.id.Language_top_title_two = "Service connection success";
        a.id.Language_Menu_Setting = "Setting";
        a.id.Language_Menu_Control = "Control";
        a.id.Language_Menu_About = "About";
        a.id.Language_Setting_ComputerName = "Computer Name: ";
        a.id.Language_Setting_Reboot = "This operation requires restarting the software.";
        a.id.Language_Control_Title = "Choose a computer you want to control:";
        a.id.Language_About_Version = "Version: ";
        a.id.Language_About_Company = "Company: ";
        return a;
      };
      switch (type) {
        case "zh_CN":
          this.v_languageConfig = zh_CN_Config();
          this.v_languageNext = "en_US";
          break;
        // case "en_Us":
        //   this.v_languageConfig = en_US_Config();
        //   this.v_languageNext = "zh_CN";
        //   break;
        default:
          type = "en_Us";
          this.v_languageConfig = en_US_Config();
          this.v_languageNext = "zh_CN";
          break;
      }
      this.v_w.app.Main.All.Set_Language(type); // 保存配置
    },
    // f_language End
    
    ////// basic
    f_basic: function() {
      this.f_basic_user(); // 获取用户信息
    },
    // f_basic End
    f_basic_user: function() {
      let w = this.v_w;
      let session = this.f_config().get().getSession();
      w.JS_Basic.Ajax(
        w.url.operating_getUserInfo,
        { w:session },
        (result) => {
          if(result.status != 200) { this.f_msg("服务器开小差了", true, "error"); return; }
          let resultData = result.data;
          if(resultData.code != 0) { this.f_msg("服务器开小差了", true, "error"); return; } 
          this.v_basic_user = resultData.user; // 设置用户
        }
      )
    },
    // f_basic_user End
    f_msg: function(title, client, type) {
      this.v_w.function.msg(title, client, type);
    },
    // (服务器错误)f_error End

    ////// Config
    f_config: function() {
      let a = {};
      let Config = this.v_w.app.Main;
      a.set = (w_menu, New_Data) => { //修改配置
        this.v_w.function.msg("Menu:{0} Data:{1}".format(w_menu, New_Data));
        //switch (w_menu) {}
      };
      a.get = () => { //获取配置
        let result = {};
        result.getSession = () => { return Config.All.Get_w(); };
        return result;
      };
      return a;
    }
    // f_config End
  },
  mounted() {
    this.f_ready();
  },
  created() {
    this.f_language(this.v_w.JS_Basic.GetQueryString("Language")); // Language
  }
};
</script>