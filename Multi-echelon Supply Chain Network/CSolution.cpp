#include "pch.h"
#include "CSolution.h"




bool CSolution::setInXd(double value, int i, int j)
{
	setInMatrix(xd, value, i, j);
	return true;
}

bool CSolution::setInXm(double value, int i, int j)
{
	setInMatrix(xm, value, i, j);
	return true;
}

bool CSolution::setInXf(double value, int i, int j)
{
	setInMatrix(xf, value, i, j);
	return true;
}

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

CSolution CSolution::readFromDoubleTable(double * pdSolution, int delivers, int factories, int shops, int magazines)
{
	CSolution help;
	help.delivers = delivers;
	help.factories = factories;
	help.shops = shops;
	help.magazines = magazines;

	help.xd.resize(factories, delivers);
	help.xf.resize(magazines, factories);
	help.xm.resize(shops, magazines);
		

	for (int i = 0; i < delivers; ++i)
		for (int j = 0; j < factories; ++j)
			help.xd.set(pdSolution[i*factories + j], i, j);

	int xdSize = xd.getMaxSize();

	for (int i = 0; i < factories; ++i)
		for (int j = 0; j < magazines; ++j)
			help.xf.set(pdSolution[xdSize + i * magazines + j], i, j);

	int xfSize = xf.getMaxSize();

	for (int i = 0; i < magazines; ++i)
		for (int j = 0; j < shops; ++j)
			help.xm.set(pdSolution[xdSize + xfSize + i * shops + j], i, j);

	return help;
}
double * CSolution::toDoubleTable()
{
	int size = delivers * factories + factories * magazines + shops * magazines;
	double * table = new double[size];

	int k = 0;

	for (int i = 0; i < delivers; i++)
		for (int j = 0; j < factories; j++)
		{
			table[k] = xd.get(i, j);
			k++;
		}

	for (int i = 0; i < factories; i++)
		for (int j = 0; j < magazines; j++)
		{
			table[k] = xf.get(i, j);
			k++;
		}

	for (int i = 0; i < magazines; i++)
		for (int j = 0; j < shops; j++)
		{
			table[k] = xm.get(i, j);
			k++;
		}

	return table;
}
void CSolution::saveToFile(const char * fileName)
{
	std::fstream file(fileName);

	file.flush();

	file << "D ";
	file << delivers << "\n";
	file << "F ";
	file << factories << "\n";
	file << "M ";
	file << magazines << "\n";
	file << "S ";
	file << shops << "\n";
	file << "xd \n";
	saveMatrixToFile(file, xd);
	file << "\n";
	file << "xf \n";
	saveMatrixToFile(file, xf);
	file << "\n";
	file << "xm \n";
	saveMatrixToFile(file, xm);


	file.close();
}
