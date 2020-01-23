package com.weteoes.computermanagement.apicloud.module.config;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;

import com.uzmap.pkg.uzcore.UZWebView;
import com.uzmap.pkg.uzcore.uzmodule.UZModule;
import com.uzmap.pkg.uzcore.uzmodule.UZModuleContext;

import org.json.JSONException;
import org.json.JSONObject;

import weteoes.Application.ConfigClass;

/**
 * 该类映射至Javascript中moduleDemo对象<br><br>
 * <strong>Js Example:</strong><br>
 * var module = api.require('moduleDemo');<br>
 * module.xxx();
 * @author APICloud
 *
 */
public class main extends UZModule {

	public main(UZWebView webView) { super(webView); }

	public void jsmethod_w(UZModuleContext moduleContext) {
		try {
			String w = moduleContext.optString("w");
			String session = new ConfigClass().session(w);
			if (session == "") { moduleContext.error(null); return; } //如果返回""则错误
			// 初始化返回JSON
			JSONObject result = new JSONObject();
			result.put("w", session);
			moduleContext.success(result);
		} catch (Exception e) {
			moduleContext.error(null);
		}
	}
}
