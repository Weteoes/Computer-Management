using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Weteoes
{
    public class Wvariable
    {
        public const int WM_APPCOMMAND = 0x319;
        public const int APPCOMMAND_VOLUME_UP = 0x0a; //音量+,使用要 * 0x10000
        public const int APPCOMMAND_VOLUME_DOWN = 0x09; //音量-,使用要 * 0x10000
        public const int APPCOMMAND_VOLUME_MUTE = 0x08; 
    }
}
