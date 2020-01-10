#pragma once
#include "pch.h"
#include "CRandomSearch.h"
#include "CRandom.h"

int CRandomSearch::randomSearch(int howMuchTimeInSeconds)
{
	int actualTime = time(NULL);
	int endingTime = actualTime + howMuchTimeInSeconds;

	int bestQuality = 0;
	int counter = 0;
	int current = 0;

	CRandom rand;

	while (endingTime > actualTime)
	{
		problem->randomizeSolution(rand);
		current = problem->getQuality(NULL);

		if (problem->constrainedSatisfied(NULL))
		{
			if (bestQuality < current)
			{
				bestQuality = current;
				std::cout << "\n";
				std::cout << counter << ". Teraz wydajność wynosiła: " << current << ", najlepsze rozwiązanie to: " << bestQuality << ". \n";
				std::cout << "\n";
				problem->getSolution().saveToFile("readSolution.txt");
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

		actualTime = time(NULL);
		counter++;
	}
	std::cout << " KONIEC! NAJLEPSZA WARTOŚĆ TO: " << bestQuality << "\n";
	return bestQuality;
}