namespace Weteoes
{
    class AppConfigClass
    {
        public string GetConfig(ref string text, string flag = "_") {
            try
            {
                string a = text.Substring(0, text.IndexOf(flag));
                string b = text.Substring(a.Length + 1);
                text = b;
                return a;
            }
            catch {
                return "";
            }
        }
    }
}
