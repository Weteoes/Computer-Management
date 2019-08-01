using Newtonsoft.Json;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;

namespace Weteoes
{
    class WebClass
    {
        private string parameter; //参数
        private Socket socket;

        /* 如果返回true则不断开socket连接 */
        public bool entrance(string data, ref Socket socket) {
            try
            {
                //全局变量
                this.socket = socket;

                //处理字符串
                int a = data.IndexOf("/");
                data = data.Substring(a, data.IndexOf("HTTP/") - a); //All url
                string url = data.Substring(0, data.IndexOf("?")); //url
                parameter = data.Substring(url.Length+1).TrimEnd(); //全局变量 参数

                //执行
                return function(getFunction(url));
            }
            catch { return false; }
        }
        private int getFunction(string data) {
            switch (data) {
                case "/operating/entrance":
                    return 1;
                case "/get/computerlist":
                    return 2;
                default:
                    return -1;
            }
        }

        /* 如果返回true则不断开socket连接 */
        private bool function(int i) {
            switch (i) {
                case 1:
                    new BasicMainClass().socketEntrance(parameter, ref socket);
                    return false;
                case 2:
                    string a = get_computerlist(parameter);
                    sendHttp(a);
                    return true;
                default:
                    return false;
            }
        }
        private string get_computerlist(string user) {
            string result_s = "{}";
            new ServerClass().removeFailList(); //清除已下线客户端
            List<ServerClass.serverUser> all = ServerClass.allServerList;
            foreach (ServerClass.serverUser only in all) {
                //检测用户
                if (only.user != user) { continue; }

                List<ServerClass.serverComputer> all_computer = only.server; //循环列表
                List<object> result_all = new List<object>(); //需要返回的列表

                //循环获取在线数量
                for (int i = all_computer.Count - 1; i >= 0 ; i--) {
                    ServerClass.serverComputer only_computer = all_computer[i];
                    object result_a = new { computer = only_computer.name };
                    result_all.Add(result_a);
                }

                /* 设置result */
                if (result_all.Count > 0) {
                    object result_o = new { user = result_all };
                    result_s = JsonConvert.SerializeObject(result_o).ToString();
                }
            }
            return result_s;
        }
        private void sendHttp(string data) {
            byte[] content_to_bytes = Encoding.Default.GetBytes(data);
            string statusline = "HTTP/1.1 200 OK\r\n";   //状态行
            byte[] statusline_to_bytes = Encoding.Default.GetBytes(statusline);
            string header = string.Format("Content-Type:text/html;charset=UTF-8\r\nContent-Length:{0}\r\n", content_to_bytes.Length);
            byte[] header_to_bytes = Encoding.Default.GetBytes(header);  //应答头
            socket.Send(statusline_to_bytes);  //发送状态行
            socket.Send(header_to_bytes);  //发送应答头
            socket.Send(new byte[] { (byte)'\r', (byte)'\n' });  //发送空行
            socket.Send(content_to_bytes);  //发送正文（html）
        }
    }
}