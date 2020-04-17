<template>
  <div class="data_all data_about">
    <div class="data_about_center">
      <div class="about_text">
        <div
          class="title"
          id="Language_About_Version"
          v-text="props_languageConfig.id.Language_About_Version"
        >Version:</div>
        <div class="data">
          <span id="About_Version" v-text="about_version"></span>
        </div>
      </div>
      <div class="about_text">
        <div
          class="title"
          id="Language_About_Company"
          v-text="props_languageConfig.id.Language_About_Company"
        >Company:</div>
        <div class="data">
          <span>Weteoes</span>
        </div>
      </div>
      <div class="about_end">Weteoes.All Rights Reserved</div>
    </div>
  </div>
</template>

<style scoped>
.main_body_data .data_about {
  position: absolute;
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
}
.data_about .data_about_center {
  width: 700px;
  height: auto;
  min-height: 40px;
  margin: 40px auto;
}
.data_about_center .about_text {
  width: 100%;
  height: 30px;
}
.about_text .title {
  width: auto;
  height: 30px;
  font-size: 17px;
  line-height: 30px;
  color: #000;
  display: inline-block;
  vertical-align: top;
  margin: 0 10px 0 0;
}
.about_text .data {
  width: auto;
  height: 30px;
  font-size: 17px;
  line-height: 30px;
  color: #000;
  display: inline-block;
  vertical-align: top;
}
.about_end {
  width: 100%;
  height: 30px;
  line-height: 30px;
  font-size: 15px;
  text-align: center;
  position: absolute;
  right: 0;
  bottom: 0;
  left: 0;
}
</style>

<script>
export default {
  data () {
    return {
      w: window.weteoes,
      about_version: '3.6.1987.1524' // 版本信息
    }
  },
  props: {
    props_languageConfig: Object // 语言
  },
  methods: {
    ready: function () {
      this.config().get() // 获取配置
    },
    // ready End
    config: function () {
      const a = {}
      a.set = (menu, NewData) => {
        // 修改配置
        this.w.function.msg('Menu:{0} Data:{1}'.format(menu, NewData))
        // switch (w_menu) { }
      }
      a.get = () => {
        // 获取配置
        const Version = () => {
          this.about_version = this.w.softwareApi.app('Main', 'GetVersion')
        }
        Version()
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
