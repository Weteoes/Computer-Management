using System;
using System.Xml;
using System.IO;

namespace Weteoes
{
    public class XmlClass
    {
        XmlDocument Xmldocument = null;
        string Xmlpath = null;
        public XmlDocument read(string path) {
            try
            {
                if (!File.Exists(path)) { new InitializationClass().xml(path); }
                XmlDocument a = new XmlDocument();
                a.Load(path);
                Xmldocument = a;
                Xmlpath = path;
                return a;
            }
            catch {
                return null;
            }
        }
        public void save() {
            try
            {
                Xmldocument.Save(Xmlpath);
            }
            catch { }
        }
    }
}
