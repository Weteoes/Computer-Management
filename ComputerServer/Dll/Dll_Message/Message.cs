using System;
using System.IO;

namespace Weteoes {
    public class MessageClass {
        static string logPath = null;
        static string logTemp = "";
        // allowRepeat �����ظ�
        public void writeLog(string log, bool allowRepeat = false) {
            if (logPath == null)  {
                string a = ConfigClass.startPath + @"/log";
                if (!Directory.Exists(a)) { Directory.CreateDirectory(a); }
                logPath = a + @"/" + DateTime.Now.ToString("yyyyMMdd_HHmmss") + ".log";
            }
            try {
                if (logTemp.Equals(log) && !allowRepeat) { return; }
                logTemp = log;
                StreamWriter TextWrite = new StreamWriter(logPath, true);
                TextWrite.Write(log + "\r\n");
                TextWrite.Close();
                writeLine(log);
            }
            catch { }
        }
        public void writeLine(string writeLine) {
            string dateTime = DateTime.Now.ToString();
            Console.WriteLine(dateTime + ": " + writeLine);
        }
    }
}
