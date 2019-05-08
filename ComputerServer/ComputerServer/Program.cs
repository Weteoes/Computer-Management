using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Weteoes;
using System.Xml;

namespace ComputerServer
{
    class Program
    {
        static WinApi.SetConsoleCtrlHandlerControl closeEvent;
        static void Main(string[] args)
        {
            try {
                closeEvent = new WinApi.SetConsoleCtrlHandlerControl(closeing);
                WinApi.SetConsoleCtrlHandler(closeEvent, true);
            } catch { }
            loadingServer();
            new SocketClass().server(ConfigClass.serverPort, true);
        }
        static bool closeing(int type) {
            new SocketClass().stop();
            foreach (ServerClass.serverUser i in ServerClass.allServerList) {
                foreach (ServerClass.serverComputer ii in i.server) {
                    ii.socket.Close();
                    ii.socket.Dispose();
                }
            }
            return false;
        }
        static void loadingServer() {
            try
            {
                XmlDocument a = new XmlClass().read("xml/server.xml");
                ConfigClass.serverPort = int.Parse(a.GetElementsByTagName("port").Item(0).InnerXml);
            }
            catch (Exception error) {
                new MessageClass().writeLog("ComputerServer->loadingServer Error:" + error);
            }
        }
    }
}
