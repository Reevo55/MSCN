#include "pch.h"
#include <iostream>
#include "CMatrix.h"
#include "CTable.h"
#include "CMscnProblem.h"

void test()
{
	CMscnProblem problem;

	const int testDCount = 1;
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

	int err;
	double * solution = new double[3]{ 10, 10, 10 };

	std::cout << "\n Quality : " << problem.getQuality(solution, 3, &err);
	std::cout << "\n Constrainits satisfied: " << problem.constrainedSatisfied(solution, 3, &err) << "\n";

	problem.saveToFile("test.txt");

	problem.debuggingPrint();
}

int main()
{
	test();
}
