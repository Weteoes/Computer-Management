<template>
  <div class="login" @keydown="sumbitKeydown">
    <div class="login_body">
      <div class="SystemMenu">
        <div class="menu exit" id="exit" @click="systemMenuClick(0)">×</div>
        <div class="menu mini" id="mini" @click="systemMenuClick(1)" v-if="systemMenu_Mini">-</div>
      </div>
      <div class="login_body_center">
        <div class="icon"></div>
        <div class="title">Computer Management</div>
        <div class="input">
          <input type="text" spellcheck="false" placeholder="User" id="User" v-model="input.user" />
          <div class="error" v-if="inputError.user">×</div>
        </div>
        <div class="input">
          <input type="password" placeholder="Password" id="Password" v-model="input.pass" />
          <div class="error" v-if="inputError.pass">×</div>
        </div>
        <div class="error" v-text="errorMsg"></div>
        <div class="submit" id="login" @click="sumbitClick">Submit</div>
      </div>
    </div>
    <div class="login_background">
      <div class="login_background_img"></div>
    </div>
  </div>
</template>

<style scoped>
.login {
  width: 300px;
  height: 400px;
  position: relative;
  overflow: hidden;
  -webkit-touch-callout: none; /* iOS Safari */
  -webkit-user-select: none; /* Chrome/Safari/Opera */
  -khtml-user-select: none; /* Konqueror */
  -moz-user-select: none; /* Firefox */
  -ms-user-select: none; /* Internet Explorer/Edge */
  user-select: none; /* Non-prefixed version, currently */
}
.login_body {
  width: 300px;
  height: 400px;
  position: absolute;
  top: 0;
  left: 0;
  z-index: 1;
}
.login_background {
  width: 100%;
  height: 280px;
  position: absolute;
  top: 0;
  left: 0;
  z-index: 0;
  background-image: linear-gradient(
    rgba(255, 255, 255, 0),
    rgba(255, 255, 255, 1)
  );
}
.login_background_img {
  height: 280px;
  background: url("/Weteoes/Client/Login/index/image/background.jpg") 100%;
  mix-blend-mode: overlay;
}
.login_body_center {
  width: 230px;
  height: 240px;
  margin: 26px auto;
}
.login_body_center .icon {
  width: 70px;
  height: 70px;
  background: url("/Weteoes/Client/Login/index/image/icon.png");
  background-size: 100%;
  margin: 0 auto 10px;
}
.login_body_center .title {
  width: 100%;
  height: 26px;
  font-size: 16px;
  color: #eceaea;
  margin: 0 auto 30px;
  text-align: center;
}
.login_body_center .input {
  width: 100%;
  height: 35px;
  margin: 0 auto 10px;
  position: relative;
}
.login_body_center .input input {
  width: 100%;
  height: 35px;
  line-height: 35px;
  position: absolute;
  top: 0;
  left: 0;
  font-size: 16px;
  color: #4c4b4b;
  caret-color: #4c4b4b;
  background: transparent;
  border: none;
  border-bottom: 1px solid #ababab;
  outline: none;
}
.login_body_center .input .error {
  width: 20px;
  height: 20px;
  position: absolute;
  top: 5px;
  right: 5px;
  color: #fb4d4d;
  font-size: 26px;
  line-height: 20px;
}
.login_body_center .error {
  width: 100%;
  height: 20px;
  color: #fb4d4d;
  font-size: 15px;
  line-height: 20px;
}
.login_body_center .submit {
  width: 100%;
  height: 40px;
  margin: 20px auto;
  color: #fff;
  text-align: center;
  line-height: 40px;
  background: #23aff3;
  cursor: pointer;
  border-radius: 20px;
}
.login_body_center .submit:hover {
  background: #14a7ef;
}
</style>
<style>
.SystemMenu {
  width: 100%;
  height: 24px;
}
.SystemMenu .menu {
  width: 30px;
  height: 24px;
  line-height: 24px;
  text-align: center;
  float: right;
  border-radius: 1px;
  transition: 0.3s;
  cursor: pointer;
}
.SystemMenu .exit {
  font-size: 26px;
  line-height: 24px;
}
.SystemMenu .mini {
  font-size: 26px;
  line-height: 24px;
}
.SystemMenu .exit:hover { background: #fb4d4d; }
.SystemMenu .mini:hover { background: rgba(66, 86, 239, 0.78); }
.SystemMenu .mini:active { background: unset; }
.SystemMenu .mini:hover+.SystemMenu .mini:active { background: unset; }
</style>

<script>
export default {
  data () {
    return {
      w: window.weteoes,
      systemMenu_Mini: true, // 用于刷新Mini按钮
      errorMsg: '',
      input: { user: '', pass: '' },
      inputError: { user: false, pass: false }
    }
  },
  methods: {
    ready: function () {
      this.w.softwareFun.addDlgMouseEvent(document.querySelector('.SystemMenu')) // 拖动条
      this.$parent.readyCEFSize('.login') // 窗口大小
    },
    // 登录事件
    sumbitClick: function () {
      const ffError = msg => {
        this.errorMsg = msg
      } // 统一错误
      const ffFinished = deleteUser => {
        // 清除输入框数据
        if (deleteUser) {
          this.input.user = ''
        }
        this.input.pass = ''
      }
      const ffPd = () => {
        // 本地判断是否为空
        const user = this.input.user
        const pass = this.input.pass
        let result = true
        if (user === '') {
          this.inputError.user = true
          result = false
        }
        if (pass === '') {
          this.inputError.pass = true
          result = false
        }
        return result
      }
      const ffInitialization = () => {
        // 清空所有错误信息
        this.errorMsg = ''
        this.inputError.user = this.inputError.pass = false
      }
      // Code
      const w = this.w
      ffInitialization()
      if (!ffPd()) {
        return
      }
      w.basic.ajax(
        w.url.operating_sign_in,
        'post',
        { user: this.input.user, pass: this.input.pass },
        result => {
          const resultData = result.data
          if (resultData.code === 0) {
            // success
            this.w.softwareApi.app('Login', 'Signin', { w: resultData.w })
            this.w.softwareApi.app('Login', 'createMainDlg') // 创建窗口
            ffFinished(true)
          } else {
            ffError('Username or Password Error')
            ffFinished()
          }
        },
        () => {
          ffError('Login Sign_in Error')
          ffFinished()
        }
      )
    },
    // 登录事件End
    // Keydown
    sumbitKeydown: function (a) {
      if (a.keyCode === 13) {
        this.sumbitClick()
      }
    },
    // Keydown End
    // systemMenuClick
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
    }
    // systemMenuClick End
  },
  mounted () {
    if (this.$store.state.debug) {
      window.debug = this
    }
    this.ready()
  }
}
</script>
