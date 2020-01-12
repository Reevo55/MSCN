#pragma once
#include "pch.h"
#include "CMscnProblem.h"
#include "CSolution.h"
#include "CRandom.h"

class CRandomSearch {
public:
	CRandomSearch(CMscnProblem* problem) { this->problem = problem; }
	void setProblem(CMscnProblem* problem) { if (this->problem = NULL) this->problem = problem; }
	int randomSearch(int howMuchTimeInSeconds);
	void setSeed(int value) { this->seed = value; }
	int getSeed() { return this->seed; }
	CSolution nextValid();
private:
	int seed;
	CMscnProblem* problem;
};