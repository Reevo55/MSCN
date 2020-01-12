#pragma once
#include "pch.h"
#include <iostream>
#include "CMscnProblem.h"
#include "CDiffEvol.h"
#include "CSolution.h"
#include "CRandomSearch.h"

void test()
{
	/*const int testDCount = 1;
const int testFCount = 1;
const int testMCount = 1;
const int testSCount = 1;

problem.setDelivers(testDCount);
problem.setFactories(testFCount);
problem.setMagazines(testMCount);
problem.setShops(testSCount);

for (int i = 0; i < testDCount; i++)
	for (int j = 0; j < testFCount; j++)
		problem.setInCd(i*testDCount + j, j, i);

for (int i = 0; i < testFCount; i++)
	for (int j = 0; j < testMCount; j++)
		problem.setInCf(i*testFCount + j, i, j);

for (int i = 0; i < testMCount; i++)
	for (int j = 0; j < testSCount; j++)
		problem.setInCm(i*testMCount + j, i, j);

problem.setInSd(10, 0);
problem.setInSf(10, 0);
problem.setInSm(10, 0);
problem.setInSs(10, 0);

problem.setInCd(5, 0, 0);
problem.setInCf(4, 0, 0);
problem.setInCm(3, 0, 0);

problem.setInPs(1000, 0);
problem.setInUd(100, 0);
problem.setInUf(100, 0);
problem.setInUm(100, 0);



double * solution = new double[3]{ 10, 10, 10 };*/


	int* err = new int;


	CMscnProblem* problem = new CMscnProblem();

	CSolution csolution;
	csolution.readFromFile("readSolution.txt");

	(*problem).readFromFile("readProblem.txt");

	//(*problem).generateInstances(NULL);
	//(*problem).saveToFile("readProblem.txt");


	std::cout << "Quality: " << (*problem).getQuality(csolution, err) << "\n";
	std::cout << "Constrained satisfied: " << (*problem).constrainedSatisfied(csolution, err) << "\n";


	std::cout << *err << "\n";

	/*
	int timeInSeconds = 100;
	randomSearch.randomSearch(timeInSeconds);*/

	int time = 20;

	int populationSize = 100;
	double crosProb = 0.2;
	double diffWeight = 0.5;

	CDiffEvol diff(populationSize);

	std::cout<<"Najlepszy wynik to: " << diff.startDifferentialEvolution(problem, crosProb, diffWeight, time);
	

}

int main()
{
	test();
}
