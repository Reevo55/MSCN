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

				std::cout << counter << ". Teraz wydajno�� wynosi�a: " << problem->getQuality(solution, NULL) << ", najlepsze rozwi�zanie to: " << bestQuality << ". \n";
			}
		}
		else
		{
			std::cout << counter << ". Teraz wydajno�� wynosi�a: " << problem->getQuality(solution, NULL) << ", ale rozwi�zanie nie jest prawid�owe, najlepsze rozwi�zanie to: " << bestQuality << ". \n";
		}
		actualTime = time(NULL);
		counter++;

	}
	std::cout << " KONIEC! NAJLEPSZA WARTO�� TO: " << bestQuality << "\n";
	return bestQuality;
}