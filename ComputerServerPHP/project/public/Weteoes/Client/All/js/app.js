(function(w){
    if(typeof(w.Weteoes) == "undefined"){ w.Weteoes = {}; }
    if(typeof(w.Weteoes.app) == "undefined"){ w.Weteoes.app = {}; }
    var obj = w.Weteoes, obj_app = w.Weteoes.app, obj_app_ = w.Weteoes_App;

    /* SystemMenu */
    if(typeof(obj_app.SystemMenu) == "undefined"){ obj_app.SystemMenu = {}; }
    obj_app.SystemMenu.Exit = function(){
        if(typeof(obj_app_) == "object" && typeof(obj_app_.SystemMenu) == "object" && typeof(obj_app_.SystemMenu.Exit) == "function"){
            return obj_app_.SystemMenu.Exit();
        }
    };
    obj_app.SystemMenu.Mini = function(){
        if(typeof(obj_app_) == "object"  && typeof(obj_app_.SystemMenu) == "object" && typeof(obj_app_.SystemMenu.Mini) == "function"){
            return obj_app_.SystemMenu.Mini();
        }
    };

    /* Login */
    if(typeof(obj_app.Login) == "undefined"){ obj_app.Login = {}; }
    obj_app.Login.Login = function(w){
        if(typeof(obj_app_) == "object" && typeof(obj_app_.Login) == "object" && typeof(obj_app_.Login.Login) == "function"){
            return obj_app_.Login.Login(w);
        }
    };

    /* Main */
    if(typeof(obj_app.Main) == "undefined"){ obj_app.Main = {}; }

    /* Main.All */
    if(typeof(obj_app.Main.All) == "undefined"){ obj_app.Main.All = {}; }
    obj_app.Main.All.Get_w = function(){
        if(typeof(obj_app_) == "object" && typeof(obj_app_.Main) == "object" && typeof(obj_app_.Main.All) == "object" &&  typeof(obj_app_.Main.All.Get_w) == "function"){
            return obj_app_.Main.All.Get_w();
        }
    };
    obj_app.Main.All.Set_Language = function(name){
        if(typeof(obj_app_) == "object" && typeof(obj_app_.Main) == "object" && typeof(obj_app_.Main.All) == "object" &&  typeof(obj_app_.Main.All.Set_Language) == "function"){
            return obj_app_.Main.All.Set_Language(name);
        }
    };

    /* Main.Setting */
    if(typeof(obj_app.Main.Setting) == "undefined"){ obj_app.Main.Setting = {}; }
    obj_app.Main.Setting.Get_ComputerName = function(){
        if(typeof(obj_app_) == "object" && typeof(obj_app_.Main) == "object" && typeof(obj_app_.Main.Setting) == "object" &&  typeof(obj_app_.Main.Setting.Get_ComputerName) == "function"){
            return obj_app_.Main.Setting.Get_ComputerName();
        }
    };
    obj_app.Main.Setting.Set_ComputerName = function(name){
        if(typeof(obj_app_) == "object" && typeof(obj_app_.Main) == "object" && typeof(obj_app_.Main.Setting) == "object" &&  typeof(obj_app_.Main.Setting.Set_ComputerName) == "function"){
            return obj_app_.Main.Setting.Set_ComputerName(name);
        }
    };

    /* Main.About */
    if(typeof(obj_app.Main.About) == "undefined"){ obj_app.Main.About = {}; }
    obj_app.Main.About.Get_Version = function(){
        if(typeof(obj_app_) == "object" && typeof(obj_app_.Main) == "object" && typeof(obj_app_.Main.About) == "object" &&  typeof(obj_app_.Main.About.Get_Version) == "function"){
            return obj_app_.Main.About.Get_Version();
        }
    };

    /* URL */
    if(typeof(obj.url) == "undefined"){ 
        obj.url = {
            operating_sign_in: "/operating/Login/sign_in?w_Type=0", //登录接口
            operating_getUserInfo: "/operating/User/get?" //获取用户信息（也被用于判断是否登录）
        }; 
    }

    /* Language被Language.js动态添加 */
})(window);
