(function(w){
    if(typeof w.Weteoes == "undefined") { w.Weteoes = {}; }
    w = w.Weteoes;
    // 初始化JS_Basic
    w.JS_Basic = {};
    w = w.JS_Basic;
    w.GetQueryString = getQueryString;
    w.Ajax = ajax;

    /* 获取Get参数 */
    function getQueryString(name) { 
        var reg = new RegExp("(^|&)"+ name +"=([^&]*)(&|$)");
        var r = window.location.search.substr(1).match(reg);
        if(r!=null)return  unescape(r[2]); return null;
    }

    /* Ajax */
    function ajax(url, data, success, error) {
        if(data==""||data==undefined){data={};}
        if(typeof(success)!="function"){success=function(){};}
        if(typeof(error)!="function"){error=function(){};}
        $.ajax({
            type: "post",
            url: url,
            data: data,
            success: success,
            error: error
        });
    }
})(window);