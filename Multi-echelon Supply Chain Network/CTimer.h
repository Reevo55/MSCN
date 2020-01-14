#pragma once
#include "pch.h"
#include <windows.h>

class CTimer {
public:
	void startTimer(){
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&start);
	}
	double endTimer()
	{
		QueryPerformanceCounter(&end);
		return (end.QuadPart - start.QuadPart) / frequency.QuadPart;
	}

private:
	double seconds;
	LARGE_INTEGER start, end, frequency;
};

