(function(w){
    // All Language
    var en_US_Config_ = en_US_Config(),
        zh_CN_Config_ = zh_CN_Config();

    //Now Language
    var GetLanguage = en_US_Config_; //Language

    //Config
    var GetConfig = {
        LanguageTitleDiv : "#Language_Menu_Language "
    };
    $(function this_(){
        /* 如果还没加载完毕 */
        if(typeof(w.JS_Basic)=="undefined"){ setTimeout(this_,100); return; }
        /* 执行操作 */
        var Language = w.JS_Basic.GetQueryString("Language");
        if(Language == undefined) { Language = en_US_Config_.Basic.Code; }
        SetLanguage(Language);
        w.Language = {}; //设置全局Window变量
        w.Language.Set = SetLanguage; //设置全局Window变量
        w.Language.Get = GetLanguage; //设置全局Window变量
    });
    function Renew_Language(){
        var Config = GetLanguage.id;
        for(var i in Config){
            var a = $("#"+i);
            if(a.attr("w_IsNull") != undefined){ //是否可以为NULL
                if(a.html() == "" || a.html() == undefined){ //现在为NULL所以不用翻译
                    continue;
                }
            }
            a.html(Config[i]);
        }
    }
    function en_US_Config(){
        var a = {}; 
        a.Basic = {};
        a.Basic.Title = "English";
        a.Basic.Code = "en_US";
        a.id = {};
        a.id.Language_top_title_one = "Login User: ";
        a.id.Language_top_title_two = "Service connection success";
        a.id.Language_Menu_Setting = "Setting";
        a.id.Language_Menu_About = "About";
        a.id.Language_Setting_ComputerName = "Computer Name: ";
        a.id.Language_Setting_Reboot = "This operation requires restarting the software.";
        a.id.Language_About_Version = "Version: ";
        a.id.Language_About_Company = "Company: ";
        return a;
    }
    function zh_CN_Config(){
        var a = {}; 
        a.Basic = {};
        a.Basic.Title = "简体中文";
        a.Basic.Code = "zh_CN";
        a.id = {};
        a.id.Language_top_title_one = "当前用户: ";
        a.id.Language_top_title_two = "服务器连接成功";
        a.id.Language_Menu_Setting = "设置";
        a.id.Language_Menu_About = "关于";
        a.id.Language_Setting_ComputerName = "电脑名称: ";
        a.id.Language_Setting_Reboot = "该操作需要重启软件才能生效.";
        a.id.Language_About_Version = "版本: ";
        a.id.Language_About_Company = "公司: ";
        return a;
    }
    function GetLanguage(){ //获取语言
        return GetLanguage;
    }
    function SetLanguage(this_){ //设置语言
        var w_language = this_,
            display_Title; //要切换显示的Title(切换完后显示)
        if(typeof(this_.attr) != "undefined") { //如果this_是元素
            w_language = this_.attr("w_language");
            if(w_language == undefined) { console.log("w_language:"+NULL); return; }
        }
        switch(w_language){
            case zh_CN_Config_.Basic.Code:{
                GetLanguage = zh_CN_Config_; 

                //按钮修改内容(切换完后显示)
                w_language = en_US_Config_.Basic.Code; 
                display_Title = en_US_Config_.Basic.Title;
                break;
            }
            case en_US_Config_.Basic.Code:{
                GetLanguage = en_US_Config_;
                w_language = "zh_CN"; //按钮修改attr的内容

                //按钮修改内容(切换完后显示)
                w_language = zh_CN_Config_.Basic.Code; 
                display_Title = zh_CN_Config_.Basic.Title;
                break;
            }
            default:{
                GetLanguage = en_US_Config_;
                w_language = "zh_CN"; //按钮修改attr的内容

                //按钮修改内容(切换完后显示)
                w_language = zh_CN_Config_.Basic.Code; 
                display_Title = zh_CN_Config_.Basic.Title;
                break;
            }
        }
        $(GetConfig.LanguageTitleDiv).html(display_Title);
        $(GetConfig.LanguageTitleDiv).parent().attr("w_language",w_language);
        Renew_Language();
        C_Set_Language(); //保存配置
    }
    function C_Set_Language(){ //保存配置
        w.app.Main.All.Set_Language(GetLanguage.Basic.Code);
    }
})(typeof(window.Weteoes) == "undefined" ? $("html").html("") : window.Weteoes);