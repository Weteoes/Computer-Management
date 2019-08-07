<template>
  <div class="login" @keydown="f_sumbitKeydown">
    <div class="login_body">
      <div class="SystemMenu">
        <div class="menu exit" id="exit" @click="f_systemMenuClick(0)">×</div>
        <div class="menu mini" id="mini" @click="f_systemMenuClick(1)" v-if="v_systemMenu_Mini">-</div>
      </div>
      <div class="login_body_center">
        <div class="icon"></div>
        <div class="title">Computer Management</div>
        <div class="input">
          <input type="text" spellcheck="false" placeholder="User" id="User" v-model="v_input.user">
          <div class="error" v-if="v_inputError.user">×</div>
        </div>
        <div class="input">
          <input type="password" placeholder="Password" id="Password" v-model="v_input.pass">
          <div class="error" v-if="v_inputError.pass">×</div>
        </div>
        <div class="error" v-text="v_errorMsg"></div>
        <div class="submit" id="login" @click="f_sumbitClick">Submit</div>
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

<script>
export default {
  data() {
    return {
      v_w: window.Weteoes,
      v_systemMenu_Mini: true, // 用于刷新Mini按钮
      v_errorMsg: "",
      v_input: { user: "", pass: "" },
      v_inputError: { user: false, pass: false },
    };
  },
  methods: {
    f_ready: function() {},
    // 登录事件
    f_sumbitClick: function() {
      let ff_error = (msg) => { this.v_errorMsg = msg; }; //统一错误
      let ff_finished = (deleteUser) => { // 清除输入框数据
        if(deleteUser) { this.v_input.user = "";} 
        this.v_input.pass = "";
      }
      let ff_pd = () => { // 本地判断是否为空
        let user = this.v_input.user,
            pass = this.v_input.pass;
        let result = true;
        if(user == "") { this.v_inputError.user = true; result = false; }
        if(pass == "") { this.v_inputError.pass = true; result = false; }
        return result;
      }
      let ff_initialization = () => { // 清空所有错误信息
        this.v_errorMsg = "";
        this.v_inputError.user = this.v_inputError.pass = false;
      }
      // Code
      let v_w = this.v_w;
      ff_initialization();
      if(!ff_pd()) { return; }
      v_w.JS_Basic.Ajax(
        v_w.url.operating_sign_in,
        { user: this.v_input.user, pass: this.v_input.pass },
        (result) => {
          let resultData = result.data;
          if (resultData.code == 0) { //success
            v_w.app.Login.Login(resultData.w);
            ff_finished(true);
          } else {
            ff_error("Username or Password Error");
            ff_finished();
          }
        },
        () => {
          ff_error("Login Sign_in Error");
          ff_finished();
        }
      );
    },
    // 登录事件End
    // Keydown
    f_sumbitKeydown: function(a) {
      if (a.keyCode == 13) {
        this.f_sumbitClick();
      }
    },
    // Keydown End
    // systemMenuClick
    f_systemMenuClick: function(a) {
      switch(a) {
        case 0: // Exxit
          this.v_w.app.SystemMenu.Exit();
          break;
        case 1: // Mini
          this.v_systemMenu_Mini = false;
          this.v_w.app.SystemMenu.Mini();
          setTimeout(() => { this.v_systemMenu_Mini = true; }, 100);
          break;
      }
    },
    // systemMenuClick End
  },
  mounted() {
    this.f_ready();
  }
};
</script>
