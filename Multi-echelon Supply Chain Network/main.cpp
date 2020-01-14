#pragma once
#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"
#include "CDiffEvol.h"
#include "CSolution.h"
#include "CRandomSearch.h" 
#include "CProblem.h"
#include "COptimizer.h"
#include "CTimer.h"

void test()
{
	int timeDiff = 5;

	int populationSize = 10;
	double crosProb = 0.2;
	double diffWeight = 0.5;
	int timeRandomSearch = 10;

	CTimer time;


	int* err = new int;
	CMscnProblem* problem = new CMscnProblem();
	CSolution csolution;
	csolution.readFromFile("readSolution.txt");
	(*problem).readFromFile("readProblem.txt");

	/////////////////////////////////SPRAWDZENIE FUNKCJI POPRAWIAJ¥CEJ QUALITY////////////////////////////////
	std::cout << "Quality: " << (*problem).getQuality(csolution, err) << "\n";
	std::cout << "Constrained satisfied: " << (*problem).constrainedSatisfied(csolution, err) << "\n";

	std::cout << "Quality: " << (*problem).getQualityIfNotGoodImprove(csolution) << "\n";
	std::cout << "Constrained satisfied: " << (*problem).constrainedSatisfied(csolution, err) << "\n";

	//////////////RANDOMSEARCH////////////////////

	 CRandomSearch randomSearch(problem);
	 randomSearch.randomSearch(timeRandomSearch);
	
	
	//////////////DIFERANTIAL////////////////////
	CDiffEvol diff(problem, diffWeight, crosProb, populationSize);
	std::cout << "Najlepszy wynik to: " << diff.startDifferentialEvolution(timeDiff) << "\n";


}


int main()
{
	test();
}
