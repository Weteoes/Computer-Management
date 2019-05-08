(function(w){
    $(function(){
        login();
    });
    function login(){
        var user = $("#User"),
            password= $("#Password");
        function click(a){
            if(typeof(a.type) != "undefined"){
                a = a.target;
            }
            initialization();
            if(!PD()){ return; }
            Sign_in(a);
        }
        function Sign_in(a){ //提交
            function error(text){ //统一错误
                $(a).parent().children(".error").html(text);
            }
            function Finished(success = false){ //是否登录成功
                if(success){
                    user.val("");
                }
                password.val("");
            }
            var data = {
                "user":user.val(),
                "pass":password.val()
            };
            w.JS_Basic.Ajax(
                w.url.operating_sign_in,
                data,
                function(a){
                    if(a.code == 0){ //success
                        w.app.Login.Login(a.w);
                        Finished(true);
                    }else{
                        error("Username or Password Error");
                        Finished();
                    }
                },
                function(){
                    error("Login Sign_in Error");
                    Finished();
                }
            );
        }
        function PD(){ //本地判断
            var result = true;
            if(user.val() == ""){
                user.parent().children(".error").css("display","block");
                result = false;
            }
            if(password.val() == ""){
                password.parent().children(".error").css("display","block");
                result = false;
            }
            return result;
        }
        function initialization(){ 
            $(".login_body_center div .error").css("display","none"); //清除用户区域error
            $(".login_body_center").children(".error").html(""); //清除提示信息error
        }
        function keydown(a){
            if(a.keyCode == 13){
                click($("#login"));
            }
        }
        $(document).off("click","#login").on("click","#login",click);
        $(document).off("keydown",".login").on("keydown",".login",keydown);
    }
   
})(typeof(window.Weteoes) == "undefined" ? $("html").html("") : window.Weteoes);