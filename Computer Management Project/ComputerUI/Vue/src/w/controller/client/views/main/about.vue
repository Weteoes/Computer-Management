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
          <span id="About_Version" v-text="v_about_version"></span>
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
  data() {
    return {
      v_w: window.Weteoes,
      v_about_version: "3.6.1987.1524" // 版本信息
    };
  },
  props: {
    props_languageConfig: Object // 语言
  },
  methods: {
    f_ready: function() {
      this.f_config().get(); // 获取配置
    },
    // f_ready End
    f_config: function() {
      let a = {};
      let Config = this.v_w.app.Main;
      a.set = (w_menu, New_Data) => {
        //修改配置
        this.v_w.function.msg("Menu:{0} Data:{1}".format(w_menu, New_Data));
        //switch (w_menu) { }
      };
      a.get = () => {
        //获取配置
        let Version = () => {
          this.v_about_version = Config.About.Get_Version();
        };
        Version();
      };
      return a;
    }
    // f_config End
  },
  mounted() {
    this.f_ready();
  }
};
</script>
