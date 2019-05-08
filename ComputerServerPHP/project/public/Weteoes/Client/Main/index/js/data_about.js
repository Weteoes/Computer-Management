(function(w){
    var GetConfig; //配置
    $(function(){
        GetConfig = Config();
        Menu().Get_Menu();
    });
    function Config(){
        var a = {};
        return a;
    }
    function Menu(){
        var a = {}; 
        var Config = w.app.Main.About;
        a.Get_Menu = function(){ //获取配置
            function Version(){
                if(typeof(Config.Get_Version) == "undefined") { return; }
                $("#About_Version").html(Config.Get_Version());
            }
            Version();
        }
        return a;
    }
})(typeof(window.Weteoes) == "undefined" ? $("html").html("") : window.Weteoes);