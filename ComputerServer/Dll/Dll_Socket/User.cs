using System;
namespace Weteoes
{
    class UserClass {
        public bool Sign_in(ref string data) { //ToKen(身份)验证
            /* AppConfig */
            AppConfigClass AppConfig = new AppConfigClass();
            string session = AppConfig.GetConfig(ref data, "|");
            string user;
            if (!Sign_in_w(session, out user)) { return false; }
            data = user + "_" + data;
            return true;
        }
        public bool Sign_in_w(string w, out string user) {
            user = "";
            if (w == "") { return false; }
            NetworkClass.ResultObject resultObject = new Weteoes.NetworkClass().request(string.Format(ConfigClass.URL_up, w));
            if (resultObject.code == "0") { //Success
                user = resultObject.user;
                return true;
            }
            return false;
        }
    }
}