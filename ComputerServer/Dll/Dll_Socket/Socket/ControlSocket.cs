using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Text;
using System.Collections.Generic;
using System.IO;

namespace Weteoes
{
    public class ControlSocketClass
    {
        List<TcpListener> allTcpListener = new List<TcpListener>(); //监听ip集合
        static List<SocketType> SocketTypeList = new List<SocketType>(); //Socket集合(客户机)
        private Dictionary<Socket, byte[]> tempMap = new Dictionary<Socket, byte[]>(); //临时缓存区(一个Sokcet一个缓存区)
        int SocketByteSize = 600000; //设置缓存区大小
        static bool status = true; //运行状态
        public void server(int port, bool allIPAddress = false)
        {
            TcpListener b = null;
            try
            {
                WriteMessage("初始化服务器");
                if (!allIPAddress)
                {
                    string name = Dns.GetHostName();
                    IPAddress[] ipadrlist = Dns.GetHostAddresses(name);
                    string all = "";
                    foreach (IPAddress aaaaa in ipadrlist)
                    {
                        if (all.IndexOf(aaaaa.ToString() + "|") != -1) { continue; }
                        all += aaaaa + "|";
                        IPAddress a = IPAddress.Parse(aaaaa.ToString());
                        if (aaaaa.AddressFamily == AddressFamily.InterNetwork)
                        {
                            b = new TcpListener(a, port);
                            new Thread(new ParameterizedThreadStart(serverListen)).Start(b);
                        }
                        else {  WriteMessage("IPv6地址：" + a + " 已跳过"); }
                    }
                }
                else
                {
                    IPAddress ip = IPAddress.Parse("0.0.0.0");
                    b = new TcpListener(ip, port);
                    new Thread(new ParameterizedThreadStart(serverListen)).Start(b);
                }
            }
            catch { WriteMessage("初始化服务器失败"); }
        }
        public void stop()
        {
            try
            {
                status = false;
                Thread.Sleep(300);
                foreach (TcpListener i in allTcpListener) { if (i != null) { i.Stop(); } } //关闭监听
                foreach (SocketType i in SocketTypeList) { i.SocketConnect.Close(); i.SocketConnect.Dispose(); } //关闭Socket
                WriteMessage("关闭服务器成功");
            }
            catch
            {
                WriteMessage("关闭服务器失败");
            }
        }
        private void serverListen(object serverIP)
        {
            TcpListener b = (TcpListener)serverIP;
            try
            {
                allTcpListener.Add(b);
                b.Start();
                WriteMessage("线程启动,IPv4地址：" + b.LocalEndpoint);
                while (status)
                {
                    try
                    {
                        Socket c = b.AcceptSocket();
                        int SocketTypeListNow = SocketTypeList.Count; //当前添加位置
                        SocketTypeList.Add(new SocketType() { SocketConnect = c, SocketByte = new byte[SocketByteSize] }); //添加集合
                        c.BeginReceive(SocketTypeList[SocketTypeListNow].SocketByte, 0, SocketTypeList[SocketTypeListNow].SocketByte.Length, SocketFlags.None, new AsyncCallback(InternetSocketCallback), SocketTypeList[SocketTypeListNow]);
                    }
                    catch (Exception error)
                    {
                        WriteMessage("捕捉 Error:IPv4地址：" + b.LocalEndpoint + " ," + error.Message);
                    }
                }
            }
            catch (Exception error)
            {
                WriteMessage("Error:IPv4地址：" + b.LocalEndpoint + " ," + error.Message);
                return;
            }
        }
        public bool sendSocket(Socket socket, string data)
        {
            try
            {
                socket.Send(Encoding.Default.GetBytes(data));
                socket.SendTimeout = 100;
                return true;
            }
            catch
            {
                socket.Close();
                socket.Dispose();
                return false;
            }
        }
        private void InternetSocketClose(SocketType socketType)
        {
            socketType.SocketConnect.Close();
            socketType.SocketConnect.Dispose();
        }
        public byte[] SubByte(byte[] srcBytes, int startIndex, int length)
        {
            System.IO.MemoryStream bufferStream = new System.IO.MemoryStream();
            byte[] returnByte = new byte[] { };
            if (length == 0) { return returnByte; }
            if (srcBytes == null) { return returnByte; }
            if (startIndex < 0) { startIndex = 0; }
            if (startIndex < srcBytes.Length)
            {
                if (length < 1 || length > srcBytes.Length - startIndex) { length = srcBytes.Length - startIndex; }
                bufferStream.Write(srcBytes, startIndex, length);
                returnByte = bufferStream.ToArray();
                bufferStream.SetLength(0);
                bufferStream.Position = 0;
            }
            bufferStream.Close();
            bufferStream.Dispose();
            return returnByte;
        }

        
        private void InternetSocketCallback(IAsyncResult WeteoesType)
        {
            SocketType socketType = (SocketType)WeteoesType.AsyncState;
            Socket socket = socketType.SocketConnect;
            bool IsReturn = true; //是否关闭连接
            try {
                // get Temp
                byte[] temp = { };
                if (!tempMap.TryGetValue(socket, out temp)) { temp = new byte[0]; }

                /* Recv */
                //string data = System.Text.Encoding.UTF8.GetString(socketType.SocketByte);
                byte[] allResult = { };
                string data = "";
                if (temp.Length > 0)
                {
                    Array.Resize(ref allResult, allResult.Length + temp.Length);
                    allResult = SubByte(temp, 0, temp.Length);

                    data += System.Text.Encoding.ASCII.GetString(temp);

                    Array.Clear(temp, 0, temp.Length);
                    Array.Resize(ref temp, 0);
                }
                Array.Resize(ref allResult, allResult.Length + socketType.SocketByte.Length);
                socketType.SocketByte.CopyTo(allResult, allResult.Length - socketType.SocketByte.Length);

                data += System.Text.Encoding.ASCII.GetString(socketType.SocketByte);
                data = data.TrimEnd('\0');

                Array.Resize(ref allResult, data.Length);
                recv:
                while (socket.Available > 0)
                {
                    int availableLength = socket.Available;
                    socketType.SocketByte = new byte[availableLength];
                    socket.Receive(socketType.SocketByte, 0, socketType.SocketByte.Length, SocketFlags.None);
                    Array.Resize(ref allResult, allResult.Length + socketType.SocketByte.Length);
                    socketType.SocketByte.CopyTo(allResult, allResult.Length - socketType.SocketByte.Length);
                    data += System.Text.Encoding.ASCII.GetString(socketType.SocketByte);
                }
                int endInt = data.LastIndexOf("|end|");
                if (socket.Available > 0) { goto recv; }
                if (endInt != -1) {
                    String dataTemp = data.TrimEnd('\0');
                    int onlyDataLength = endInt + 5; // 加上|end|的长度
                    temp = SubByte(allResult, onlyDataLength, dataTemp.Length - onlyDataLength); // 临时数据(未接受完整的)
                    Array.Resize(ref allResult, onlyDataLength);  // 设置发送数据大小
                                                                  // 执行操作
                    if (new ControlMainClass().Entrance(allResult, ref socket)) { // 操作成功则保留Socket
                        IsReturn = false;
                        InternetSocketCallbackReset(socketType); // 读取数据完毕，重新监听
                    }
                }
            }
            catch { }
            finally {
                if (IsReturn == true) { // 是否退出 
                    socket.Close();
                    socket.Dispose();
                    if (SocketTypeList.IndexOf(socketType) != -1) {
                        SocketTypeList.Remove(socketType); //删除列表
                    }
                }
            }
        }
        private void InternetSocketCallbackReset(SocketType socketType)
        { //重新设置监听
            socketType.SocketByte = new byte[SocketByteSize];
            socketType.SocketConnect.BeginReceive(socketType.SocketByte, 0, socketType.SocketByte.Length, SocketFlags.None, new AsyncCallback(InternetSocketCallback), socketType);
        }
        class SocketType
        {
            public Socket SocketConnect;
            public byte[] SocketByte;
        }

        static MessageClass messageClass = new MessageClass();
        public void WriteMessage(string msg) {
            messageClass.writeLog("Control:" + msg);
        }
    }
}
