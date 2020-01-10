#pragma once
#include "pch.h"

#include "CMscnProblem.h"
#include "CSolution.h"
#include "CRandom.h"

class CRandomSearch {
public:

	CRandomSearch(CMscnProblem* problem) { this->problem = problem; }
	void setProblem(CMscnProblem* problem) { if (this->problem != NULL) delete this->problem; else this->problem = problem; }
	int randomSearch(int howMuchTimeInSeconds);

private:
	CMscnProblem* problem;
};