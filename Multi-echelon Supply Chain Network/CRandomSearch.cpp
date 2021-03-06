#pragma once
#include "pch.h"
#include "CRandomSearch.h"
#include "COptimizer.h"
#include "CMscnProblem.h"
#include "CSolution.h"
#include "CRandom.h"
#include "CProblem.h"


int CRandomSearch::randomSearch(int howMuchTimeInSeconds)
{
	int bestQuality = -99999999;
	int counter = 0;
	int current = 0;
	double * solution = new double[problem->sizeOfSolution()];

	CRandom rand;
	timer.startTimer();

	while ((int)timer.endTimer() < howMuchTimeInSeconds)
	{
		solution = problem->randomizeSolution(rand);
		current = problem->getQuality(solution, NULL);

		if (problem->constrainedSatisfied(solution, NULL))
		{
			if (bestQuality < current)
			{
				bestQuality = current;
				std::cout << "\n";
				std::cout << counter << ". Teraz wydajność wynosiła: " << current << ", najlepsze rozwiązanie to: " << bestQuality << ". \n";
				std::cout << "\n";
				//problem->getSolution().saveToFile("readSolution.txt");
			}
			else
			{
				std::cout << "\n";
				std::cout << counter << ". Teraz wydajność wynosiła: " << current << ", najlepsze rozwiązanie to: " << bestQuality << ". \n";
				std::cout << "\n";
			}
		}
		else
		{
			std::cout << counter << ". Teraz wydajność wynosiła: " << current << ", ale rozwiązanie nie jest prawidłowe, najlepsze rozwiązanie to: " << bestQuality << ". \n";
		}
		counter++;
	}
	std::cout << " KONIEC! NAJLEPSZA WARTOŚĆ TO: " << bestQuality << "\n";
	return bestQuality;
}

double* CRandomSearch::nextValid()
{
	CRandom rand(seed);
	double* solution = new double[problem->sizeOfSolution()];

	while (true)
	{
		solution = problem->randomizeSolution(rand);
		if (problem->constrainedSatisfied(solution, NULL))
		{
			return solution;
		}
	}
}