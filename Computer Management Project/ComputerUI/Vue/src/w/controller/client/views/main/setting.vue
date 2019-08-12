<template>
  <div class="data_all data_setting">
    <div class="data_setting_center">
      <div class="information" id="Language_Setting_Reboot" v-text="v_setting_Information"></div>
      <!-- 选项区域 -->
      <!-- 电脑名称 -->
      <div class="setting_edit" ref="ref_setting_computerName">
        <div
          class="title"
          w_menu="Computer_Name"
          id="Language_Setting_ComputerName"
          v-text="props_languageConfig.id.Language_Setting_ComputerName"
        >Computer Name:</div>
        <div class="data" v-bind:class="{no_diskplay: v_setting_computerName_Edit}">
          <span id="Setting_Computer_Name" v-text="v_setting_computerName">Computer</span>
          <div class="editButton" @click="f_setting_computerNameEditClick"></div>
        </div>
        <div class="edit" v-bind:class="{no_diskplay: !v_setting_computerName_Edit}">
          <input type="text" spellcheck="false" maxlength="20" val="Computer" />
        </div>
      </div>
      <!-- 选项区域 End -->
    </div>
  </div>
</template>

<style scoped>
.main_body_data .data_setting {
  width: 100%;
  height: auto;
}
.data_setting .data_setting_center {
  width: 700px;
  height: auto;
  min-height: 40px;
  margin: 10px auto;
}
.data_setting_center .setting_edit {
  width: 100%;
  height: 30px;
}
.setting_edit .title {
  width: auto;
  height: 30px;
  margin: 0 10px 0 0;
  font-size: 17px;
  line-height: 30px;
  color: #000;
  display: inline-block;
  vertical-align: top;
}
.setting_edit .data {
  width: auto;
  height: 30px;
  font-size: 17px;
  line-height: 30px;
  color: #000;
  display: inline-block;
  vertical-align: top;
}
.setting_edit .editButton {
  width: 30px;
  height: 30px;
  background: url("/Weteoes/Client/Main/index/image/edit.png") 7px 7px no-repeat;
  background-size: 60% 60%;
  cursor: pointer;
  display: inline-block;
  vertical-align: top;
}
.setting_edit .edit {
  min-width: 100px;
  height: 30px;
  display: inline-block;
  vertical-align: top;
}
.setting_edit .edit input {
  width: 200px;
  height: 30px;
  line-height: 30px;
  font-size: 17px;
  outline: none;
  border: none;
  border-bottom: 1px solid #000;
}
.data_setting_center .information {
  width: 100%;
  height: 30px;
  line-height: 30px;
  color: #f31b1b;
  font-size: 16px;
  font-weight: bold;
}
.setting_edit .no_diskplay {
  display: none;
}
</style>

<script>
export default {
  data() {
    return {
      v_w: window.Weteoes,
      v_setting_Information: "", //  提示消息
      v_setting_computerName: "", // 电脑名称
      v_setting_computerName_Edit: false // 是否编辑电脑名称
    };
  },
  props: {
    props_languageConfig: Object // 语言
  },
  methods: {
    f_ready: function() {
      this.f_config().get(); // 获取配置
    },
    // f_setting End
    f_config: function() {
      let a = {};
      let Config = this.v_w.app.Main;
      a.set = (w_menu, New_Data) => {
        //修改配置
        this.v_w.function.msg("Menu:{0} Data:{1}".format(w_menu, New_Data));
        switch (w_menu) {
          case "ComputerName": {
            Config.Setting.Set_ComputerName(New_Data);
            this.v_setting_Information = this.props_languageConfig.id.Language_Setting_Reboot;
            break;
          }
        }
      };
      a.get = () => {
        //获取配置
        let Computer_Name = () => {
          this.v_setting_computerName = Config.Setting.Get_ComputerName();
        };
        Computer_Name();
      };
      return a;
    },
    // f_config End
    f_setting_computerNameEditClick: function() {
      let computerName_Div = this.$refs.ref_setting_computerName.querySelector(
        "#Setting_Computer_Name"
      ); // 原始内容Div
      let EditInput = this.$refs.ref_setting_computerName.querySelector(
        "input"
      ); // Edit Div
      let oldConputerName = computerName_Div.innerText,
        newComputerName; // 保存旧的和新的电脑名称
      let edit_on = () => {
        // 开始编辑
        EditInput.value = oldConputerName; // 设置编辑框内文字
        setTimeout(() => {
          EditInput.focus();
        }, 10); // 获取焦点
        document
          .querySelector(".setting_edit")
          .querySelector("input")
          .focus();
        document.onclick = edit_off; // 设置全局click事件
        document.onkeydown = a => {
          if (a.keyCode == 13) {
            edit_off();
          }
        }; // 设置全局keydown事件
        this.v_setting_computerName_Edit = true;
      };
      let edit_off_PD = () => {
        // 判断数据是否正确
        newComputerName = computerName_Div.innerText.trim();
        if (newComputerName == "") {
          return false;
        }
        if (oldConputerName == newComputerName) {
          return false;
        }
        return true;
      };
      let edit_off = a => {
        // 结束编辑
        if (
          a != undefined &&
          (a.target.className == "editButton" || a.target.nodeName == "INPUT")
        ) {
          return;
        }
        computerName_Div.innerText = EditInput.value; // 设置编辑框内文字
        document.onclick = null; // 取消全局click事件
        document.onkeydown = null; // 取消全局keydown事件
        if (edit_off_PD()) {
          // 数据正确就保存
          this.f_config().set("ComputerName", newComputerName);
          this.v_w.function.msg("修改成功", true);
        }
        this.v_setting_computerName_Edit = false;
      };
      edit_on();
    }
    // f_setting_computerNameEditClick End
  },
  mounted() {
    this.f_ready();
  }
};
</script>
