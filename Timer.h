#ifndef _TIMER_H_
#define _TIMER_H_

#include "Initialize.h"
#include <graphics.h>
#include <time.h>
#include <windows.h>
#include <vector>
#include <chrono>

class Timer {
public:
	virtual void InitialinzeTimer() = 0;
	virtual void CalculateTime() = 0;
	virtual void ChangeStyle() = 0;
	virtual void DrawTime() = 0;
	virtual void CheckInput() = 0;
	std::chrono::steady_clock::time_point GetNowTimePoint();
};

#endif	// !_TIMER_H_