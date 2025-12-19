#include "Smugglingtimer.h"
#include "Killingtimer.h"
#include "initialize.h"

static bool EXE_RUNNING = true;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Initialize* initialize = Initialize::getInstance();
    std::vector<Timer*> timers;
    if (initialize->ENABLE_SMUGGLING_TIMER) {
        SmugglingTimer* smuggling_timer = new SmugglingTimer(initialize);
        timers.emplace_back(smuggling_timer);
    }
    if (initialize->ENABLE_KILLING_TIMER) {
        KillingTimer* killing_timer = new KillingTimer(initialize);
        timers.emplace_back(killing_timer);
    }

    HWND hWnd = initgraph(520, 80);
    SetWindowText(hWnd, _T("Phasmophobia Timer"));                                                                                                  // 设置标题
    SetWindowPos(hWnd, HWND_TOPMOST, GetSystemMetrics(SM_CXSCREEN) / 2 - 270 + initialize->OFFSET_X, initialize->OFFSET_Y, 0, 0, SWP_NOSIZE);       // 设置窗口位置
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_CAPTION);                                                                   // 设置无边框
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);                                                             // 设置透明
    SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);                                                                                // 设置透明

    BeginBatchDraw();
    while (&EXE_RUNNING) {
        DWORD start_time = GetTickCount();

        // 按键检测：检测是否计时
        for (auto timer : timers) {
            timer->CheckInput();
        }

        // 计算时间
        for (auto timer : timers) {
            timer->CalculateTime();
        }

        // 绘制时间
        cleardevice();
        for (auto timer : timers) {
            timer->DrawTime();
        }
        FlushBatchDraw();

        // 帧率控制
        DWORD end_time = GetTickCount();
        DWORD delta_time = end_time - start_time;
        if (delta_time < initialize->FPS) {
            Sleep(initialize->FPS - delta_time);
        }
    }
    EndBatchDraw();

    for (auto timer : timers) {
        timers.push_back(timer);
        delete timer;
    }
    return 0;
}