using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Weteoes;
using System.Xml;
using System.Threading;

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
            //Thread socketThread = new Thread(new ThreadStart(() => new SocketClass().server(ConfigClass.serverPort, true)));
            //Thread controlSocketThread = new Thread(new ThreadStart(() => new ControlSocketClass().server(ConfigClass.controlServerPort, true)));
            new BasicSocketClass().server(ConfigClass.serverPort, true);
            new ControlSocketClass().server(ConfigClass.controlServerPort, true);
        }
        static bool closeing(int type) {
            new BasicSocketClass().stop();
            new ControlSocketClass().stop();
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
