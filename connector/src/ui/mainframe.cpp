#include "ui/mainframe.hpp"
#include "apply_theme.hpp"

MainFrame::MainFrame()
{
    auto* panel = new wxPanel(this);
    auto* label = new wxStaticText(panel, wxID_ANY, _("Color_Picker"));

    auto* sizer = new wxBoxSizer(wxVERTICAL);
    // コンストラクタ内で FromDIP するとクラッシュするため、wxSizerFlags の既定の余白を使う
    sizer->Add(label, wxSizerFlags().Border(wxALL));
    panel->SetSizer(sizer);

    // AviUtl2 のテーマ色を適用 (背景・文字)
    awx::theme::ApplyTree(*panel);
}
