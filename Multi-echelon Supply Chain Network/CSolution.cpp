#include "pch.h"
#include "CSolution.h"
#include "CTable.h"


void CSolution::readFromFile(const char* fileName)
{
	std::fstream file(fileName);

	char garbage;
	
	file >> garbage;
	file >> delivers;
	file >> garbage;
	file >> factories;
	file >> garbage;
	file >> magazines;
	file >> garbage;
	file >> shops;
	
	xd.resize(factories, delivers);
	xf.resize(magazines, factories);
	xm.resize(shops, magazines);


	double helper = 0;

	file >> garbage;
	file >> garbage;

	readMatrixFromFile(file, xd, delivers, factories);

	file >> garbage;
	file >> garbage;

	readMatrixFromFile(file, xf, factories, magazines);


	file >> garbage;
	file >> garbage;

	readMatrixFromFile(file, xm, magazines, shops);

}

void CSolution::readFromDoubleTable(double * pdSolution)
{
	xd.resize(factories, delivers);
	xf.resize(magazines, factories);
	xm.resize(shops, magazines);

	for (int i = 0; i < delivers; i++)
		for (int j = 0; j < factories; j++)
			xd.set(pdSolution[i*factories + j], i, j);

	int xdSize = xd.getMaxSize();

	for (int i = 0; i < factories; i++)
		for (int j = 0; j < magazines; j++)
			xf.set(pdSolution[xdSize + i * magazines + j], i, j);

	int xfSize = xf.getMaxSize();

	for (int i = 0; i < magazines; i++)
		for (int j = 0; j < shops; j++)
			xm.set(pdSolution[xdSize + xfSize + i * shops + j], i, j);
}
