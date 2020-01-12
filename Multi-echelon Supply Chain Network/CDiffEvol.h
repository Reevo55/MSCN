#pragma once
#include "pch.h"

#include "CMscnProblem.h"
#include "CSolution.h"
#include "CRandom.h"
#include "CRandomSearch.h"


class CDiffEvol {
public:
	CDiffEvol(int populationNumber) { this->populationNumber = populationNumber; }
	double startDifferentialEvolution(CMscnProblem * problem, double differenceWeight, double crossProbability, int howMuchTimeInSeconds);
	void print(){}
	double* getPopulationQuality() { return populationQuality; }
private:
	int populationNumber;
	double ** population;
	double *populationQuality;
	double tablesSize;

	void initPopulation(CMscnProblem * problem);
	bool indexesAreDifferent(int first, int second, int third, int fourth);
};