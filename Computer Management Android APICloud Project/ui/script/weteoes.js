(function() {
  let w = window;
  if (typeof w.Weteoes == "undefined") {
    w.Weteoes = {};
  }
  // 设置w为Weteoes变量
  w = w.Weteoes;
  // 添加通用函数
  w.JS_Basic = {};
  let w_JS_Basic = w.JS_Basic;

  // 获取URL Get参数
  w_JS_Basic.GetQueryString = name => {
    var reg = new RegExp("(^|&)" + name + "=([^&]*)(&|$)");
    var r = window.location.search.substr(1).match(reg);
    if (r != null) return unescape(decodeURI(r[2]));
    return null;
  };
  // 获取URL Get参数  End
  // Ajax
  w_JS_Basic.Ajax = (url, data, success, error) => {
    if (data == "" || data == undefined) {
      data = {};
    }
    if (typeof success != "function") {
      success = function() {};
    }
    if (typeof error != "function") {
      error = function() {};
    }
    try {
      api.ajax(
        {
          url: url,
          data: { values: data },
          method: "post"
        },
        data => {
          data = { status: 200, data: data };
          console.log(JSON.stringify(data));
          success(data);
        }
      );
    } catch (e) {
      error(e);
    }
  };
  // Ajax End
  // String.format
  //// "{a}".format({a:1})
  String.prototype.format = function(args) {
    var result = this;
    if (arguments.length > 0) {
      if (arguments.length == 1 && typeof args == "object") {
        for (var key in args) {
          if (args[key] != undefined) {
            var reg1 = new RegExp("({" + key + "})", "g");
            result = result.replace(reg1, args[key]);
          }
        }
      } else {
        for (var i = 0; i < arguments.length; i++) {
          if (arguments[i] != undefined) {
            var reg2 = new RegExp("({)" + i + "(})", "g");
            result = result.replace(reg2, arguments[i]);
          }
        }
      }
    }
    return result;
  };
  // String.format End
  // Date.format
  //// new Date().format("yyyy-MM-dd HH:mm:ss");
  Date.prototype.format = function(fmt) {
    var o = {
      "M+": this.getMonth() + 1, //月份
      "d+": this.getDate(), //日
      "H+": this.getHours(), //小时
      "m+": this.getMinutes(), //分
      "s+": this.getSeconds(), //秒
      "q+": Math.floor((this.getMonth() + 3) / 3), //季度
      S: this.getMilliseconds() //毫秒
    };
    if (/(y+)/.test(fmt))
      fmt = fmt.replace(
        RegExp.$1,
        (this.getFullYear() + "").substr(4 - RegExp.$1.length)
      );
    for (var k in o)
      if (new RegExp("(" + k + ")").test(fmt))
        fmt = fmt.replace(
          RegExp.$1,
          RegExp.$1.length == 1
            ? o[k]
            : ("00" + o[k]).substr(("" + o[k]).length)
        );
    return fmt;
  };
  // Date.format End
})();
