package Weteoes.Model.Config;

import org.json.JSONObject;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;

import java.io.ByteArrayOutputStream;
import java.io.File;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import Weteoes.Model.FilesClass;
import Weteoes.Model.XmlClass;

public class XML_ConfigClass {
    /* 配置 */
    String element_Main = "Weteoes"; //main节点
    private String getXmlString(Document document){
        try{
            TransformerFactory tf   =   TransformerFactory.newInstance();
            Transformer t = tf.newTransformer();
            t.setOutputProperty("encoding","GB23121");//解决中文问题，试过用GBK不行
            ByteArrayOutputStream bos   =   new   ByteArrayOutputStream();
            t.transform(new DOMSource(document), new StreamResult(bos));
            String xmlStr = bos.toString();
            return xmlStr;
        }catch (Exception error){
            error.printStackTrace();
            return null;
        }
    }
    private Document getXMLDocument(String file, boolean create){
        try{
            Weteoes.Model.FilesClass filesClass = new FilesClass();
            XmlClass xmlClass = new XmlClass();
            String data = filesClass.read(file);
            if(data == null){
                if(create){  return xmlClass.GetNewDocument(); } //如果文件不存在就创建
                return null;
            }
            data = new InitializationClass().rsa_Code(data,2); //数据解密
            Document document = xmlClass.read(data);
            return document;
        }catch (Exception error){
            error.printStackTrace();
            return null;
        }
    }
    private void saveXML(String file, String data){
        data = new InitializationClass().rsa_Code(data,1); //数据加密
        Weteoes.Model.FilesClass filesClass = new FilesClass();
        filesClass.write(file, data);
    }
    /* users.xml */
    class config_users{
        /* Set */
        public boolean set(String file, JSONObject data){
            try{
                File file_e = new File(file);
                if(file_e.exists()){ file_e.delete(); } //如果存在就删除旧的
                Document document = getXMLDocument(file,true); //读取，不存在就创建
                if(document == null){ return false; }

                /* Main */
                Element main = document.createElement(element_Main);

                /* Users */
                Element users_e = document.createElement("users");
                users_e.setAttribute("w",(String)data.get("w"));
                main.appendChild(users_e);

                /* Save */
                document.appendChild(main);
                saveXML(file,getXmlString(document));
                return true;
            }catch (Exception error){
                error.printStackTrace();
                return false;
            }
        }
        /* Get */
        public JSONObject get(String file){
            try{
                JSONObject result = new JSONObject(); //result
                Document document = getXMLDocument(file,false); //读取，不存在不创建
                if(document == null){ return null; }

                /* Main */
                Element main = (Element)document.getElementsByTagName(element_Main).item(0);
                if(main == null){ return null; }

                /* Users */
                Node users_e = main.getElementsByTagName("users").item(0);
                if(users_e == null){ return null; }
                NamedNodeMap users_b = users_e.getAttributes();
                result.put("w", users_b.getNamedItem("w").getNodeValue());

                /* Result */
                return result;
            }catch (Exception error){
                error.printStackTrace();
                return null;
            }
        }
    }
}