(function(w){
    var GetConfig; //配置
    $(function(){
        GetConfig = Config();
        Menu().Get_Menu(); //获取配置
        data_setting_edit();
    });
    function Config(){
        var a = {};
        a.body = ".data_setting_center ";
        a.onDiv = "html"; //绑定元素父Div
        return a;
    }
    function data_setting_edit(){
        var Edit_Button = GetConfig.body+".setting_edit .editButton"; //Edit Button
        $(document).off("click",Edit_Button).on("click",Edit_Button,click); //ID:1
        function click(a){
            var this_ = $(a.currentTarget),  //Edit图标(绑定事件的元素)
                Title_Div = this_.parent().parent().children(".title"), //Title Div
                Data_Div = this_.parent(), //Data Div
                Edit_Data_Div = this_.parent().children("span"), //原始内容Div
                Edit_Div = this_.parent().parent().children(".edit"), //Edit 主Div
                Input_Div = Edit_Div.find("input"); //Input Div
            function edit_on(){ //开始编辑
                function KeyDown(a){
                    if(a.keyCode == 13){ //Enter
                        var this_ = $(a.currentTarget); //元素
                        this_.off("keydown");
                        edit_off();
                    }
                }
                Data_Div.css("display","none");
                Edit_Div.css("display","inline-block");
                Input_Div.val(Edit_Data_Div.html()); //Data
                Input_Div.focus(); //焦点
                Input_Div.on("keydown",KeyDown);
            }
            function edit_off(a){ //编辑结束
                if(a != undefined){ //如果是点击任意处后进入函数的
                    var this_ = a.target; //(触发事件的元素)
                    if(this_.localName == "input"){ //如果是Input
                        return;
                    }
                }
                var Old_Data, New_Data;
                function PD_Data(){ //判断Data
                    Old_Data = Edit_Data_Div.html();
                    New_Data = Input_Div.val();
                    if(New_Data == ""){
                        return false;
                    }
                    if(Old_Data == New_Data){
                        return false;
                    }
                    return true;
                }
                Data_Div.css("display","inline-block");
                Edit_Div.css("display","none"); //Edit Div
                if(PD_Data()){
                    Edit_Data_Div.html(New_Data);
                    var w_menu = Title_Div.attr("w_menu");
                    if(w_menu != undefined){
                        Menu().Set_Menu(w_menu,New_Data);
                        console.log("w_menu:",w_menu," New_Data:",New_Data);
                    }
                }
                $(document).off("click",GetConfig.onDiv); //ID:0
                $(document).off("click",Edit_Button).on("click",Edit_Button,click); //ID:1
            }
            edit_on();
            $(document).on("click",GetConfig.onDiv,edit_off); //ID:0 任意处取消编辑状态
            $(document).off("click",Edit_Button); //ID:1
        }
    }
    function Menu(){
        var a = {}; 
        var Config = w.app.Main.Setting;
        a.Set_Menu = function(w_menu,New_Data){ //修改配置
            switch(w_menu){
                case "Computer_Name":{
                    Config.Set_ComputerName(New_Data);
                    Add_Reboot_Information(); //添加消息
                    break;
                }
            }
        }
        a.Get_Menu = function(){ //获取配置
            function Computer_Name(){
                $("#Setting_Computer_Name").html(Config.Get_ComputerName());
            }
            Computer_Name();
        }
        return a;
    }
    function Add_Reboot_Information(){
        if(typeof(w.Language) == "undefined" || typeof(w.Language.Get) == "undefined" ){ return; }
        var Language = w.Language.Get;
        if(typeof(Language) == "undefined" || typeof(Language.id) == "undefined" || typeof(Language.id.Language_Setting_Reboot) == "undefined" ) { return; }
        $(GetConfig.body + ".Reboot_Information").html(Language.id.Language_Setting_Reboot);
    }
})(typeof(window.Weteoes) == "undefined" ? $("html").html("") : window.Weteoes);