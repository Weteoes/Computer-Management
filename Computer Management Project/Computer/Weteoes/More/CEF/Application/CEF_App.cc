#include <pch.h>

#include "CEF_App.h"
#include "CEF_Handler.h"
#include "CEF_V8Handler.h"
#include <Weteoes/More/CEF/include/cef_browser.h>
#include <Weteoes/More/CEF/include/cef_command_line.h>
#include <Weteoes/More/CEF/include/views/cef_browser_view.h>
#include <Weteoes/More/CEF/include/views/cef_window.h>
#include <Weteoes/More/CEF/include/wrapper/cef_helpers.h>
#include <Weteoes/More/CEF/Config.h>
#include <Weteoes/Application/CEF/AppCef.h>
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/More/CEF/Application/CEF_WindowDelegate.h>

CEF_App::CEF_App() {}

void CEF_App::OnBeforeCommandLineProcessing(const CefString & process_type, CefRefPtr<CefCommandLine> command_line) {
#ifdef cef_single_process
	command_line->AppendSwitch("single-process");
#endif
#ifdef cef_disable_gpu
	command_line->AppendSwitch("disable-gpu");
	command_line->AppendSwitch("disable-gpu-compositing");
#endif
#ifdef cef_no_proxy
    command_line->AppendSwitch("no-proxy-server");
#endif
}

void CEF_App::OnContextInitialized() {
  CEF_REQUIRE_UI_THREAD();
//    CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();
//#if defined(OS_WIN) || defined(OS_LINUX)
//  const bool use_views = command_line->HasSwitch("use-views");
//#else
//  const bool use_views = false;
//#endif
}


void CEF_App::OnWebKitInitialized() {
    std::string Code =
        "var weteoesBrowser = {"
        "    dlg: {"
        "        mouse: {"
        "            down (x, y) { native function Dlg_Mouse_Down(x, y); return Dlg_Mouse_Down(x, y); },"
        "            move (x, y) { native function Dlg_Mouse_Move(x, y); return Dlg_Mouse_Move(x, y); },"
        "            up () { native function Dlg_Mouse_Up(); return Dlg_Mouse_Up(); },"
        "        },"
        "        size (width, height) { native function Dlg_Size(width, height); return Dlg_Size(width, height); },"
        "        minimize () { native function Dlg_Minimize(); return Dlg_Minimize(); },"
        "        close () { native function Dlg_Close(); return Dlg_Close(); },"
        "        exit () { native function Dlg_Exit(); return Dlg_Exit(); },"
        "        create (url) { native function Dlg_Create(url); return Dlg_Create(url); }"
        "    },"
        "    app (app, fun, args) { args = JSON.stringify(args); native function App(app, fun, args); return App(app, fun, args); }"
        "};";
	CefRegisterExtension("V8/CEF", Code, new CEF_V8Handler());
}

void CEF_App::OnContextCreated(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context) {
}