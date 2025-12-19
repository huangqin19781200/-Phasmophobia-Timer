#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "inicpp.hpp"
#include <graphics.h>
#include <fstream>
#include <string>

class Initialize {
public:
	static Initialize* initialize;
	DWORD FPS;
	int KEY_SMUGGLINGTIMER;
	int KEY_KILLINGTIMER;
	int OFFSET_X;
	int OFFSET_Y;
	int MAX_SMUGGLING_TIME;
	bool ENABLE_SMUGGLING_TIMER;
	int MAX_KILLING_TIME;
	bool ENABLE_KILLING_TIMER;
public:
	Initialize();
    ~Initialize();
	void GetValue();
	static Initialize* getInstance();
};

#endif // !INITIALIZE_H
