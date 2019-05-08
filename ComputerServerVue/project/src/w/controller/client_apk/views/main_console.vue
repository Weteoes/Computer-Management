<template>
  <!-- 设置宽高 -->
  <div class="w_data" :style="'width:'+this.ready.w+'px;'+'height:'+this.ready.h+'px;'">
    <div class="w_body">
      <!-- class console 用于vue -->
      <div class="console">
        <!-- 状态栏 -->
        <div class="main_nav console_nav">
          <div class="one"></div>
          <div class="two main_nav_two">
            <div class="left main_nav_two main_nav_inline"></div>
            <div class="menu main_nav_menu main_nav_two main_nav_inline" v-on:click="callbackClick">
              <img class="main_nav_menu" src="/Weteoes/Client_apk/Main/console/image/callback.png">
            </div>
            <div class="title main_nav_two main_nav_inline">返回</div>
          </div>
        </div>
        <!-- 状态栏 End -->
        <!-- 中间图片 -->
        <!-- :style用于垂直居中 -->
        <div class="console_icon" :style="'bottom:'+features.row.length*70+'px'">
          <img class="model" v-if="model!=''" :src="get_modelUrl(model)">
          <!-- <div class='model'></div> -->
        </div>
        <!-- 中间图片 End -->
        <!-- Console -->
        <div class="console_data">
          <div class="row" v-for="(onlyRow,rowNumber) in features.row" :key="rowNumber">
            <div
              class="column"
              v-for="(onlyColumn,columnNumber) in onlyRow.column"
              :key="columnNumber"
              :data="onlyColumn.data"
              v-on:click="featuresClick(rowNumber,columnNumber)"
            >
              <span v-html="onlyColumn.title"></span>
            </div>
          </div>
        </div>
        <!-- Console End -->
      </div>
    </div>
    <div class="w_background main_background"></div>
  </div>
</template>

<!-- index.css -->
<style scoped>
.w_data {
  /* 设置不闪烁，默认不隐藏 */
  display: block;
  /* 背景颜色 */
  background: #f1f2f3;
}
.console_data {
  position: absolute;
  left: 0;
  right: 0;
  bottom: 0;
  overflow: hidden;
}
.console_data .row {
  width: 100%;
  height: 70px;
  line-height: 70px;
  background: #fff;
  display: -webkit-flex;
  display: -moz-flex;
  display: flex;
  /* display: -webkit-box;
  display: -moz-box;
  display: box; */
}
.console_data .row .column {
  width: 100%;
  text-align: center;
  -moz-box-flex: 1; /* Firefox */
  -webkit-box-flex: 1; /* Safari and Chrome */
  box-flex: 1;
  border: 1px solid #e4e4e4;
  margin: 0 -1px -1px 0;
}
.console_icon {
  position: absolute;
  top: 60px;
  bottom: 0;
  left: 0;
  right: 0;
}
.console_icon .model {
  width: 60%;
  position: absolute;
  top: 0;
  bottom: 0;
  left: 0;
  right: 0;
  margin: auto;
}
</style>

<!-- nav.css -->
<style scoped>
.console_nav {
  background: transparent;
}
.console_nav .title {
  color: #000;
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
      //Data
      model: "", //用于model图片
      // 菜单
      features: {
        row: [
          {
            column: [{ title: "Loading", data: "" }]
          }
        ]
      }
      // 菜单 End
    };
  },
  methods: {
    // ready_
    ready_: function() {
      // 全局函数
      let w = this.w;
      // 全局this
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
      // 获取控制列表
      (() => {
        let data = w.JS_Basic.GetQueryString("data");
        w.JS_Basic.Ajax(w.url.mainConsole_get, { w: this_.session, features: data }, function(
          result
        ) {
          if (result == null) {
            w.function.msg("获取控制列表失败", 2);
            return;
          }
          if (result.status != 200) {
            w.function.msg("获取控制列表失败,code -1", 2);
            return;
          }
          let resultData = result.data;
          if(resultData.code != 0) {
            w.function.msg("获取控制列表失败,功能不存在", 2);
            return;
          }
          /* Vue */
          this_.model = resultData.model;
          this_.features.row = resultData.row;
        });
      })();
      // 获取控制列表 End
    },
    // ready_ End
    // get_modelUrl
    get_modelUrl: function(data) {
      return "/Weteoes/Client_apk/Main/All/image/model/{data}_1.png".format({
        data: data
      });
    },
    // get_modelUrl End
    // 按钮点击事件
    featuresClick: function(rowNumber, columnNumber) {
      // 存储全局函数
      let w = this.w;
      // 存储全局this
      let this_ = this;
      // data
      let now = this.features.row[rowNumber].column[columnNumber];
      let data = now.data;
      let computerName = w.JS_Basic.GetQueryString("computerName");
      
      w.function.msg("Console Send Data Success \ncomputerName:{computerName}\nshell:{shell}".format({
        computerName: computerName,
        shell: data
        })
      ,1);
      w.JS_Basic.Ajax(
        w.url.operating_app_sumbit,
        { w: this_.session, computerName: computerName, shell: data },
        function(result) {
          if(result.status != 200) { w.function.msg("发送指令失败", 2); return; }
          let resultData = result.data;
          if (resultData.code != 0) { w.function.msg("发送指令失败".format({ msg: resultData.msg }), 2); return; }
          w.function.msg("发送指令成功", 1);
        }
      );
    },
    // 按钮点击事件 End
    // 返回按钮点击事件
    callbackClick: function() {
      window.history.go(-1);
    }
    // 返回按钮点击事件 End
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
