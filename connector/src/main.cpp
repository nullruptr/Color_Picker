#include <winsock2.h>
#include <windows.h>
#include <wx/wx.h>
#include "aviutl2_sdk/plugin2.h"
#include "aviutl2_sdk/config2.h"
#include "ui/mainframe.hpp"
#include "get_colour.hpp"
#include "modal_guard.hpp"
#include "wx_runtime.hpp"

namespace {
HINSTANCE g_hModule = nullptr;
MainFrame* g_frame = nullptr;
bool g_wx_started = false;

COMMON_PLUGIN_TABLE g_plugin_table = {
    L"Color_Picker Connector for AviUtl2",
    L"Color_Picker Connector for AviUtl2",
};
} // namespace

// 設定関連の初期化。InitializePlugin / RegisterPlugin より先に呼ばれる。
EXTERN_C __declspec(dllexport) void InitializeConfig(CONFIG_HANDLE* handle)
{
    awx::theme::SetConfig(handle);
}

EXTERN_C __declspec(dllexport) COMMON_PLUGIN_TABLE* GetCommonPluginTable(void)
{
    return &g_plugin_table;
}

EXTERN_C __declspec(dllexport) void RegisterPlugin(HOST_APP_TABLE* host)
{
    if (!awx::StartWx())
        return;
    g_wx_started = true;

    awx::SetEditHandle(host->create_edit_handle());

    g_frame = new MainFrame();
    host->register_window_client(L"Color_Picker", static_cast<HWND>(g_frame->GetHandle()));
}

EXTERN_C __declspec(dllexport) void UninitializePlugin()
{
    if (g_frame) {
        g_frame->Destroy();
        g_frame = nullptr;
    }
    if (g_wx_started) {
        awx::StopWx();
        g_wx_started = false;
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
        g_hModule = hinstDLL;
    return TRUE;
}
