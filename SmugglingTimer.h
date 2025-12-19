#ifndef _SMUGGLINGTIMER_H_
#define _SMUGGLINGTIMER_H_

#include "Timer.h"

class SmugglingTimer : public Timer {
private:
    Initialize* initialize;
    int max_time;
    int R, G, B;
    int total_seconds, minutes, seconds, milliseconds;
    bool is_timer_running;
    TCHAR time_text[64];
    std::chrono::steady_clock::time_point the_first;
    std::chrono::steady_clock::time_point now;
    int push_intevals;
public:
    SmugglingTimer(Initialize* _initialize);
    ~SmugglingTimer();
    void InitialinzeTimer();
    void CalculateTime();
    void ChangeStyle();
    void DrawTime();
    void CheckInput();
    std::chrono::steady_clock::time_point GetNowTimePoint();
};

#endif // !_SMUGGLINGTIMER_H_