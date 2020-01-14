#pragma once
#include "pch.h"
#include "CRandom.h"
class CProblem {
public: 
	virtual double getQuality(int* err)=0;
	virtual double getQuality(double* pdSolution, int* err) = 0;

	virtual bool constrainedSatisfied(double* pdSolution, int* err) = 0;
	virtual bool constrainedSatisfied(int* err) = 0;

	virtual int sizeOfSolution() = 0;
	virtual void fixSolutionTable(double* pdSolution, int length)=0;
	virtual void randomizeSolution(CRandom& rand) = 0;
	virtual double* getPdSolution() = 0;
};