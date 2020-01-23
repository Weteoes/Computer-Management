package weteoes.Application;

import org.json.JSONObject;

import weteoes.Model.Config.XML_EntranceClass;

public class ConfigClass {

    /* 获取、设置 Session */
    public String session(String session) {
        try {
            String configFile = weteoes.Application.AppConfig.appConfigDirectory + "/users.xml";
            if (session == null || session.isEmpty()) {
                // 获取
                JSONObject result = new XML_EntranceClass().Entrance(configFile);
                if (result != null) { return (String)result.get("w"); }
                return "";
            }
            else {
                // 设置
                JSONObject a = new JSONObject();
                a.put("w", session);
                if (new XML_EntranceClass().Entrance(configFile, a)){
                    return "success";
                }
                return "";
            }
        } catch(Exception e) { return ""; }
    }
}
