package Weteoes.Application;

import android.os.Environment;

public class AppConfig {
    public static String appConfigDirectory =  Environment.getExternalStorageDirectory() + "/Weteoes/Computer Management"; //软件配置目录


    /* Android */
    public static String js_function = "window.Weteoes.android."; //客户端调用网页位置
    /* URL */
    public static class AppUrl{
        public static String domain_Url = "https://computerVue.weteoes.cn";
        //public static String domain_Url = "http://172.16.187.82:8080";
        public static String Login_Url = domain_Url + "/client_apk/login/?";
    }
}
