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
        private Dictionary<IntPtr, int> closeMap = new Dictionary<IntPtr, int>(); //准备退出缓存区(一个Sokcet一个缓存区)
        private Dictionary<IntPtr, byte[]> tempMap = new Dictionary<IntPtr, byte[]>(); //临时缓存区(一个Sokcet一个缓存区)
        int SocketByteSize = 600000; //设置缓存区大小
        static bool status = true; //运行状态

        public string flac_Start = "|start|";
        public string flac_End = "|end|";
        public string flac_Success = "|Success|";

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
                socket.Send(Encoding.ASCII.GetBytes(data));
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
        
        private void InternetSocketCallback(IAsyncResult WeteoesType)
        {
            SocketType socketType = (SocketType)WeteoesType.AsyncState;
            Socket socket = socketType.SocketConnect;
            bool IsReturn = false; //是否关闭连接
            try {
                // get Temp
                byte[] temp = new byte[0];
                if (!tempMap.TryGetValue(socket.Handle, out temp)) { temp = new byte[0]; }

                /* Recv */
                byte[] allResult = new byte[0];
                string data = "";

                if (temp.Length > 0) {
                    int byteStart = allResult.Length;
                    Array.Resize(ref allResult, byteStart + temp.Length);
                    Array.Copy(temp, 0, allResult, byteStart, temp.Length);
                    //allResult = SubByte(temp, 0, temp.Length);
                    //data += System.Text.Encoding.ASCII.GetString(temp);
                    Array.Clear(temp, 0, temp.Length);
                    Array.Resize(ref temp, 0);
                }
                bool firstRead = true;
                do {
                    int availableLength = 0;
                    if (!firstRead) { // 如果不是第一次读取，重置内存
                        Array.Clear(socketType.SocketByte, 0, socketType.SocketByte.Length);
                        availableLength = socket.Available;
                        socket.Receive(socketType.SocketByte, 0, availableLength, SocketFlags.None); // 读取socket
                    }
                    int byteStart = allResult.Length; // 记录一会从那里开始输入
                    string onlyData_S = System.Text.Encoding.ASCII.GetString(socketType.SocketByte); // 转到string
                    onlyData_S = onlyData_S.Trim('\0'); // 去掉\0
                    availableLength = onlyData_S.Length; // 有效长度
                    Array.Resize(ref allResult, byteStart + availableLength); // 修改byte大小
                    Array.Copy(socketType.SocketByte, 0, allResult, byteStart, availableLength);
                    data += onlyData_S; // 全局字符串
                    firstRead = false;
                }
                while (socket.Available > 0);

                if (data.Length == 0) { // 用于兼容mono
                    int tempClose;
                    if (!closeMap.TryGetValue(socket.Handle, out tempClose)) { closeMap[socket.Handle] = 0; }
                    if (closeMap[socket.Handle] > 10) { IsReturn = true; }
                    else { closeMap[socket.Handle] = closeMap[socket.Handle] + 1; }
                }
                else { closeMap[socket.Handle] = 0; }

                int findIndex = 0;
                string allRest_S = System.Text.Encoding.ASCII.GetString(allResult);
                //allRest_S = allRest_S.Trim('\0');
                while (true) {
                    int findStart = allRest_S.IndexOf(flac_Start, findIndex);
                    bool quitWhile = false; // 是否退出循环
                    int onlyDataLength = 0; // 数据长度
                    if (allRest_S.Length <= findStart || findStart == -1) { quitWhile = true; }
                    else {
                        int findEnd = allRest_S.IndexOf(flac_End, findStart);
                        onlyDataLength = findEnd - findStart + flac_End.Length - flac_Start.Length; // 加上|end|的长度 减去|start|的长度
                        if (findStart != -1 && findEnd != -1) {
                            byte[] onlyData = SubByte(allResult, findStart + flac_Start.Length, onlyDataLength);
                            string onlyData_s = System.Text.Encoding.ASCII.GetString(onlyData);
                            onlyData_s = onlyData_s.TrimEnd('\0');
                            onlyData = SubByte(onlyData, 0, onlyData_s.Length);
                            int oldDataLen = onlyData_s.Length;
                            onlyData_s = onlyData_s.TrimStart('\0');
                            onlyData = SubByte(onlyData, oldDataLen - onlyData_s.Length, onlyData_s.Length);
                            if (onlyData.Length == 0) { continue; }
                            if (!new ControlMainClass().Entrance(onlyData, ref socket)) {
                                IsReturn = true;
                            }
                        }
                    }
                    if (quitWhile) { // 是否退出循环
                        int len = allRest_S.Length - findIndex;
                        if (len != 0) {
                            temp = SubByte(allResult, findIndex, len); // 临时数据(未接受完整的)
                            tempMap[socket.Handle] = temp; // 放入临时数据列表
                        }
                        break;
                    }
                    findIndex += onlyDataLength; // 最后在加上(因为找的是组合所以没加1也行)
                }
                //if (socket.Available > 0) { goto recv; }
            }
            catch { }
            //catch(Exception error) { WriteMessage("ControlSocketClass->InternetSocketCallback:" + error.Message); }
            finally {
                if (IsReturn == true) { // 是否退出 
                    socket.Close();
                    socket.Dispose();
                    if (SocketTypeList.IndexOf(socketType) != -1) {
                        SocketTypeList.Remove(socketType); //删除列表
                    }
                }
                else { InternetSocketCallbackReset(socketType); } // 重新监听
            }
        }
        private void InternetSocketCallbackReset(SocketType socketType) { //重新设置监听
            try {
                Array.Clear(socketType.SocketByte, 0, socketType.SocketByte.Length);
                socketType.SocketConnect.BeginReceive(socketType.SocketByte, 0, socketType.SocketByte.Length, SocketFlags.None, new AsyncCallback(InternetSocketCallback), socketType);
            }
            catch { }
        }
        class SocketType
        {
            public Socket SocketConnect;
            public byte[] SocketByte;
        }

        static MessageClass messageClass = new MessageClass();
        public void WriteMessage(string msg) {
            messageClass.writeLog("Control:" + msg, true);
        }
        public byte[] SubByte(byte[] srcBytes, int startIndex, int length) {
            try {
                System.IO.MemoryStream bufferStream = new System.IO.MemoryStream();
                byte[] returnByte = new byte[] { };
                if (srcBytes == null) { return returnByte; }
                if (startIndex < 0) { startIndex = 0; }
                if (startIndex < srcBytes.Length) {
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
            catch(Exception error) {
                WriteMessage("ControlSocketClass->SubByte:" + error.Message);
                return new byte[0];
            }
        }
    }
}
