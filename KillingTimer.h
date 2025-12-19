#ifndef _KILLINGTIMER_H_
#define _KILLINGTIMER_H_

#include "Timer.h"

class KillingTimer : public Timer {
private:
    Initialize* initialize;
    int max_time;
    int R, G, B;
    int total_seconds, seconds, milliseconds;
    bool is_timer_running;
    TCHAR time_text[64];
    std::chrono::steady_clock::time_point the_first;
    std::chrono::steady_clock::time_point now;
    int push_intevals;
public:
    KillingTimer(Initialize* _initialize);
    ~KillingTimer();
    void InitialinzeTimer();
    void CalculateTime();
    void ChangeStyle();
    void DrawTime();
    void CheckInput();
    std::chrono::steady_clock::time_point GetNowTimePoint();
};

#endif // !_KILLINGTIMER_H_