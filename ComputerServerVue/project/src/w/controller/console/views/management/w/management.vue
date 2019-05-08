<template>
    <div class="management_w_management">
        <div class="data">
            <el-button type="danger" @click="button_removeUseless">清除无用W值</el-button>
            <el-button type="danger" @click="button_removeAll">清除所有W值</el-button>
        </div>

        <el-dialog title="提示" :visible.sync="dlg.visible" width="30%">
            <span v-text="dlg.title"></span>
            <span slot="footer" class="dialog-footer">
                <el-button @click="dlg.visible = false">取 消</el-button>
                <el-button type="primary" @click="dlg_yes">确 定</el-button>
            </span>
        </el-dialog>
    </div>
</template>


<style lang="scss" scoped>
.management_w_management {
  width: 100%;
  height: 400px;
}
.data {
  width: 90%;
  height: auto;
  margin: 50px auto;
}
</style>

<style lang="scss" scoped>

</style>

<script>
export default {
    data(){
        return {
            w: window.Weteoes,
            session: window.localStorage.getItem("w"),
            // dlg
            dlg: {
                visible: false,
                title: "确定执行该操作吗?"
            }
        };
    },
    methods:{
        // ready_
        ready_: function() {

        },
        // ready_ End
        // dlg_yes
        dlg_yes: function() {
            this.dlg.visible = false;
            this.dlg_function();
        },
        // dlg_yes End
        // dlg成功后事件
        dlg_function: function() {},
        // dlg成功后事件 End
        // 清除无用W值
        button_removeUseless: function() {
            // 全局变量
            let w = this.w,
                this_ = this;
            // 设置成功事件
            this.dlg_function = ()=>{
                w.JS_Basic.Ajax(
                    w.url.management_.w.operating_removeUseless,
                    { w: this_.session },
                    function(result) {
                        if(result.status != 200) { w.function.msg("操作失败 code:1", 2, "error"); return; }
                        let resultData = result.data;
                        // -1 为未登录
                        if(resultData.code == -1) { this_.$router.push(w.url.login); return; }
                        if(resultData.code != 0) { w.function.msg("操作失败 code:2", 2, "error"); return; }
                        w.function.msg("操作成功", 2, "success");
                    },
                    function(error) {
                        w.function.msg("服务器开小差啦 msg:"+ error, 2, "error");
                    }
                )
            }
            // 显示窗口
            this.dlg.visible = true;
        },
        // 清除无用W值 End
        // 清除所有W值
        button_removeAll: function() {
            // 全局变量
            let w = this.w,
                this_ = this;
            // 设置成功事件
            this.dlg_function = ()=>{
                w.JS_Basic.Ajax(
                    w.url.management_.w.operating_removeAll,
                    { w: this_.session },
                    function(result) {
                        if(result.status != 200) { w.function.msg("操作失败 code:1", 2, "error"); return; }
                        let resultData = result.data;
                        // -1 为未登录
                        if(resultData.code == -1) { this_.$router.push(w.url.login); return; }
                        if(resultData.code != 0) { w.function.msg("操作失败 code:2", 2, "error"); return; }
                        w.function.msg("操作成功", 2, "success");
                    },
                    function(error) {
                        w.function.msg("服务器开小差啦 msg:"+ error, 2, "error");
                    }
                )
            }
            // 显示窗口
            this.dlg.visible = true;
        },
        // 清除所有W值 End
    },
    mounted() {
        this.ready_();
    }
}
</script>
