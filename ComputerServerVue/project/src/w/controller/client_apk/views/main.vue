<template>
  <!-- 设置宽高 -->
  <div class="w_data" :style="'width:'+this.ready.w+'px;'+'height:'+this.ready.h+'px'">
    <div class="w_body">
      <!-- <div class='systemMenu'>Main1</div> -->
      <div class="main_nav">
        <div class="one"></div>
        <div class="two main_nav_two">
          <div class="left main_nav_two main_nav_inline"></div>
          <!-- <div class='menu main_nav_menu main_nav_two main_nav_inline'>
                            <img class='main_nav_menu' src='/Weteoes/Client_apk/Main/computer/image/more.png' />
          </div>-->
          <div class="title main_nav_two main_nav_inline">控制中心</div>
        </div>
      </div>
      <div class="main_data">
        <!-- All Computer Vue -->
        <div class="main_computer">
          <!-- Only Computer -->
          <!-- 
            For循环电脑
            设置点击事件
          -->
          <div
            class="data_computer data_computer_"
            v-for="(onlyComputer,number) in allComputer" :key="number"
            @click="click_computer(onlyComputer.name)"
            @click.stop
          >
            <div class="left data_computer_">
              <div class="icon"></div>
            </div>
            <div class="right data_computer_ data_computer_right_">
              <div class="computer data_computer_right_">
                <div class="one">
                  电脑名称:
                  <span v-html="onlyComputer.name">NoteBook</span>
                </div>
                <div class="one">
                  <div class="online_icon">
                    <!--这个空div是icon-->
                    <div></div>
                  </div>
                  <div class="online_title">在线</div>
                </div>
              </div>
            </div>
            <div class="bottom"></div>
          </div>
          <div class="data_computer_null" v-if="allComputer.length==0 && nullDiv == true"></div>
          <!-- Only Computer End -->
        </div>
        <!-- All Computer Vue End -->
      </div>
      <!-- Bottom -->
      <div class="main_bottom">
        <span>仅展示当前在线设备</span>
      </div>
      <!-- Bottom End -->
    </div>
    <div class="w_background main_background"></div>
  </div>
</template>

<!-- index.css -->
<style scoped>
.main_background {
  background: #fff;
}
.main_data {
  width: 100%;
  height: auto;
}
.main_computer {
  padding-bottom: 22px;
}
/* .data_computer {
} */
.data_computer_null {
  width: 80px;
  height: 80px;
  background: url("/Weteoes/Client_apk/Main/index/image/TAT.png") no-repeat;
  background-size: 100%;
  margin: 260px auto 0;
}
.data_computer_ {
  height: 90px;
}
.data_computer .left {
  width: 100px;
  display: inline-block;
  vertical-align: top;
}
.data_computer .right {
  display: inline-block;
  vertical-align: top;
}
.data_computer_right_ {
  width: 200px;
}
.data_computer .bottom {
  height: 2px;
  background: url("/Weteoes/Client_apk/Main/index/image/bottom.png") 100%;
}
.data_computer .icon {
  margin: 12px 0 0 20px;
  width: 70px;
  height: 70px;
  background: url("/Weteoes/Client_apk/Main/index/image/computer.png");
  background-size: 100%;
}
.data_computer .right .computer {
  height: 60px;
  padding-left: 20px;
  padding-top: 17px;
}
.data_computer .right .computer .one {
  height: 30px;
  line-height: 30px;
  color: #46abf8;
  font-size: 14px;
}
.computer .one .online_icon {
  height: 30px;
  display: inline-block;
  vertical-align: top;
}
.computer .one .online_icon div {
  width: 16px;
  height: 16px;
  margin: 7px 0;
  background: url("/Weteoes/Client_apk/Main/index/image/online.png");
  background-size: 15px;
  background-repeat: no-repeat;
}
.computer .one .online_title {
  height: 30px;
  margin-left: 6px;
  display: inline-block;
  vertical-align: top;
}
</style>

<!-- main_bottom.css -->
<style scoped>
.main_bottom {
  width: 100%;
  height: 22px;
  line-height: 22px;
  position: absolute;
  bottom: 0;
  left: 0;
  right: 0;
  background: #afafac;
}
.main_bottom span {
  color: #fff;
  margin-left: 5px;
  font-size: 14px;
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
      // data
      allComputer: [],
      nullDiv: false
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
          window.console.log("重新获取设备列表");
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
      w.JS_Basic.Ajax(w.url.operating_getComputerList, { w: this_.session }, function(result) {
        if (result.status != 200) { w.function.msg("服务器开小差啦", 2); return; }
        let resultData = result.data;
        // 因为有转发所以加JSON.parse
        resultData =  JSON.parse(resultData);
        if(resultData.code == -1) { w.function.msg("获取设备信息失败 msg:{msg}".format({msg: resultData.msg}), 2); return; }
        // 判断是否为undefined
        if (typeof resultData.user == "undefined") {
          return;
        }
        // if(result.user.length === 0){ w.function.msg("当前没有电脑在线", 2); }

        /* 获取信息 */
        var result_a = resultData.user;
        var allComputer = [];
        for (let only in result_a) {
          allComputer.push({ name: result_a[only].computer });
        }

        /* Vue */
        this_.nullDiv = true;
        this_.allComputer = allComputer;
      });
    },
    // getComputer End
    // 电脑点击事件
    click_computer: function(computerName) {
      let url = "{url}computerName={computerName}".format({ 
        url: this.w.url.mainComputer,
        computerName: computerName 
      });
      this.$router.push(url);
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
      body_.style.position = "relative";
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
      ()=>{ 
        // 登录成功
        // 设置全局session
        this.session = window.localStorage.getItem("w");
        this.ready_(); 
      },
      ()=>{ // 登录失败
        this.$router.push(this.w.url.login);
      }
    );
    // 判断是否登录 End
  }
};
</script>