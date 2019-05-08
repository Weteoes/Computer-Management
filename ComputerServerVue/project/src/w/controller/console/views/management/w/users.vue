<template>
  <div class="management_w_user">
    <div class="data">
      <el-table
        v-loading="loadingList"
        :data="wList.slice((currentPage-1)*pageSize,currentPage*pageSize)"
        style="width: 100%"
        :default-sort="{prop: 'ID', order: 'ascending'}"
      >
        <el-table-column prop="ID" label="ID" sortable></el-table-column>
        <el-table-column prop="User" label="用户名" sortable></el-table-column>
        <el-table-column prop="LoginTime" width="200" label="登录时间" :formatter="format_LoginTime" sortable></el-table-column>
        <el-table-column prop="Type" label="设备" :formatter="format_Type" sortable></el-table-column>
        <el-table-column prop="w" label="W值" width="300"></el-table-column>
        <el-table-column label="操作">
          <template slot-scope="scope">
            <el-button size="mini" type="danger" @click="handleDelete(scope.row)">删除</el-button>
          </template>
        </el-table-column>
      </el-table>
      <el-pagination class="pagination" background @current-change="pagination_next" layout="prev, pager, next" :currentPage="currentPage" :total="total*10"></el-pagination>
    </div>
  </div>
</template>

<style lang="scss" scoped>
.management_w_user {
  width: 100%;
  height: auto;
}
.data {
  width: 90%;
  height: 700px;
  margin: 30px auto;
  position: relative;
}
.data .pagination {
  position: absolute;
  bottom: 30px;
}
</style>

<script>
export default {
  data() {
    return {
      // 全局函数
      w: window.Weteoes,
      // session
      session: window.localStorage.getItem("w"),
      wList: [ ], // Data
      loadingList: true, // 正在加载表格
      currentPage: 1, // 当前页码
      total: 1, // 总条数
      pageSize: 10 // 每页的数据条数
    };
  },
  methods: {
    // ready_
    ready_: function() {
      // 获取列表
      this.readyTable();
    },
    // readyTable
    //// 获取列表
    readyTable: function() {
      // 全局变量
      let w = this.w;
      let this_ = this;
      // Ajax
      w.JS_Basic.Ajax(
        w.url.management_.w.operating_getList,
        { w: this_.session },
        function(result) {
          if(result.status != 200) { w.function.msg("获取列表失败 code:1" + 2, "error"); return; }
          let resultData = result.data;
          // -1 为未登录
          if(resultData.code == -1) { this_.$router.push(w.url.login); return; }
          if(resultData.code != 0) { w.function.msg("获取列表失败 code:2" + 2, "error"); return; }

          // 总页数
          this_.total = resultData.list.length / this_.pageSize;
          // 当前页数(如果大于总页数就设置为最后一页)
          this_.currentPage = this_.currentPage > this_.total ? this_.total : this_.currentPage;

          // List
          this_.wList = resultData.list;
          this_.loadingList = false;
        },
        function(error) {
          w.function.msg("服务器开小差啦 msg:" + error, 2, "error");
        }
      );
    },
    // readyTable End
    // ready_ End
    // handleDelete
    //// 删除按钮
    handleDelete: function(row) {
      // 全局变量
      let w = this.w;
      let this_ = this;
      // Remove ID
      let removeId = row.w;
      if(removeId == "") { w.function.msg("W值获取失败,删除失败", 2, "error"); return; }
      // Ajax
       w.JS_Basic.Ajax(
        w.url.management_.w.operating_remove,
        { w: this_.session, removeId: removeId },
        function(result) {
          if(result.status != 200) { w.function.msg("删除失败 code:1", 2, "error"); return; }
          let resultData = result.data;
          // -1 为未登录
          if(resultData.code == -1) { this_.$router.push(w.url.login); return; }
          if(resultData.code != 0) { w.function.msg("删除失败 code:2", 2, "error"); return; }
          w.function.msg("删除成功", 2, "success"); 
          // 获取列表
          this_.readyTable();
        },
        function(error) {
          w.function.msg("服务器开小差啦 msg:" + error, 2, "error");
        }
      );
    },
    // handleDelete End
    // table_LoginTime
    //// 格式化日期
    format_LoginTime: function (row) {
      let date_ = row.LoginTime + "000";
      let date = new Date(parseInt(date_));
      let result = date.format("yyyy-MM-dd HH:mm:ss");
      return result;
    },
    // table_LoginTime End
    // format_Type
    //// 格式化类型
    format_Type: function(row) {
      let result = "未知";
      switch(row.Type) {
        case "0": result = "电脑"; break;
        case "1": result = "手机"; break;
        case "2": result = "后台"; break;
      }
      return result;
    },
    // format_Type End
    // pagination_next
    pagination_next: function(page) {
      this.currentPage = page;
    }
    // pagination_next End
  },
  mounted() {
    this.ready_();
  }
};
</script>