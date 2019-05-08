(function(w){
    var GetConfig; //配置
    $(function(){
        GetConfig = Config();
        Menu().Get_Menu(); //获取配置
    });
    function Config(){
        var a = {};
        return a;
    }
    function Menu(){
        var a = {}; 
        var Config = w.app.Main.All;
        a.Get_Menu = function(){ //获取配置
            let session = Config.Get_w();
            // 获取用户名
            (()=>{
                w.JS_Basic.Ajax(
                    w.url.operating_getUserInfo,
                    { w: session },
                    function(a){
                        if(a.code == 0){ //success
                            $("#User").html(a.user);
                        }
                    }
                );
            })();
        }
        return a;
    }
})(typeof(window.Weteoes) == "undefined" ? $("html").html("") : window.Weteoes);