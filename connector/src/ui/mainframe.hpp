#pragma once
#include "hosted_frame.hpp"

// AviUtl2 のウィンドウクライアントとして登録する wx のフレーム。
class MainFrame : public awx::HostedFrame {
public:
    MainFrame();
};
