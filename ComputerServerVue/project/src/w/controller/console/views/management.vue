<template>
  <div class="management">
    <!-- topNav -->
    <div class="topNav">
      <div class="right">
        <div class="rightData">
          <div class="only">
            <div class="icon icon_user" :title="'用户'"></div>
            <div class="title" :style="'max-width:80px;'" v-text="user.name" :title="user.name"></div>
          </div>
          <div class="only">
            <div class="icon icon_quit" id="quit" :title="'退出'" @click="topNav_quit"></div>
          </div>
        </div>
      </div>
    </div>
    <!-- topNav End -->
    <div class="data">
      <div class="leftNav">
        <el-menu
          :default-active="default_leftNav"
          class="el-menu-vertical-demo"
          background-color="#545c64"
          text-color="#fff"
          active-text-color="#ffd04b"
          @select="leftNavSelect"
          :style="'width: 100%;'"
        >
          <el-submenu index="/w">
            <template slot="title">
              <i class="el-icon-tickets"></i>
              <span>W值管理</span>
            </template>
            <el-menu-item-group>
              <el-menu-item :index="w.url.management_.users">用户列表</el-menu-item>
              <el-menu-item :index="w.url.management_.management">管理</el-menu-item>
            </el-menu-item-group>
          </el-submenu>
        </el-menu>
      </div>
      <div class="rightData">
        <router-view/>
      </div>
    </div>
  </div>
</template>

<style>
tbody tr td div {
  user-select: text;
}
</style>

<style lang="scss" scoped>
// 顶部菜单
$topNav_Height: 50px;
// 顶部菜单右菜单
$topNav_right_Height: 30px;
@mixin topNav_Background {
  background: #50575f;
}
// 左侧菜单
$leftNav_Width: 250px;
@mixin leftNav_Background {
  background: #545c64;
}
.management {
  min-width: 1200px;
  min-height: 820px;
  position: absolute;
  top: 0;
  bottom: 0;
  left: 0;
  right: 0;
}
.management .topNav {
  width: 100%;
  height: $topNav_Height;
  @include topNav_Background;
}
.management .data {
  position: absolute;
  top: $topNav_Height;
  bottom: 0;
  right: 0;
  left: 0;
}
.data .rightData {
  position: absolute;
  left: $leftNav_Width;
  right: 0;
  top: 0;
  bottom: 0;
}
.data .leftNav {
  width: $leftNav_Width;
  position: absolute;
  left: 0;
  top: 0;
  bottom: 0;
  @include leftNav_Background;
}
// topNav
.topNav .right {
  width: auto;
  height: $topNav_Height;
  float: right;
}
.topNav .right .rightData {
  width: auto;
  height: $topNav_right_Height;
  padding-top: ($topNav_Height - $topNav_right_Height) / 2;
}
.topNav .right .only {
  width: auto;
  height: $topNav_right_Height;
  margin-right: 20px;
  display: inline-block;
  vertical-align: top;
}
.topNav .right .only .icon {
  width: 30px;
  float: left;
}
.topNav .right .only .title {
  height: $topNav_right_Height;
  line-height: $topNav_right_Height;
  color: #fff;
  float: left;
  overflow: hidden;
  text-overflow: ellipsis;
}
.topNav .right .only #quit {
  cursor: pointer;
}
// topNav End
// icon
@mixin icon_Height {
  height: 100%;
}
.icon_user {
  @include icon_Height;
  background: url("/Weteoes/Console/Management/image/icon/user.png") no-repeat left /auto 80%;
}
.icon_quit {
  @include icon_Height;
  background: url("/Weteoes/Console/Management/image/icon/quit.png") no-repeat left /auto 80%;
}
// icon End
</style>
<script>
export default {
  data() {
    return {
      // 全局函数
      w: window.Weteoes,
      // session
      session: window.localStorage.getItem("w"),
      // 用户信息
      user: {
        name: ""
      },
      // 菜单位置
      default_leftNav: this.$router.history.current.path
    };
  },
  methods: {
    // ready_
    ready_: function() {
      window.a = this;
      // 保存全局变量
      let w = this.w,
        this_ = this;
      // 获取用户信息
      (()=>{
        w.JS_Basic.Ajax(
          w.url.operating_getUserInfo,
          { w: this_.session },
          function(result) {
            if(result.status != 200) { w.function.msg("服务器开小差了", 2, "error"); return; }
            let resultData = result.data;
            if(resultData.code != 0) { w.function.msg("获取用户信息失败,msg:{msg}".format({msg: resultData.msg}), 2, "error"); return; }
            // 保存用户信息
            this_.user.name = resultData.user;
          }
        );
      })();
      // 获取用户信息 End
    },
    // ready_ End
    // leftNavSelect 
    //// 左侧菜单选择
    //// function(key, keyPath)
    leftNavSelect: function(key) {
      this.leftNavClick(key);
    },
    // leftNavSelect End
    // leftNavClick
    // 左侧菜单点击事件
    leftNavClick: function(key) {
      this.default_leftNav = key;
      this.$router.push(key); 
      //if
    },
    // leftNavClick End
    // topNav_quit
    //// 退出登录
    topNav_quit: function() {
      window.localStorage.clear();
      this.$router.push(this.w.url.login);
    },
    // topNav_quit End
  },
  mounted() {
    // 判断是否登录
    this.w.function.isLogin(
      () => {
        // 登录成功
      },
      () => {
        // 登录失败
        this.$router.push(this.w.url.login);
      }
    );
    this.ready_();
    // 判断是否登录 End
  }
};
</script>
