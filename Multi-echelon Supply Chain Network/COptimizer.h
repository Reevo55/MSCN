#pragma once
#include"pch.h"
#include"CProblem.h"
#include"CTimer.h"
class COptimizer {
public: 
	COptimizer(CProblem* problem) { this->problem = problem; }
	virtual void startOptimalization(int seconds) = 0;
	void setProblem(CProblem* newProblem) { if (problem != nullptr) problem = nullptr; problem = newProblem; }
protected:
	CProblem* problem;
	CTimer timer;
};