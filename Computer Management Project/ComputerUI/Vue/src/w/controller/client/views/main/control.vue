<template>
  <div class="data_all data_control">
    <div class="data_control_center" v-loading>
      <div class="clientList">
        <div v-if="v_controlList != 0 && v_controlList.length > 0">
          <div class="title" v-text="props_languageConfig.id.Language_Control_Title"></div>
          <div
            class="data_control_Client"
            v-for="(v_control, v_id) in v_controlList"
            v-bind:key="v_id"
            @click="f_ClientClick(v_control)"
          >
            <div class="clientPNG">
              <img src="/Weteoes/Client/Main/index/image/control.png" />
            </div>
            <div class="clientTitle" v-bind:title="v_control" v-text="v_control"></div>
          </div>
        </div>
        <div class="noClientList" v-else-if="v_controlList.length == 0">
          <img  src="/Weteoes/Client/Main/control/TAT.png"/>
        </div>
      </div>
    </div>
  </div>
</template>

<!-- data_control -->
<style lang="scss" scoped>
$data_control_Client_Width: 100px;
.main_body_data .data_control {
  width: 100%;
  height: auto;
  .data_control_center {
    width: ($data_control_Client_Width + 20px + 2px) * 6;
    height: auto;
    min-height: 40px;
    margin: 20px auto;
    .title {
      width: 100%;
      height: auto;
      padding-left: 10px;
    }
    .clientList {
      width: 100%;
      height: auto;
      .noClientList {
        text-align: center;
        img { width:100px; margin-top: 50px; }
      }
    }
  }
}
.clientList {
  $v_clientHeight: 100px;
  .data_control_Client {
    width: $data_control_Client_Width;
    height: auto;
    border: 1px solid #000;
    border-radius: 10px;
    cursor: pointer;
    text-align: center;
    display: inline-block;
    margin: 10px 10px 10px 10px;
    .clientPNG {
      $v_clientPngHeight: 60px;
      width: 100%;
      height: $v_clientPngHeight;
      img {
        $vv_imgHeight: 40px;
        height: $vv_imgHeight;
        margin: {
          top: ($v_clientPngHeight - $vv_imgHeight) / 2;
        }
      }
    }
    .clientTitle {
      width: 100%;
      height: 26px;
      line-height: 16px;
      font-size: 15px;
      overflow: hidden;
      text-overflow: ellipsis;
    }
  }
}
</style>

<script>
import { setTimeout } from 'timers';
export default {
  data() {
    return {
      v_w: window.Weteoes,
      v_controlList: 0, // 电脑控制列表
    };
  },
  props: {
    props_languageConfig: Object // 语言
  },
  methods: {
    f_ready: function() {
      this.v_w.function.msg("该功能还在开发中，请耐心等待...", true, "");
      this.f_getControlList(); // 获取电脑控制列表
    },
    // f_ready End
    f_getControlList: function() {
      let w = this.v_w;
      //// loading
      // let loading;
      // let loading_Stop = () => { loading.close(); }
      // let loading_Start = () => {
      //   loading = this.$loading({ lock: true, text: 'Loading', background: 'rgba(0, 0, 0, 0.7)'});
      //   setTimeout(loading_Stop, 600);
      // }
      // loading_Start();
      //// Ajax
      let session = "bj1cv6gaeh8ttgusr7gvq0t4j2"; //this.f_config().get().getSession();
      w.JS_Basic.Ajax(
        w.url.operating_getControlList,
        { w: session },
        result => {
          if (result.status != 200) {
            loading_Stop();
            this.f_msg("服务器开小差了", true, "error");
            return;
          }
          let resultData = result.data;
          if (resultData.code != 0) {
            loading_Stop();
            this.f_msg("服务器开小差了", true, "error");
            return;
          } // 设置用户
          let controlList = [];
          let nowComputerName = w.app.Main.Setting.Get_ComputerName();
          for (let i of resultData.computer) {
            if(i.name === nowComputerName) { continue; } // 跳过自己
            controlList.push(i.name);
          }
          this.v_controlList = controlList; // 设置列表
          loading_Stop();
        }
      );
    },
    f_msg: function(title, client, type) {
      this.v_w.function.msg(title, client, type);
    },
    // (服务器错误)f_error End
    // f_getControlList End
    f_ClientClick: function(v_control) {
      let session = this.f_config().get().getSession();
      let w = this.v_w;
      w.JS_Basic.Ajax(
        w.url.operating_app_sumbit,
        { w: session, computerName: v_control, shell: "vceeDI" },
        result => {
          if (result.status != 200) { this.f_msg("服务器开小差了", true, "error"); return; }
          let resultData = result.data;
          if (resultData.code != 0) { this.f_msg("服务器开小差了", true, "error"); return; }
          this.f_msg("操作成功", true, "success");
        }
      )
    },
    // f_ClientClick  End
    f_config: function() {
      let a = {};
      let Config = this.v_w.app.Main;
      a.get = () => {
        let result = {};
        result.getSession = () => {
          return Config.All.Get_w();
        };
        return result;
      };
      return a;
    }
    // f_config End
  },
  mounted() {
    window.a=this;
    this.f_ready();
  }
};
</script>