<template>
  <div class="data_all data_setting">
    <div class="data_setting_center">
      <div class="information" id="Language_Setting_Reboot" v-text="setting_Information"></div>
      <!-- 选项区域 -->
      <!-- 电脑名称 -->
      <div class="setting_edit" ref="resetting_computerName">
        <div
          class="title"
          w_menu="Computer_Name"
          id="Language_Setting_ComputerName"
          v-text="props_languageConfig.id.Language_Setting_ComputerName"
        >Computer Name:</div>
        <div class="data" v-bind:class="{no_diskplay: setting_computerName_Edit}">
          <span id="Setting_Computer_Name" v-text="setting_computerName">Computer</span>
          <div class="editButton" @click="setting_computerNameEditClick"></div>
        </div>
        <div class="edit" v-bind:class="{no_diskplay: !setting_computerName_Edit}">
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
  data () {
    return {
      w: window.weteoes,
      setting_Information: '', //  提示消息
      setting_computerName: '', // 电脑名称
      setting_computerName_Edit: false // 是否编辑电脑名称
    }
  },
  props: {
    props_languageConfig: Object // 语言
  },
  methods: {
    ready: function () {
      this.config().get() // 获取配置
    },
    // setting End
    config: function () {
      const a = {}
      a.set = (menu, NewData) => {
        // 修改配置
        this.w.function.msg('Menu:{0} Data:{1}'.format(menu, NewData))
        switch (menu) {
          case 'ComputerName': {
            this.w.softwareApi.app('Main', 'SetComputerName', { name: NewData })
            this.setting_Information = this.props_languageConfig.id.Language_Setting_Reboot
            break
          }
        }
      }
      a.get = () => {
        // 获取配置
        const ComputerName = () => {
          this.setting_computerName = this.w.softwareApi.app('Main', 'GetComputerName')
        }
        ComputerName()
      }
      return a
    },
    // config End
    setting_computerNameEditClick: function () {
      const computerNameDiv = this.$refs.resetting_computerName.querySelector(
        '#Setting_Computer_Name'
      ) // 原始内容Div
      const EditInput = this.$refs.resetting_computerName.querySelector(
        'input'
      ) // Edit Div
      const oldConputerName = computerNameDiv.innerText
      let newComputerName // 保存旧的和新的电脑名称
      const editOn = () => {
        // 开始编辑
        EditInput.value = oldConputerName // 设置编辑框内文字
        setTimeout(() => {
          EditInput.focus()
        }, 10) // 获取焦点
        document
          .querySelector('.setting_edit')
          .querySelector('input')
          .focus()
        document.onclick = editOff // 设置全局click事件
        document.onkeydown = a => {
          if (a.keyCode === 13) {
            editOff()
          }
        } // 设置全局keydown事件
        this.setting_computerName_Edit = true
      }
      const editofPD = () => {
        // 判断数据是否正确
        newComputerName = computerNameDiv.innerText.trim()
        if (newComputerName === '') {
          return false
        }
        if (oldConputerName === newComputerName) {
          return false
        }
        return true
      }
      const editOff = a => {
        // 结束编辑
        if (
          a !== undefined &&
          (a.target.className === 'editButton' || a.target.nodeName === 'INPUT')
        ) {
          return
        }
        computerNameDiv.innerText = EditInput.value // 设置编辑框内文字
        document.onclick = null // 取消全局click事件
        document.onkeydown = null // 取消全局keydown事件
        if (editofPD()) {
          // 数据正确就保存
          this.config().set('ComputerName', newComputerName)
          this.w.function.msg('修改成功', true)
        }
        this.setting_computerName_Edit = false
      }
      editOn()
    }
    // setting_computerNameEditClick End
  },
  mounted () {
    if (this.$store.state.debug) {
      window.debug = this
    }
    this.ready()
  }
}
</script>
