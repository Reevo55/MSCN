#pragma once
#include "pch.h"

#include "CMscnProblem.h"
#include "CSolution.h"

class CRandomSearch {
public:

	CRandomSearch(CMscnProblem* problem) { this->problem = problem; }
	void setProblem(CMscnProblem* problem) { if (this->problem != NULL) delete this->problem; else this->problem = problem; }
	int randomSearch(int howMuchTimeInSeconds, CSolution& solution);

private:
	CMscnProblem* problem;
};