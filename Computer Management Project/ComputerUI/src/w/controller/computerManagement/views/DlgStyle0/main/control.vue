<template>
  <div class="data_all data_control">
    <div class="data_control_center" v-loading>
      <div class="clientList">
        <div v-if="controlList != 0 && controlList.length > 0">
          <div class="title" v-text="props_languageConfig.id.Language_Control_Title"></div>
          <div
            class="data_control_Client"
            v-for="(control, id) in controlList"
            v-bind:key="id"
            @click="ClientClick(control)"
          >
            <div class="clientPNG">
              <img src="/Weteoes/Client/Main/index/image/control.png" />
            </div>
            <div class="clientTitle" v-bind:title="control" v-text="control"></div>
          </div>
        </div>
        <div class="noClientList" v-else-if="controlList.length == 0">
          <img src="/Weteoes/Client/Main/control/TAT.png" />
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
        img {
          width: 100px;
          margin-top: 50px;
        }
      }
    }
  }
}
.clientList {
  $clientHeight: 100px;
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
      $clientPngHeight: 60px;
      width: 100%;
      height: $clientPngHeight;
      img {
        $vimgHeight: 40px;
        height: $vimgHeight;
        margin: {
          top: ($clientPngHeight - $vimgHeight) / 2;
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
export default {
  data () {
    return {
      w: window.weteoes,
      controlList: 0 // 电脑控制列表
    }
  },
  props: {
    props_languageConfig: Object // 语言
  },
  methods: {
    ready: function () {
      this.getControlList() // 获取电脑控制列表
    },
    // ready End
    getControlList: function () {
      const w = this.w
      const session = this.config().get().getSession()
      w.basic.ajax(
        w.url.operating_getControlList,
        'post',
        { w: session },
        result => {
          if (result.status !== 200) {
            // loading_Stop();
            this.msg('服务器开小差了', true, 'error')
            return
          }
          const resultData = result.data
          if (resultData.code !== 0) {
            // loading_Stop();
            this.msg('服务器开小差了', true, 'error')
            return
          } // 设置用户
          const controlList = []
          const nowComputerName = this.w.softwareApi.app('Main', 'GetComputerName')
          for (const i of resultData.computer) {
            if (i.name === nowComputerName) {
              continue
            } // 跳过自己
            controlList.push(i.name)
          }
          this.controlList = controlList // 设置列表
          // loading_Stop();
        }
      )
    },
    msg: function (title, client, type) {
      this.w.function.msg(title, client, type)
    },
    // (服务器错误)error End
    // getControlList End
    ClientClick: function (computerName) {
      const session = this.config()
        .get()
        .getSession()
      const w = this.w
      w.basic.ajax(
        w.url.operating_app_sumbit,
        'post',
        { w: session, computerName: computerName, shell: 'vceeDI' },
        result => {
          if (result.status !== 200) {
            this.msg('服务器开小差了', true, 'error')
            return
          }
          const resultData = result.data
          if (resultData.code !== 0) {
            this.msg('服务器开小差了', true, 'error')
            return
          }
          this.msg('操作成功', true, 'success')
          this.w.softwareApi.app('Main', 'ControlComputer', { computerName: computerName })
        }
      )
    },
    // ClientClick  End
    config: function () {
      const a = {}
      a.get = () => {
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
  }
}
</script>
