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
                  v-text="languageConfig.id.Language_top_title_one"
                >Login User:</span>
                <span id="User" v-text="v_basic_user"></span>
              </div>
              <div
                class="top_title_two success"
                id="Language_top_title_two"
                v-text="languageConfig.id.Language_top_title_two"
              >Service connection success</div>
            </div>
          </div>
        </div>
        <div class="AppMenu">
          <div
            class="menu"
            style="margin-left: -16px;"
            v-bind:class="{menu_now: menu_nowID == 'data_setting', menu_:menu_nowID != 'data_setting'}"
            @click="f_menuClick('data_setting')"
          >
            <div
              class="title"
              id="Language_Menu_Setting"
              v-text="languageConfig.id.Language_Menu_Setting"
            >Setting</div>
            <div class="background"></div>
          </div>
          <div
            class="menu"
            v-bind:class="{menu_now: menu_nowID == 'data_about', menu_:menu_nowID != 'data_about'}"
            @click="f_menuClick('data_about')"
          >
            <div
              class="title"
              id="Language_Menu_About"
              v-text="languageConfig.id.Language_Menu_About"
            >About</div>
            <div class="background"></div>
          </div>
          <div
            class="menu"
            v-bind:class="{menu_now: menu_nowID == 'data_language', menu_:menu_nowID != 'data_language'}"
            @click="f_menuClick('data_language')"
          >
            <div class="title" id="Language_Menu_Language">简体中文</div>
            <div class="background"></div>
          </div>
        </div>
      </div>
      <div class="main_body_data">
        <!-- Seteting -->
        <div class="data_all data_setting" v-if="menu_nowID == 'data_setting'">
          <div class="data_setting_center">
            <div class="information" id="Language_Setting_Reboot" v-text="v_setting_Information"></div>
            <!-- 选项区域 -->
            <!-- 电脑名称 -->
            <div class="setting_edit" ref="ref_setting_computerName">
              <div
                class="title"
                w_menu="Computer_Name"
                id="Language_Setting_ComputerName"
                v-text="languageConfig.id.Language_Setting_ComputerName"
              >Computer Name:</div>
              <div class="data" v-bind:class="{no_diskplay: v_setting_computerName_Edit}">
                <span id="Setting_Computer_Name" v-text="v_setting_computerName">Computer</span>
                <div class="editButton" @click="f_setting_computerNameEditClick"></div>
              </div>
              <div class="edit" v-bind:class="{no_diskplay: !v_setting_computerName_Edit}">
                <input type="text" spellcheck="false" maxlength="20" val="Computer" />
              </div>
            </div>
            <!-- 选项区域 End -->
          </div>
        </div>
        <!-- About -->
        <div class="data_all data_about" v-if="menu_nowID == 'data_about'">
          <div class="data_about_center">
            <div class="about_text">
              <div
                class="title"
                id="Language_About_Version"
                v-text="languageConfig.id.Language_About_Version"
              >Version:</div>
              <div class="data">
                <span id="About_Version" v-text="v_about_version"></span>
              </div>
            </div>
            <div class="about_text">
              <div
                class="title"
                id="Language_About_Company"
                v-text="languageConfig.id.Language_About_Company"
              >Company:</div>
              <div class="data">
                <span>Weteoes</span>
              </div>
            </div>

            <div class="about_end">Weteoes.All Rights Reserved</div>
          </div>
        </div>
      </div>
    </div>
    <div class="login_background">
      <div class="login_background_img"></div>
    </div>
  </div>
</template>

<!-- data_about -->
<style scoped>
.main_body_data .data_about {
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
}
.data_about .data_about_center {
  width: 700px;
  height: auto;
  min-height: 40px;
  margin: 40px auto;
}
.data_about_center .about_text {
  width: 100%;
  height: 30px;
}
.about_text .title {
  width: auto;
  height: 30px;
  font-size: 17px;
  line-height: 30px;
  color: #000;
  display: inline-block;
  vertical-align: top;
  margin: 0 10px 0 0;
}
.about_text .data {
  width: auto;
  height: 30px;
  font-size: 17px;
  line-height: 30px;
  color: #000;
  display: inline-block;
  vertical-align: top;
}
.about_end {
  width: 100%;
  height: 30px;
  line-height: 30px;
  font-size: 15px;
  text-align: center;
  position: absolute;
  right: 0;
  bottom: 0;
  left: 0;
}
</style>

<!-- data_setting -->
<style scoped>
.main_body_data .data_setting {
  width: 100%;
  height: auto;
}
.data_setting .data_setting_center {
  width: 700px;
  height: auto;
  min-height: 40px;
  margin: 10px auto;
}
.data_setting_center .setting_edit {
  width: 100%;
  height: 30px;
}
.setting_edit .title {
  width: auto;
  height: 30px;
  margin: 0 10px 0 0;
  font-size: 17px;
  line-height: 30px;
  color: #000;
  display: inline-block;
  vertical-align: top;
}
.setting_edit .data {
  width: auto;
  height: 30px;
  font-size: 17px;
  line-height: 30px;
  color: #000;
  display: inline-block;
  vertical-align: top;
}
.setting_edit .editButton {
  width: 30px;
  height: 30px;
  background: url("/Weteoes/Client/Main/index/image/edit.png") 7px 7px no-repeat;
  background-size: 60% 60%;
  cursor: pointer;
  display: inline-block;
  vertical-align: top;
}
.setting_edit .edit {
  min-width: 100px;
  height: 30px;
  display: inline-block;
  vertical-align: top;
}
.setting_edit .edit input {
  width: 200px;
  height: 30px;
  line-height: 30px;
  font-size: 17px;
  outline: none;
  border: none;
  border-bottom: 1px solid #000;
}
.data_setting_center .information {
  width: 100%;
  height: 30px;
  line-height: 30px;
  color: #f31b1b;
  font-size: 16px;
  font-weight: bold;
}
.setting_edit .no_diskplay {
  display: none;
}
</style>

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
export default {
  data() {
    return {
      v_w: window.Weteoes,
      v_systemMenu_Mini: true, // 用于刷新Mini按钮
      menu_nowID: "data_setting", // 当前菜单
      // language
      languageNext: "zh_CN", // 下一个要切换的语言
      languageConfig: {}, // 语言配置
      ////// basic
      v_basic_user: "Loading", // 登录用户
      ////// data_setting
      v_setting_Information: "", //  提示消息
      v_setting_computerName: "", // 电脑名称
      v_setting_computerName_Edit: false, // 是否编辑电脑名称
      ////// data_about
      v_about_version: "3.6.1987.1524", // 版本信息
    };
  },
  methods: {
    f_ready: function() {
      // 获取配置
      this.f_basic();
      this.f_setting();
    },
    // f_ready End
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
    f_menuClick: function(a) {
      switch (a) {
        case "data_language": // 如果是切换语言
          this.f_language(this.languageNext);
          break;
        default:
          // 切换页面
          this.menu_nowID = a;
          switch(a) {
            case "data_setting": this.f_config().get().setting(); break;
            case "data_about": this.f_config().get().about(); break;
          }
          break;
      }
    },
    // (切换页面)f_menuClick End
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
        a.id.Language_Menu_About = "关于";
        a.id.Language_Setting_ComputerName = "电脑名称: ";
        a.id.Language_Setting_Reboot = "该操作需要重启软件才能生效.";
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
        a.id.Language_Menu_About = "About";
        a.id.Language_Setting_ComputerName = "Computer Name: ";
        a.id.Language_Setting_Reboot =
          "This operation requires restarting the software.";
        a.id.Language_About_Version = "Version: ";
        a.id.Language_About_Company = "Company: ";
        return a;
      };
      switch (type) {
        case "zh_CN":
          this.languageConfig = zh_CN_Config();
          this.languageNext = "en_US";
          break;
        // case "en_Us":
        //   this.languageConfig = en_US_Config();
        //   this.languageNext = "zh_CN";
        //   break;
        default:
          type = "en_Us";
          this.languageConfig = en_US_Config();
          this.languageNext = "zh_CN";
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
          if(result.status != 200) { return; }
          let resultData = result.data;
          if(resultData.code == 0) { this.v_basic_user = resultData.user; } // 设置用户
        }
      )
    },
    // f_basic_user End

    ////// data_setting
    f_setting: function() {
      this.f_config().get().setting(); // 获取配置
    },
    // f_setting End
    f_setting_computerNameEditClick: function() {
      let computerName_Div = this.$refs.ref_setting_computerName.querySelector(
        "#Setting_Computer_Name"
      ); // 原始内容Div
      let EditInput = this.$refs.ref_setting_computerName.querySelector(
        "input"
      ); // Edit Div
      let oldConputerName = computerName_Div.innerText, newComputerName; // 保存旧的和新的电脑名称
      let edit_on = () => {
        // 开始编辑
        EditInput.value = oldConputerName; // 设置编辑框内文字
        setTimeout(() => {
          EditInput.focus();
        }, 10); // 获取焦点
        document
          .querySelector(".setting_edit")
          .querySelector("input")
          .focus();
        document.onclick = edit_off; // 设置全局click事件
        document.onkeydown = a => {
          if (a.keyCode == 13) {
            edit_off();
          }
        }; // 设置全局keydown事件
        this.v_setting_computerName_Edit = true;
      };
      let edit_off_PD = () => {
        // 判断数据是否正确
        newComputerName = computerName_Div.innerText.trim();
        if (newComputerName == "") {
          return false;
        }
        if (oldConputerName == newComputerName) {
          return false;
        }
        return true;
      };
      let edit_off = a => {
        // 结束编辑
        if (
          a != undefined &&
          (a.target.className == "editButton" || a.target.nodeName == "INPUT")
        ) {
          return;
        }
        computerName_Div.innerText = EditInput.value; // 设置编辑框内文字
        document.onclick = null; // 取消全局click事件
        document.onkeydown = null; // 取消全局keydown事件
        if (edit_off_PD()) { this.f_config().set("ComputerName", newComputerName); } // 数据正确就保持
        this.v_setting_computerName_Edit = false;
      };
      edit_on();
    },
    // f_setting_computerNameEditClick End

    ////// data_about
    f_about: function() {
      this.f_config().get().about(); // 获取配置
    },
    // f_about End
    ////// Config
    f_config: function() {
      let a = {};
      let Config = this.v_w.app.Main;
      a.set = (w_menu, New_Data) => { //修改配置
        this.v_w.function.msg("Menu:{0} Data:{1}".format(w_menu, New_Data));
        switch (w_menu) {
          case "ComputerName": {
            Config.Setting.Set_ComputerName(New_Data);
            this.v_setting_Information = this.languageConfig.id.Language_Setting_Reboot;
            break;
          }
        }
      };
      a.get = () => { //获取配置
        let result = {};
        // setting
        result.setting = () => {
          let Computer_Name = () => { this.v_setting_computerName = Config.Setting.Get_ComputerName(); }
          Computer_Name();
        };
        // about
        result.about = () => {
          let Version = () => { this.v_about_version = Config.About.Get_Version(); }
          Version();
        };
        // v
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