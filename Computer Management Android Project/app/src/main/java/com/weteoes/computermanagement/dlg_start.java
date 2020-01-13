package com.weteoes.computermanagement;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;

import org.json.JSONObject;

import Weteoes.Application.AppConfig;
import Weteoes.Model.Config.XML_EntranceClass;
import Weteoes.Model.PermissionsClass;

public class dlg_start extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dlg_start);
        loading();
    }
    Bundle web_bundle = new Bundle(); //传到Web窗口的参数
    private void loading(){
        loading_Permissions();
        loading_dlg();
    }
    /* 判断权限结束,允许进入后主入口 */
    private void loading_Permissions_End(){
        loading_webUrl();
        dlgWeb_Show(); //显示窗口
    }
    private void loading_dlg(){
        /* 设置黑色通知栏 */
        Weteoes.Model.StatusBarUtilClass.StatusBarLightMode(this,3);
    }
    private void dlgWeb_Show(){
        /* 线程 */
        new Thread(new Runnable() {
            @Override
            public void run() {
                try{
                    /* 初始化窗口和传参 */
                    final Intent intent = new Intent(dlg_start.this, dlg_web.class);
                    intent.putExtras(web_bundle);

                    Thread.sleep(400);
                    //启动主窗口
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            startActivityForResult(intent, 0);// 跳转并要求返回值，0代表请求值(可以随便写)
                            //startActivity(intent);
                            //结束当前的 Activity
                            dlg_start.this.finish();
                        }
                    });
                }catch (Exception error){ error.printStackTrace();}
            }
        }).start();
    }
    private void loading_webUrl(){ //获取webUrl
        String url = AppConfig.AppUrl.START_URL; //默认为登录页面
        try{
            /* 获取配置 */
            JSONObject result = new XML_EntranceClass().Entrance(Weteoes.Application.AppConfig.appConfigDirectory+"/users.xml");
            String w = (String)result.get("w");
            /* 组合 */
            url = String.format("%1$sw=%2$s", url, w);
        }catch (Exception error){ //还未登录
            error.printStackTrace();
        }
        web_bundle.putString("webUrl", url); //将变量放入
    }
    private void loading_Permissions(){ //判断权限
        if(new PermissionsClass().loading(this)) {
            loading_Permissions_End();
        }
    }
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) { //权限允许
            PermissionsClass.obtainNum++; //已获取的权限++
            if(PermissionsClass.obtainNum == PermissionsClass.permissionsList.length){
                loading_Permissions_End();
            }
        }else{ //权限拒绝
            if(ActivityCompat.shouldShowRequestPermissionRationale(this, permissions[0])){ //可以获取，没选不再提示
                loading_Permissions();
            }else{ //不能获取，选了不再提示
                this.finish();
            }
        }
    }
}
