#include "KillingTimer.h"

// 类初始化
KillingTimer::KillingTimer(Initialize* _initialize) :
    R(160), G(0), B(0), total_seconds(0), seconds(0), milliseconds(0), is_timer_running(false), push_intevals(10) {
    initialize = _initialize;
    max_time = initialize->MAX_KILLING_TIME;
    _stprintf_s(time_text, _T("%02d:%01d"), seconds, milliseconds);
    the_first = GetNowTimePoint();
    now = GetNowTimePoint();
}

KillingTimer::~KillingTimer() {
}

// 初始化计时器
void KillingTimer::InitialinzeTimer() {
    total_seconds = 0, seconds = 0, milliseconds = 0;
    R = 0; G = 0; B = 0;
    is_timer_running = true;
    the_first = GetNowTimePoint();      // 重新设置开始时间点
}

// 计算时间
void KillingTimer::CalculateTime() {
    if (is_timer_running && total_seconds <= initialize->MAX_KILLING_TIME) {
        now = GetNowTimePoint();
        milliseconds = std::chrono::duration<double, std::milli>(now - the_first).count() / 100;       // 计算时间差，并转换为毫秒(只保留一位)
        if (milliseconds > 9) {
            the_first = GetNowTimePoint();
            ++seconds;
            ++total_seconds;
        }
        // 防止溢出
        if (seconds >= 30) {
            seconds = 30;
            milliseconds = 0;
        }
    }
}

// 设置颜色变化
void KillingTimer::ChangeStyle() {
    G = total_seconds * (255 / max_time);
    B = total_seconds * (255 / max_time);
    // 防止溢出
    if (G > 255) {
        G = 255;
    }
    if (B > 255) {
        B = 255;
    }
}

// 绘制时间
void KillingTimer::DrawTime() {
    ChangeStyle();
    _stprintf_s(time_text, _T("%02d.%01d"), seconds, milliseconds);
    setbkmode(TRANSPARENT);
    settextcolor(RGB(&R, &G, &B));
    settextstyle(80, 40, _T("Hack"));
    outtextxy(360, 10, time_text);
}

// 按键检测
void KillingTimer::CheckInput() {
    if (push_intevals == 10 {
        if (GetAsyncKeyState(initialize->KEY_KILLINGTIMER)) {
            InitialinzeTimer();
            push_intevals = 0;
        }
    } else {
        ++push_intevals;
    }
}

std::chrono::steady_clock::time_point KillingTimer::GetNowTimePoint() {
    return std::chrono::high_resolution_clock::now();
}