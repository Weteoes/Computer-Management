package Weteoes.Application.Web.Application;

import android.webkit.WebResourceError;
import android.webkit.WebResourceRequest;
import android.webkit.WebResourceResponse;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import com.jwenfeng.library.pulltorefresh.PullToRefreshLayout;

public class WebViewClass extends WebViewClient {
    public static PullToRefreshLayout pullToRefreshLayout; //上拉下拉刷新控件

    public WebViewClass(PullToRefreshLayout pullToRefreshLayout) {
        this.pullToRefreshLayout = pullToRefreshLayout;
    }
    /* URL跳转 */
    @Override
    public boolean shouldOverrideUrlLoading(WebView view, WebResourceRequest request) {
        pullToRefreshLayout.setCanLoadMore(false); //取消上拉刷新
        pullToRefreshLayout.setCanRefresh(false); //取消下拉刷新
        return false;
    }

    /* 404 500 */
    @Override
    public void onReceivedHttpError(WebView view, WebResourceRequest request, WebResourceResponse errorResponse) {
//        super.onReceivedHttpError(view, request, errorResponse);
//        int statusCode = errorResponse.getStatusCode();
//        if (404 == statusCode || 500 == statusCode) {
//            view.loadUrl("file:///android_asset/web/error.html?url="+view.getUrl()); // 避免出现默认的错误界面
//        }
    }

    /* 无网络 */
    @Override
    public void onReceivedError(WebView view, WebResourceRequest request, WebResourceError error) {
//        super.onReceivedError(view, request, error);
//        if (request.isForMainFrame()) { // 或者： if(request.getUrl().toString() .equals(getUrl()))
//            // 在这里显示自定义错误页
//            view.loadUrl("file:///android_asset/web/error.html?url="+view.getUrl()); // 避免出现默认的错误界面
//        }
    }
}
