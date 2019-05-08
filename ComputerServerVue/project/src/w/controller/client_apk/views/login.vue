<template>
  <!-- 
    设置宽高
    keydown事件
  -->
  <div
    class="w_data"
    :style="'width:'+this.ready.w+'px;'+'height:'+this.ready.h+'px'"
    @keydown="sumbitKeydown"
  >
    <!-- Css -->
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <!-- Html -->
    <div class="w_body">
      <!-- SystemMenu -->
      <div class="systemMenu"></div>
      <!-- Data -->
      <div class="login_body_data">
        <div class="data_icon">
          <div class="data_icon_img"></div>
          <div class="data_icon_title">Computer Management</div>
        </div>
        <!-- User -->
        <div class="data_input" style="margin-top:50px;">
          <input type="text" v-model="input.user" placeholder="User">
        </div>
        <!-- Pass -->
        <div class="data_input">
          <input type="password" v-model="input.pass" placeholder="Password">
        </div>
        <!-- Sumbit -->
        <div class="data_sumbit" @click="sumbitClick">登录</div>
      </div>
    </div>
    <div class="w_background login_background"></div>
  </div>
</template>
<style scoped>
.login_background {
  background: url("/Weteoes/Client_apk/Login/index/image/background.png");
}
.login_body_data {
  width: 220px;
  height: auto;
  margin: 110px auto;
}
.login_body_data .data_icon {
  width: 100%;
  height: auto;
}
.data_icon .data_icon_img {
  width: 80px;
  height: 80px;
  background: url("/Weteoes/Client_apk/Login/index/image/icon.png") no-repeat;
  background-size: 100%;
  margin: 0 auto;
}
.data_icon .data_icon_title {
  width: 100%;
  height: 24px;
  line-height: 24px;
  margin-top: 10px;
  color: #000;
  font-size: 16px;
  text-align: center;
}
.login_body_data .data_input {
  width: 100%;
  height: 35px;
  margin-top: 20px;
}
.login_body_data input {
  width: 100%;
  height: 35px;
  line-height: 35px;
  font-size: 16px;
  color: #4c4b4b;
  caret-color: #4c4b4b;
  outline: none;
  border: none;
  border-bottom: 1px solid #000;
  background: transparent;
}
.login_body_data .data_sumbit {
  width: 100%;
  height: 35px;
  line-height: 35px;
  margin-top: 60px;
  font-size: 15px;
  color: #fff;
  background: #55b1f8;
  border-radius: 20px;
  text-align: center;
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
            window.localStorage.setItem("w", resultData.w);
            this_.$router.push(w.url.main);
          } else {
            w.function.msg("用户名或密码错误", 2);
          }
        },
        function(error) {
          w.function.msg("意外的错误"+error, 2);
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
    },
    // sumbitClick End
  },
  mounted() {
    // 初始化
    this.w.function.ready();
    // 判断是否登录
    this.w.function.isLogin(
      ()=>{ //登录成功
        this.$router.push(this.w.url.main);
      },
      ()=>{ //登录失败
        this.ready_(); 
      }
    );
    // 判断是否登录 End
  }
};
</script>