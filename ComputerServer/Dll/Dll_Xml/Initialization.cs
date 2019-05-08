using System;
using System.IO;

namespace Weteoes
{
    class InitializationClass
    {
        string[][] xmlIni = {
            new string[]{ "xml/server.xml", "<Weteoes><port>6666</port></Weteoes>" },
        };
        public void xml(string file)
        {
            try
            {
                for (int i = 0; i < xmlIni.Length; i++)
                {
                    string xmlIniFile = xmlIni[i][0];
                    if (file.Equals(xmlIniFile))
                    {
                        string path = xmlIniFile.Substring(0, xmlIniFile.IndexOf("/"));
                        if (!Directory.Exists(path)) {
                            Directory.CreateDirectory(path);
                        }
                        StreamWriter a = new StreamWriter(file);
                        a.Write(xmlIni[i][1]);
                        a.Close();
                        break;
                    }
                }
            }
            catch (Exception error)
            {
                new MessageClass().writeLog("Initialization->xml Error:" + error);
            }
        }
    }
}
