(function(w){
    $(function(){
        exit();
        mini();
    });
    function exit(a){
        var jq = ".SystemMenu #exit";
        $(document).off("click",jq).on("click",jq,click);
        $(document).off("mouseenter",jq).on("mouseenter",jq,mouseenter);
        $(document).off("mouseleave",jq).on("mouseleave",jq,mouseleave);

        function mouseenter(){
            $(jq).css("background","#fb4d4d");
        }
        function mouseleave(){
            $(jq).css("background","transparent");
        }
        function click(){
            mouseleave();
            mouseleave();
            w.app.SystemMenu.Exit();
        }
    }
    function mini(a){
        var jq = ".SystemMenu #mini";
        $(document).off("click",jq).on("click",jq,click);
        $(document).off("mouseenter",jq).on("mouseenter",jq,mouseenter);
        $(document).off("mouseleave",jq).on("mouseleave",jq,mouseleave);

        function mouseenter(){
            $(jq).css("background","rgba(66, 86, 239, 0.78)");
        }
        function mouseleave(){
            $(jq).css("background","transparent");
        }
        function click(){
            mouseleave();
            mouseleave();
            w.app.SystemMenu.Mini();
        }
    }
})(typeof(window.Weteoes) == "undefined" ? $("html").html("") : window.Weteoes);