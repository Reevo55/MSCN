#pragma once
#include "pch.h"
#include "CMscnProblem.h"
#include "CSolution.h"
#include "CRandom.h"
#include "CProblem.h"
#include "COptimizer.h"


class CRandomSearch: public COptimizer{
public:
	CRandomSearch(CProblem* problem) : COptimizer(problem) {}
	void setProblem(CProblem* problem) { if (this->problem = NULL) this->problem = problem; }
	int randomSearch(int howMuchTimeInSeconds);

	void startOptimalization(int howMuchTime) { randomSearch(howMuchTime); }

	void setSeed(int value) { this->seed = value; }
	int getSeed() { return this->seed; }
	double* nextValid();
private:
	int seed;
};