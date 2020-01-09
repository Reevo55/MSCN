#pragma once
#include "pch.h"
#include "CRandomSearch.h"

int CRandomSearch::randomSearch(int howMuchTimeInSeconds, CSolution& solution)
{
	int actualTime = time(NULL);
	int endingTime = actualTime + howMuchTimeInSeconds;

	int bestQuality = 0;
	int counter = 0;

	while (endingTime > actualTime)
	{
		problem->generateInstances(rand());

		if (problem->constrainedSatisfied(solution, NULL))
		{
			if (bestQuality < problem->getQuality(solution, NULL))
			{
				bestQuality = problem->getQuality(solution, NULL);

				std::cout << counter << ". Teraz wydajnoœæ wynosi³a: " << problem->getQuality(solution, NULL) << ", najlepsze rozwi¹zanie to: " << bestQuality << ". \n";
			}
		}
		else
		{
			std::cout << counter << ". Teraz wydajnoœæ wynosi³a: " << problem->getQuality(solution, NULL) << ", ale rozwi¹zanie nie jest prawid³owe, najlepsze rozwi¹zanie to: " << bestQuality << ". \n";
		}
		actualTime = time(NULL);
		counter++;

	}
	std::cout << " KONIEC! NAJLEPSZA WARTOŒÆ TO: " << bestQuality << "\n";
	return bestQuality;
}