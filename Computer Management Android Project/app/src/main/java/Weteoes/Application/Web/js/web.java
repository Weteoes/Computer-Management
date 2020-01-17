package Weteoes.Application.Web.js;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.webkit.JavascriptInterface;
import android.webkit.WebView;

import com.jwenfeng.library.pulltorefresh.PullToRefreshLayout;
import com.weteoes.computermanagement.dlg_web;

import org.json.JSONObject;

import Weteoes.Application.AppConfig;
import Weteoes.Model.Config.XML_EntranceClass;

public class web extends Object {
    private Activity this_; //窗口句柄
    private WebView webView; //浏览器控件
    private PullToRefreshLayout pullToRefreshLayout; //上拉下拉刷新控件

    public web(Activity this_, WebView webView,PullToRefreshLayout pullToRefreshLayout){
        this.this_ = this_;
        this.webView = webView;
        this.pullToRefreshLayout = pullToRefreshLayout;
    }

    /* Toast消息 */
    @JavascriptInterface
    public void dlg_Toast(String data) {
        Weteoes.Model.MessageClass.Toast(this_,data);
    }

    /* 登录成功后设置w */
    @JavascriptInterface
    public void login_setW(String w){
        try{
            JSONObject a = new JSONObject();
            a.put("w",w);
            if(!new XML_EntranceClass().Entrance(Weteoes.Application.AppConfig.appConfigDirectory+"/users.xml",a)){
                dlg_Toast("登录失败");
            }
        }catch (Exception error){
            error.printStackTrace();
        }
    }

    /* 上拉下拉刷新 */
    @JavascriptInterface
    public void dlg_setPullToRefreshLayout(boolean CanLoadMore,boolean CanRefresh){
        pullToRefreshLayout.setCanLoadMore(CanLoadMore);//上拉刷新
        pullToRefreshLayout.setCanRefresh(CanRefresh); //下拉刷新
    }

    /* 重新尝试打开页面（无网络 404 500时） */
    @JavascriptInterface
    public void w_reload(final String url){
        this_.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                webView.loadUrl(url);
            }
        });
    }

    /* 打开新页面 */
    @JavascriptInterface
    public void openWeb(final String url){
        this_.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                try{
                    Bundle web_bundle = new Bundle(); //传到Web窗口的参数
                    web_bundle.putString("webUrl", url);
                    /* 初始化窗口和传参 */
                    final Intent intent = new Intent(this_, dlg_web.class);
                    intent.putExtras(web_bundle);
                    this_.startActivityForResult(intent, 0);// 跳转并要求返回值，0代表请求值(可以随便写)
                } catch (Exception e){ e.printStackTrace();}
            }
        });
    }
}