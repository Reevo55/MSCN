#include "pch.h"
#include "CDiffEvol.h"

double CDiffEvol::startDifferentialEvolution(CMscnProblem * problem, double differenceWeight, double crossProbability, int howMuchTimeInSeconds)
{
	int actualTime = time(NULL);
	int endingTime = actualTime + howMuchTimeInSeconds;
	int* err = 0;
	CRandom rand;
	populationQuality = new double[populationNumber];

	initPopulation(problem);

	for (int i = 0; i < populationNumber; i++)
	{
		populationQuality[i] = 0;
	}

	while (endingTime > actualTime)
	{
		for (int i = 0; i < populationNumber; i++)
		{
			int baseIndividualOffSet = rand.nextInt(0, populationNumber - 1);
			int add0IndividualOffSet = rand.nextInt(0, populationNumber - 1);
			int add1InvidualOffSet = rand.nextInt(0, populationNumber - 1);

			if (indexesAreDifferent(i, baseIndividualOffSet, add0IndividualOffSet, add1InvidualOffSet))
			{
				int genotypeSize = problem->sizeOfSolution();

				double *indNew = new double[genotypeSize];

				for (int geneOffSet = 0; geneOffSet < genotypeSize; geneOffSet++)
				{
					if (rand.nextDouble(0, 1) < crossProbability)
					{
						indNew[geneOffSet] = population[baseIndividualOffSet][geneOffSet] +
							differenceWeight * (population[add0IndividualOffSet][geneOffSet] - population[add1InvidualOffSet][geneOffSet]);			
					}
					else indNew[geneOffSet] = population[i][geneOffSet];
				}
				if (problem->constrainedSatisfied(indNew, err))
				{
					double quality = problem->getQuality(indNew, err);
					std::cout << "Constrained satisfied! Quality: " << quality << " \n";

					if (quality > populationQuality[i])
					{
						delete[] population[i];
						population[i] = indNew;
						populationQuality[i] = quality;
					}
					else delete[] indNew;
				}
				else
				{
					std::cout << "Constrained not satisfied!" << "\n";
					delete[] indNew;
				}
			}
		}
		actualTime = time(NULL);
	}

	double best = 0;

	for (int i = 0; i < populationNumber; i++)
	{
		std::cout << i << ". Quality to: " << populationQuality[i] << ".\n";
		if (best < populationQuality[i]) best = populationQuality[i];
	}

	return best;
}

void CDiffEvol::initPopulation(CMscnProblem * problem)
{
	if (populationNumber < 0) return;
	
	CRandomSearch randomSearch(problem);

	population = new double * [populationNumber];

	for (int i = 0; i < populationNumber; i++)
	{
		population[i] = new double[problem->sizeOfSolution()];

		randomSearch.setSeed(rand());
		CSolution solution = randomSearch.nextValid();
		double* helperTable = solution.toDoubleTable();

		for (int j = 0; j < problem->sizeOfSolution(); j++)
		{
			population[i][j] = helperTable[j];
		}

		delete helperTable;
	}
}

bool CDiffEvol::indexesAreDifferent(int first, int second, int third, int fourth)
{
	bool answer = true;

	if (first == second || first == third || first == fourth) answer = false;
	if (second == third || second == fourth) answer = false;
	if (third == fourth) answer = false;

	return answer;
}
