<template>
  <!-- keydown事件 -->
  <div class="login" @keydown="sumbitKeydown">
    <div class="w_body">
        <!-- 让div位置调整到适合的位置 -->
      <div class="data" :style="'margin-top:'+data_top+'px'">
        <div class="login_title">
          <div class="a">后台管理系统</div>
          <div class="b">Backstage management System</div>
        </div>
        <div class="login_data">
            <!-- from 设置背景，因为边框不要背景 -->
            <div class="form">
                <div class="occupy"></div>
                <div class="only">
                    <el-input placeholder="请输入用户名" :disabled="input.sumbiting" v-model="input.user" clearable></el-input>
                </div>
                <div class="only">
                     <el-input placeholder="请输入用户名" :disabled="input.sumbiting" v-model="input.pass" show-password></el-input>
                </div>
                <div class="only">
                    <el-button class="sumbit" @click="sumbitClick" :loading="input.sumbiting" type="primary">登录</el-button>
                </div>
                <div class="occupy"></div>
            </div>
        </div>
      </div>
    </div>
    <div class="w_background"></div>
  </div>
</template>

<style lang="scss" scoped>
$minW: 700px;
.login {
  min-height: $minW;
}
.w_background {
    min-height: $minW;
  background: url("/Weteoes/Console/Login/image/back.jpg") 0/100% 100%;
}
.data {
  width: 400px;
  height: 300px;
  position: absolute;
  left: 0;
  right: 0;
  top: 0;
  bottom: 50px;
  margin: auto;
}
.login_title {
    width: 100%;
    height: auto;
    color: #fff!important;
}
.login_title .a {
    font-size: 18px;
}
.login_data {
    border: 5px solid rgba(100, 100, 100, 0.4);
    width: 100%;
    height: auto;
    border-radius: 5px;
    margin-top: 20px;
}
.login_data .form {
    background: #fff;
}
.login_data .form .only {
    width: 80%;
    height: 40px;
    line-height: 40px;
    margin: 0 auto;
    padding: 12px 0;
    text-align: center;
    color: #fff;
}
.login_data .form .occupy{
    width: 100%;
    height: 30px;
}
.login_data .form .sumbit {
    width: 100%;
    margin: 0 auto;
}
</style>


<script>
export default {
    data() {
        return {
          // 全局函数
          w: window.Weteoes,
          // Div调整到适当位置
          data_top: 0,
          // 用户输入 sumbiting加载ing
          input:{  user: "", pass: "", sumbiting: false }
        }
    },
  methods: {
    ready_: function() {
        // data_top
        (()=>{
            let onresize = (first)=>{
                let div_h = document.getElementsByClassName("data")[0].offsetHeight;
                let client_h = window.innerHeight;
                if(!first && client_h < 700) { return; }
                this.data_top = (client_h - div_h) / 2 - 50;
            };
            // 立即调整大小
            onresize(true);
            // 绑定事件
            window.onresize = onresize;
        })();
        // data_top End
    },
    // sumbitKeydown
    sumbitKeydown: function(a) {
      if (a.keyCode == 13) {
        this.sumbitClick();
      }
    },
    // sumbitKeydown End
    sumbitClick: function() {
      // 设置正在加载
      this.input.sumbiting = true;
      // 全局变量
      let this_ = this;
      let w = this.w;
      // 获取用户名和密码
      let user = this.input.user,
          pass = this.input.pass;
      // 判断是否符合规则
      if (!isnull(user, pass)) {
        end();
        return;
      }
      // 提交
      w.JS_Basic.Ajax(
        w.url.operating_sign_in,
        { user: user, pass: pass },
        function(result) {
          if(result.status != 200) { w.function.msg("登录失败", 2, "error"); end(); return; }
          let resultData = result.data;
          if (resultData.code != 0) { w.function.msg("用户名或密码错误", 2, "error"); end(); return; }
          // Session
          window.localStorage.setItem("w", resultData.w);
          this_.$router.push(w.url.management);
        },
        function(error) {
          w.function.msg("服务器开小差了 msg:"+error, 2, "error");
          end();
        }
      );
      // 提交 End

      // 完成
      function end() {
        // 设置可以点击
        this_.input.sumbiting = false;
      }
      // 完成 End
      // isnull
      function isnull(user, pass) {
        if (user == "" || pass == "") {
          w.function.msg("用户名或密码不能为空", 2, "error");
          return false;
        } else if (user == undefined || pass == undefined) {
          w.function.msg("用户名密码获取失败", 2, "error");
          return false;
        } else if (pass.length < 6) {
          w.function.msg("请输入正确的密码", 2, "error");
          return false;
        }
        return true;
      }
      // isnull End
    }
  },
  mounted() {
    // 判断是否登录
    this.w.function.isLogin(
      ()=>{ //登录成功
        this.$router.push(this.w.url.management);
      },
      ()=>{ //登录失败
        this.ready_(); 
      }
    );
    // 判断是否登录 End
  }
};
</script>
