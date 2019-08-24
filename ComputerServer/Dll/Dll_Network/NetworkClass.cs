using System.Net;
using System.IO;
using Newtonsoft.Json;
using System;

namespace Weteoes
{
    public class NetworkClass
    {
        public ResultObject request(string url) {
            try
            {
                WebRequest w1 = WebRequest.Create(url);
                w1.Credentials = CredentialCache.DefaultCredentials;
                WebResponse w2 = w1.GetResponse();
                //通过WebRequest 对象的GetResponse方法实例化一个WebResponse 对象
                Stream s1 = w2.GetResponseStream();
                //调用WebResponse 对象的GetResponseStream方法返回数据流
                StreamReader sr = new StreamReader(s1);
                string s2 = sr.ReadToEnd();
                ResultObject rb = JsonConvert.DeserializeObject<ResultObject>(s2);
                return rb;
            }
            catch(Exception error) {
                new MessageClass().writeLog("" +
                    "Error:NetworkClass::request data:" + error.Message +
                    " url:" + url
                );
                return null;
            }
        }
        public class ResultObject
        {
            public string code { get; set; }
            public string user { get; set; }
        }
    }
}
