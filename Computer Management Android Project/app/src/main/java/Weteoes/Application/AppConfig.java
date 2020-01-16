package Weteoes.Application;

import android.os.Environment;

public class AppConfig {
    public static String appConfigDirectory =  Environment.getExternalStorageDirectory() + "/Weteoes/Computer Management"; //软件配置目录
    /* Android */
    public static String js_function = "window.Weteoes.android."; //客户端调用网页位置
    /* URL */
    public static class AppUrl{
        public static String START_URL = "file:///android_asset/ui/html/client/appMain/index.html?";
        public static String ERROR_URL = "file:///android_asset/error/index.html?";
        //public static String START_URL = "https://computerVue.weteoes.cn/client_apk/login/?";
    }
}
