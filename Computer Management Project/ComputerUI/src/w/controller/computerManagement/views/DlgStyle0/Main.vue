<template>
  <div class="main">
    <div class="main_body">
      <div class="main_body_top">
        <div class="SystemMenu">
          <!-- <div class='menu exit' id='exit'>×</div> -->
          <div class="menu mini" id="mini" @click="systemMenuClick(1)" v-if="systemMenu_Mini">×</div>
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
                <span id="User" v-text="basic_user"></span>
                <span id="SignOut" @click="basicSignOutClick">退出登录</span>
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
            class="menu" v-for="(menu,menuKey) in menus" :key="menu.id"
            v-bind:class= "{ firstMenu: menuKey == 0, menu_now: menu_nowID == menu.id, menu_: menu_nowID != menu.id}"
            @click="menuClick(menu.id)"
          >
            <div
              class="title"
              id="Language_Menu_Setting"
              v-text="menu.title"
            ></div>
            <div class="background"></div>
          </div>
        </div>
      </div>
      <div class="main_body_data">
        <!-- Seteting -->
        <data_setting v-if="menu_nowID == 'data_setting'" v-bind:props_languageConfig="languageConfig"></data_setting>
        <!-- Control -->
        <data_control v-if="menu_nowID == 'data_control'" v-bind:props_languageConfig="languageConfig"></data_control>
        <!-- About -->
        <data_about v-if="menu_nowID == 'data_about'" v-bind:props_languageConfig="languageConfig"></data_about>
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
#SignOut {
  font-size: 14px;
  margin: 0 10px;
  cursor: pointer;
}
</style>

<script>
import viewControl from './main/control'
import viewSetting from './main/setting'
import viewAbout from './main/about'

export default {
  data () {
    return {
      w: window.weteoes,
      systemMenu_Mini: true, // 用于刷新Mini按钮
      menu_nowID: 'data_setting', // 当前菜单
      // language
      languageNext: 'zh_CN', // 下一个要切换的语言
      languageConfig: {}, // 语言配置
      // menu
      menus: [], // 菜单
      /// /// basic
      basic_user: 'Loading' // 登录用户
    }
  },
  components: {
    data_control: viewControl,
    data_setting: viewSetting,
    data_about: viewAbout
  },
  methods: {
    ready: function () {
      this.menu() // 初始化菜单
      this.basic() // 获取配置
      this.w.softwareFun.addDlgMouseEvent(document.querySelector('.SystemMenu')) // 拖动条
      this.$parent.readyCEFSize('.main') // 窗口大小
    },
    // ready End
    // 初始化菜单
    menu: function () {
      this.menus.length = 0
      this.menus.push({ id: 'data_setting', title: this.languageConfig.id.Language_Menu_Setting })
      this.menus.push({ id: 'data_control', title: this.languageConfig.id.Language_Menu_Control })
      this.menus.push({ id: 'data_about', title: this.languageConfig.id.Language_Menu_About })
      this.menus.push({ id: 'data_language', title: this.languageNext })
    },
    // menu End
    systemMenuClick: function (a) {
      switch (a) {
        case 0: // Exxit
          this.w.softwareApi.dlg.close()
          break
        case 1: // Mini
          this.systemMenu_Mini = false
          this.w.softwareApi.dlg.minimize()
          setTimeout(() => {
            this.systemMenu_Mini = true
          }, 100)
          break
      }
    },
    // (最小化/关闭)systemMenuClick End
    // 切换页面
    menuClick: function (a) {
      switch (a) {
        case 'data_language': // 如果是切换语言
          this.language(this.languageNext)
          this.menu() // 初始化菜单
          break
        default:
          // 切换页面
          this.menu_nowID = a
          break
      }
    },
    // menuClick End
    language: function (type) {
      const zhCNConfig = () => {
        var a = {}
        a.Basic = {}
        a.Basic.Title = '简体中文'
        a.Basic.Code = 'zh_CN'
        a.id = {}
        a.id.Language_top_title_one = '当前用户: '
        a.id.Language_top_title_two = '服务器连接成功'
        a.id.Language_Menu_Setting = '设置'
        a.id.Language_Menu_Control = '远程控制'
        a.id.Language_Menu_About = '关于'
        a.id.Language_Setting_ComputerName = '电脑名称: '
        a.id.Language_Setting_Reboot = '该操作需要重启软件才能生效'
        a.id.Language_Control_Title = '选择一个想要控制的电脑:'
        a.id.Language_About_Version = '版本: '
        a.id.Language_About_Company = '公司: '
        return a
      }
      const enUSConfig = () => {
        var a = {}
        a.Basic = {}
        a.Basic.Title = 'English'
        a.Basic.Code = 'en_US'
        a.id = {}
        a.id.Language_top_title_one = 'Login User: '
        a.id.Language_top_title_two = 'Service connection success'
        a.id.Language_Menu_Setting = 'Setting'
        a.id.Language_Menu_Control = 'Control'
        a.id.Language_Menu_About = 'About'
        a.id.Language_Setting_ComputerName = 'Computer Name: '
        a.id.Language_Setting_Reboot = 'This operation requires restarting the software.'
        a.id.Language_Control_Title = 'Choose a computer you want to control:'
        a.id.Language_About_Version = 'Version: '
        a.id.Language_About_Company = 'Company: '
        return a
      }
      switch (type) {
        case 'zh_CN':
          this.languageConfig = zhCNConfig()
          this.languageNext = 'en_US'
          break
        default:
          type = 'en_Us'
          this.languageConfig = enUSConfig()
          this.languageNext = 'zh_CN'
          break
      }
      this.w.softwareApi.app('Main', 'SetLanguage', { type: type })
      // this.w.app.Main.All.Set_Language(type) // 保存配置
    },
    // language End

    /// /// basic
    basic: function () {
      this.basicUser() // 获取用户信息
    },
    // 获取用户信息
    basicUser: function () {
      const w = this.w
      const session = this.config().get().getSession()
      w.basic.ajax(
        w.url.operating_getUserInfo,
        'post',
        { w: session },
        (result) => {
          if (result.status !== 200) { this.msg('服务器开小差了', true, 'error'); return }
          const resultData = result.data
          if (resultData.code !== 0) { this.msg('服务器开小差了', true, 'error'); return }
          this.basic_user = resultData.user // 设置用户
        }
      )
    },
    // 退出登录
    basicSignOutClick: function () {
      this.$confirm('将要退出当前用户, 是否继续?', '', {
        confirmButtonText: '确定',
        cancelButtonText: '取消'
      }).then(() => {
        this.w.softwareApi.app('Login', 'Signin', { w: '' }) // 清空配置
        this.w.softwareApi.app('Login', 'ShowLoginDlg') // 打开登录窗口
      }).catch(() => {})
    },
    msg: function (title, client, type) {
      this.w.function.msg(title, client, type)
    },
    // (服务器错误)error End

    /// /// Config
    config: function () {
      const a = {}
      a.set = (menu, NewData) => { // 修改配置
        this.w.function.msg('Menu:{0} Data:{1}'.format(menu, NewData))
      }
      a.get = () => { // 获取配置
        const result = {}
        result.getSession = () => {
          const w = this.w.softwareApi.app('Main', 'GetSession')
          return w
        }
        return result
      }
      return a
    }
    // config End
  },
  mounted () {
    if (this.$store.state.debug) {
      window.debug = this
    }
    this.ready()
  },
  created () {
    this.language(this.w.basic.getQueryString('Language')) // Language
  }
}
</script>
