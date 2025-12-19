#include "SmugglingTimer.h"

// 类初始化
SmugglingTimer::SmugglingTimer(Initialize* _initialize) :
    R(51), G(255), B(51), minutes(0), seconds(0), milliseconds(0), is_timer_running(false), push_intevals(10) {
    initialize = _initialize;
    max_time = initialize->MAX_SMUGGLING_TIME;
    _stprintf_s(time_text, _T("%02d:%02d:%01d"), minutes, seconds, milliseconds);
    the_first = GetNowTimePoint();
    now = GetNowTimePoint();
}

SmugglingTimer::~SmugglingTimer() {
}

// 初始化计时器
void SmugglingTimer::InitialinzeTimer() {
    total_seconds = 0, minutes = 0, seconds = 0, milliseconds = 0;
    R = 51; G = 255; B = 51;
    is_timer_running = true;
    the_first = GetNowTimePoint();      // 重新设置开始时间点
}

// 计算时间
void SmugglingTimer::CalculateTime() {
    if (is_timer_running && total_seconds <= initialize->MAX_SMUGGLING_TIME) {
        now = GetNowTimePoint();
        milliseconds = std::chrono::duration<double, std::milli>(now - the_first).count() / 100;       // 计算时间差，并转换为毫秒(只保留一位)
        if (milliseconds > 9) {
            the_first = GetNowTimePoint();
            ++seconds;
            ++total_seconds;
        }
        if (seconds > 59) {
            seconds = 0;
            ++minutes;
        }
        // 防止溢出
        if (minutes >= 60) {
            minutes = 60;
            seconds = 60;
            milliseconds = 0;
        }
    }
}

// 设置颜色变化
void SmugglingTimer::ChangeStyle() {
    switch (total_seconds) {
    case 60:
        R = 255; G = 255; B = 51;
        break;
    case 90:
        R = 255; G = 51; B = 51;
        break;
    case 180:
        R = 51; G = 255; B = 255;
        break;
    default:
        break;
    }
}

// 绘制时间
void SmugglingTimer::DrawTime() {
    ChangeStyle();
    _stprintf_s(time_text, _T("%02d:%02d.%01d"), minutes, seconds, milliseconds);
    setbkmode(TRANSPARENT);
    settextcolor(RGB(R, G, B));
    settextstyle(80, 40, _T("Hack"));
    outtextxy(0, 10, time_text);
}

// 按键检测
void SmugglingTimer::CheckInput() {
    if (push_intevals == 10) {
        if (GetAsyncKeyState(initialize->KEY_SMUGGLINGTIMER)) {
            InitialinzeTimer();
            push_intevals = 0;
        }
    } else {
        ++push_intevals;
    }
}

std::chrono::steady_clock::time_point SmugglingTimer::GetNowTimePoint() {
    return std::chrono::high_resolution_clock::now();
}