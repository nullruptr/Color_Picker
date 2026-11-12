#pragma once
#include <wx/wx.h>
#include "ipc/host_client.hpp"
#include "dpi_patch.hpp"

// AviUtl2 のウィンドウクライアントとして登録する wx のフレーム。
class MainFrame : public wxFrame {
public:
    MainFrame();
    ~MainFrame() override;

protected:
    WXLRESULT MSWWindowProc(WXUINT msg, WXWPARAM wParam, WXLPARAM lParam) override;

private:
    awx::AviUtl2DpiPatch m_dpi_patch;
    cl::HostClient m_host_client;
    wxStaticText* m_status = nullptr;
};
