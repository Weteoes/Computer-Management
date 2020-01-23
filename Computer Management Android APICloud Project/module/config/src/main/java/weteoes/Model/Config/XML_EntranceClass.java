package weteoes.Model.Config;

import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

public class XML_EntranceClass extends XML_ConfigClass {
    /* 设置配置入口点 */
    public boolean Entrance(String file, JSONObject data){
        try{
            operating_ operating = new operating_();
            int result = operating.GetType(file);
            if(result<0) { return false; }
            switch (result){
                case 1: return new config_users().set(file, data);
            }
            return false;
        }
        catch (Exception error){
            error.printStackTrace();
        }
        return false;
    }
    /* 获取配置入口点 */
    public JSONObject Entrance(String file){
        try{
            operating_ operating = new operating_();
            int result = operating.GetType(file);
            if(result<0) { return null; }
            switch (result){
                case 1: return new config_users().get(file);
            }
            return null;
        }
        catch (Exception error){
            error.printStackTrace();
            return null;
        }
    }
    class operating_{
        class config_xml_only{
            String fileName;
            int type;
        }
        public int GetType(String file){
            try{
                List<config_xml_only> list = GetList();
                for (config_xml_only only : list) {
                    if(only.fileName.equals(file)) return only.type;
                }
                return -2;
            }
            catch (Exception error){
                error.printStackTrace();
            }
            return -1;
        }
        private List<config_xml_only> GetList(){
            List<config_xml_only> list = new ArrayList<>();
            final String appConfigDirectory = weteoes.Application.AppConfig.appConfigDirectory;
            /* 配置列表 */
            list.add(new config_xml_only(){{ fileName = appConfigDirectory + "/users.xml"; type = 1; }});
            return list;
        }
    }
}
