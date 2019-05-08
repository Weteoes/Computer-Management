using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Weteoes
{
    public class WinApi
    {
        /// <summary>
        /// 捕捉控制台关闭事件
        /// </summary>
        /// <param name="HandlerRoutine">SetConsoleCtrlHandlerControl事件</param>
        /// <param name="Add">添加为true</param>
        /// <returns></returns>
        [DllImport("kernel32.dll")] public static extern bool SetConsoleCtrlHandler(SetConsoleCtrlHandlerControl HandlerRoutine, bool Add); public delegate bool SetConsoleCtrlHandlerControl(int CtrlType);

        /// <summary>
        /// 模拟键盘按键
        /// </summary>
        /// <param name="bVk">键盘Key</param>
        /// <param name="bScan">为0即可</param>
        /// <param name="dwFlags">0按下 2抬起</param>
        /// <param name="dwExtraInfo">为0即可</param>
        /// <returns></returns>
        [DllImport("user32.dll", EntryPoint = "keybd_event", SetLastError = true)] public static extern void keybd_event(byte bVk, byte bScan, int dwFlags, int dwExtraInfo);

        /// <summary>
        /// 发送消息不确保接收,会放入消息队列
        /// </summary>
        /// <param name="hWnd">接收消息目标句柄</param>
        /// <param name="Msg">消息类型</param>
        /// <param name="wParam">为0即可</param>
        /// <param name="lParam">位置,为32为长整型,前16位为y,后16位为x</param>
        /// <returns></returns>
        [DllImport("user32.dll", SetLastError = true)] public static extern bool PostMessage(IntPtr hWnd, int Msg, int wParam, uint lParam);

        /// <summary>
        /// 发送消息确保接收,如果对面正忙可能丢包
        /// </summary>
        /// <param name="hWnd">接收消息目标句柄</param>
        /// <param name="Msg">消息类型</param>
        /// <param name="wParam">为0即可</param>
        /// <param name="lParam">位置,为32为长整型,前16位为y,后16位为x</param>
        /// <returns></returns>
        [DllImport("user32.dll", SetLastError = true)] public static extern bool SendMessage(IntPtr hWnd, int Msg, int wParam, uint lParam);

        /// <summary>
        /// 通过句柄获取目标窗口的top,right,bottom,left.可以计算出目标窗口高和宽
        /// </summary>
        /// <param name="hWnd">句柄</param>
        /// <param name="lpRect">GetWindowRectRect 变量</param>
        /// <returns></returns>
        [DllImport("user32.dll")] [return: MarshalAs(UnmanagedType.Bool)] public static extern bool GetWindowRect(IntPtr hWnd, ref GetWindowRectRect lpRect); public struct GetWindowRectRect { public int left, top, right, bottom; }

        /// <summary>
        /// 移动鼠标,基于屏幕绝对位置
        /// </summary>
        /// <param name="x">屏蔽左坐标</param>
        /// <param name="y">屏幕右坐标</param>
        /// <returns></returns>
        [DllImport("user32.dll")] public static extern int SetCursorPos(int x, int y);

        /// <summary>
        /// 在某个句柄中查找子句柄
        /// </summary>
        /// <param name="hwndParent">句柄</param>
        /// <param name="hwndChildAfter">为空即可IntPtr.Zero</param>
        /// <param name="lpszClass">通过class查找</param>
        /// <param name="lpszWindow">通过标题查找</param>
        /// <returns></returns>
        [DllImport("User32.DLL")] public static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpszClass, string lpszWindow);

        /// <summary>
        /// 查找句柄
        /// </summary>
        /// <param name="lpClassName">通过class名称查找</param>
        /// <param name="lpWindowName">通过标题查找</param>
        /// <returns></returns>
        [DllImport("User32.dll")] public static extern IntPtr FindWindow(string lpClassName, string lpWindowName);

        /// <summary>
        /// 获取目标句柄标题
        /// </summary>
        /// <param name="hWnd">句柄</param>
        /// <param name="lpString">StringBuilder变量,需要引入System.Text</param>
        /// <param name="nMaxCount">StringBuilder变量的Capacity属性</param>
        /// <returns></returns>
        [DllImport("user32.dll")] public static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

        /// <summary>
        /// 遍历目标句柄的子句柄
        /// </summary>
        /// <param name="hWnd">句柄</param>
        /// <param name="lpfn">遍历方法,参数需和EnumWindowProc一致</param>
        /// <param name="lParam">为0即可</param>
        /// <returns></returns>
        [DllImport("user32.dll")] public static extern int EnumChildWindows(IntPtr hWnd, EnumWindowProc lpfn, int lParam); public delegate bool EnumWindowProc(int hwnd, int lParam);

        /// <summary>
        /// 通过句柄获取Class名称
        /// </summary>
        /// <param name="hWnd">句柄</param>
        /// <param name="ClassName">StringBuilder变量,需要引入System.Text</param>
        /// <param name="nMaxCount">StringBuilder变量的Capacity属性</param>
        /// <returns></returns>
        [DllImport("User32.dll", CharSet = CharSet.Auto)] public static extern int GetClassName(IntPtr hWnd, StringBuilder ClassName, int nMaxCount);

        /// <summary>
        /// 设置当前顶部窗口
        /// </summary>
        /// <param name="hWnd">句柄</param>
        /// <returns></returns>
        [DllImport("USER32.DLL", CharSet = CharSet.Auto)] public static extern bool SetForegroundWindow(IntPtr hWnd);
    }
}
