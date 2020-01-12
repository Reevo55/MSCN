#pragma once
#include "pch.h"
#include "CRandomSearch.h"


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
				std::cout << counter << ". Teraz wydajno�� wynosi�a: " << current << ", najlepsze rozwi�zanie to: " << bestQuality << ". \n";
				std::cout << "\n";
				problem->getSolution().saveToFile("readSolution.txt");
			}
			else
			{
				std::cout << "\n";
				std::cout << counter << ". Teraz wydajno�� wynosi�a: " << current << ", najlepsze rozwi�zanie to: " << bestQuality << ". \n";
				std::cout << "\n";
			}
		}
		else
		{
			std::cout << counter << ". Teraz wydajno�� wynosi�a: " << current << ", ale rozwi�zanie nie jest prawid�owe, najlepsze rozwi�zanie to: " << bestQuality << ". \n";
		}

		actualTime = time(NULL);
		counter++;
	}
	std::cout << " KONIEC! NAJLEPSZA WARTO�� TO: " << bestQuality << "\n";
	return bestQuality;
}

CSolution CRandomSearch::nextValid()
{
	CRandom rand(seed);

	while (true)
	{
		problem->randomizeSolution(rand);
		if (problem->constrainedSatisfied(NULL))
		{
			CSolution answer;
			answer = problem->getSolution();
			return answer;
		}
	}
}