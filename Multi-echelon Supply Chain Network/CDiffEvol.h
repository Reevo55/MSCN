#pragma once
#include "pch.h"
#include "CMscnProblem.h"
#include "CSolution.h"
#include "CRandom.h"
#include "CRandomSearch.h"
#include "CProblem.h"
#include "COptimizer.h"


class CDiffEvol : public COptimizer
{
public:
	CDiffEvol(CProblem* problem, double differenceWeight, double crossProbability, int populationNumber) : COptimizer(problem) { this->populationNumber = populationNumber; 
																																this->differenceWeight = differenceWeight; this->crossProbability = crossProbability; }
	double startDifferentialEvolution(int howMuchTimeInSeconds);
	void print(){}
	double* getPopulationQuality() { return populationQuality; }
	void startOptimalization(int howMuchTime) { startDifferentialEvolution(howMuchTime); }
private:
	int populationNumber;
	double ** population;
	double *populationQuality;
	double tablesSize;
	double crossProbability;
	double differenceWeight;

	void initPopulation();
	bool indexesAreDifferent(int first, int second, int third, int fourth);
	void fixGenotype(double* genotype);
};