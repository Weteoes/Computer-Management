(function(w){
    var GetConfig; //配置
    $(function(){
        GetConfig = Config();
        AppMenu();
    });
    function Config(){
        var a = {};
        a.body = ".AppMenu "; //主Div
        a.menu_now = "menu_now"; //按钮按下class
        a.menu_ = "menu_"; //其他按钮class(没按下)
        a.data_all = ".data_all"; //所有设置页面的class
        return a;
    }
    function AppMenu(){
        function menu_(a){ //按钮(排除已按下的)
            var this_ = $(a.currentTarget);
            function Css(){ //修改CSS样式
                $(GetConfig.body + "." + GetConfig.menu_now).removeClass(GetConfig.menu_now).addClass(GetConfig.menu_);
                this_.removeClass(GetConfig.menu_).addClass(GetConfig.menu_now);
            }
            function Html(){ //设置页面
                var w_div = this_.attr("w_div");
                if(w_div == undefined) { return false; }
                if(w_div == "data_language"){ //如果是语言切换
                    w.Language.Set(this_);
                    return false;
                }
                $(GetConfig.data_all).css("display","none");
                $("."+w_div).css("display","block");
                return true;
            }
            if(Html()) { Css(); }
        }
        var TEMP = GetConfig.body + ".menu_";
        $(document).off("click",TEMP).on("click",TEMP,menu_);
    }
   
})(typeof(window.Weteoes) == "undefined" ? $("html").html("") : window.Weteoes);