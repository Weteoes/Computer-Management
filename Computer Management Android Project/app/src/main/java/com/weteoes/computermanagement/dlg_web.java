package com.weteoes.computermanagement;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.webkit.ValueCallback;
import android.webkit.WebSettings;
import android.webkit.WebView;
import com.jwenfeng.library.pulltorefresh.BaseRefreshListener;
import com.jwenfeng.library.pulltorefresh.PullToRefreshLayout;

import Weteoes.Application.AppConfig;
import Weteoes.Application.DebugClass;
import Weteoes.Application.Web.Application.*;

public class dlg_web extends AppCompatActivity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dlg_web);
        loading();
    }

    @Override
    public void onBackPressed() {
        ValueCallback<String> valueCallback = new ValueCallback<String>(){
            @Override
            public void onReceiveValue(String value) {
                onBackPressed_callback(value);
            }
        };
        webview.evaluateJavascript(AppConfig.js_function + "software_onBackPressed();", valueCallback);
    }

    @Override
    public void finish() {
        webview.destroy();
        super.finish();
    }

    public void onBackPressed_callback(String value){

        switch (value){
            case "0": break;
            case "1": webview.goBack(); break;
            case "2": super.onBackPressed(); break;
            default: super.onBackPressed(); break; // 不存在改方法(其他页面)
        }
    }
    private WebView webview; //浏览器控件
    public PullToRefreshLayout pullToRefreshLayout; //上拉下拉刷新控件
    /* Init */
    private void loading(){
        loading_pullToRefreshLayout(); //先初始化上拉下拉控件,在loading_Intent -> loading_web函数需要使用全局变量
        loading_Intent();
        loading_dlg();
    }

    /* 下拉刷新 */
    private void loading_pullToRefreshLayout(){
        /* 每次调整URL将调整不可上拉下拉刷新 */
        pullToRefreshLayout = findViewById(R.id.dlg_web_pullToRefreshLayout);
        pullToRefreshLayout.setCanLoadMore(false); //默认取消上拉刷新（网页未加载出来时）
        pullToRefreshLayout.setCanRefresh(false); //默认取消下拉刷新（网页未加载出来时）
        pullToRefreshLayout.setRefreshListener(new BaseRefreshListener() {
            @Override
            public void refresh() {
                web_reload(); //浏览器刷新（调用js）
                new Handler().postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        // 结束刷新
                        pullToRefreshLayout.finishRefresh();
                    }
                }, 1000);
            }

            @Override
            public void loadMore() {
                new Handler().postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        // 结束加载更多
                        pullToRefreshLayout.finishLoadMore();
                    }
                }, 1000);
            }
        });
    }
    /* 浏览器刷新 */
    private void web_reload(){
        /* 执行刷新操作 */
        webview.evaluateJavascript(AppConfig.js_function + "finishRefresh();",null);
    }

    /* 接收上个窗口的参数 */
    private void loading_Intent(){
        Intent intent = this.getIntent();
        Bundle bundle = intent.getExtras();
        String webUrl = (String)bundle.get("webUrl");
        if(webUrl != null){ loading_web(webUrl); }
    }

    /* 初始化窗口 */
    private void loading_dlg(){
        /* 设置黑色通知栏 */
        Weteoes.Model.StatusBarUtilClass.StatusBarLightMode(this,3);
    }

    /* 初始化浏览器 */
    private void loading_web(String url){
        webview = findViewById(R.id.dlg_web_webview);
        webview.setWebChromeClient(new WebChromeClass());
        webview.setWebViewClient(new WebViewClass(pullToRefreshLayout));
        WebSettings webSettings = webview.getSettings();
        webSettings.setJavaScriptEnabled(true); //开启JavaScript
        webSettings.setDomStorageEnabled(true); //打开本地缓存提供JS调用(window.localStorage)
        if (DebugClass.isInDebug(this)) {  // Debug
            if (Build.VERSION.SDK_INT > 19) {
                webview.setWebContentsDebuggingEnabled(true);
            }
        }
//        webSettings.setCacheMode(WebSettings.LOAD_NO_CACHE); //无缓存模式
        webview.addJavascriptInterface(new Weteoes.Application.Web.js.web(this, webview, pullToRefreshLayout), "Weteoes_App");
        webview.loadUrl(url);
    }
}
