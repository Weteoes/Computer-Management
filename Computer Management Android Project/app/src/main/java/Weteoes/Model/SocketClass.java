package Weteoes.Model;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.InetSocketAddress;

public class SocketClass {
    public String connect(String ip,int port, String data)
    {
        try {
            java.net.Socket socket = new java.net.Socket(); //获得对应socket的输入/输出流
            socket.connect(new InetSocketAddress(ip,port),2000);
            String rusult = socketSend(socket,data,true);
            socket.close(); //关闭socket
            if(rusult == null){ return null; }
            return rusult;
        }
        catch(Exception error) {
            return null;
        }
    }
    public socketRusult connectLongSocket(String ip,int port, String data)
    {
        try {
            java.net.Socket socket = new java.net.Socket(); //获得对应socket的输入/输出流
            socket.connect(new InetSocketAddress(ip,port),2000);
            String rusult = socketSend(socket,data,false);
            if(rusult == null){ socket.close(); return null; }
            socketRusult socketresult = new socketRusult();
            socketresult.socket = socket;
            socketresult.rusult = rusult;
            return socketresult;
        }
        catch(Exception error) {
            return null;
        }
    }
    public String socketSend(java.net.Socket socket, String data,boolean closeing){
        try{
            //Weteoes.security.RSA rsa = new Weteoes.security.RSA();
            DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
            //data = rsa.byPublicAsEncode(data);
            dos.write(data.getBytes());
            dos.flush(); //发送
            DataInputStream dis = new DataInputStream(socket.getInputStream());
            String result = null;
            byte[] data_one = new byte[2048];
            dis.read(data_one);
//            int len = 0;
//            while ((len = dis.read(data_one)) != -1) {
//                dis.read(data_one);
//            }
            result = new String(data_one, "utf-8").trim();//设定字符集
            if(closeing){
                dis.close(); //关闭数据输入流
                dos.close(); //关闭数据输出流
            }
            try{
                String[] all=result.split("\\|");//直接选最后一个，反正要重构
                for (int i = 0;i<all.length;i++){
                    //all读取完毕，操作
                    //all[i] = rsa.byPrivateAsUnEncode(all[i]);
                    //if( i == all.length - 1 || !all[i].equals(Config.socketOk)){
                    //   result = all[i];
                    //}
                }

            }catch(Exception error){}
            return result;
        }
        catch (Exception error){
            error.printStackTrace();
            return null;
        }
    }
    public class socketRusult{
        public java.net.Socket socket;
        public String rusult;
    }
}
