#include "pch.h"
#include "CMscnProblem.h"
#include "CTable.h"
#include "CMatrix.h"
#include <fstream>
#include <string>
#include <iostream>


#define NUMBER_OF_SUPPLIERS 2
#define NUMBER_OF_FACTORIES 1
#define NUMBER_OF_DESTRIBUTION_CENTERS 3
#define NUMBER_OF_SHOPS 4

CMscnProblem::CMscnProblem()
{
	delivers = NUMBER_OF_SUPPLIERS;
	factories = NUMBER_OF_FACTORIES;
	magazines = NUMBER_OF_DESTRIBUTION_CENTERS;
	shops = NUMBER_OF_SHOPS;

	cd = CMatrix(factories, delivers);
	cf = CMatrix(magazines, factories);
	cm = CMatrix(shops, magazines);

	sd.setNewSize(delivers);
	ud.setNewSize(delivers);
	sf.setNewSize(factories);
	uf.setNewSize(factories);
	sm.setNewSize(magazines);
	um.setNewSize(magazines);
	ss.setNewSize(shops);
	ps.setNewSize(shops);
}


bool CMscnProblem::setDelivers(int amount)
{
	if (amount < 0) return false;

	delivers = amount;
	cd.resize(factories, delivers);
	sd.setNewSize(delivers);
	ud.setNewSize(delivers);
	return true;
}
bool CMscnProblem::setFactories(int amount)
{
	if (amount < 0) return false;

	factories = amount;
	cd.resize(factories, delivers);
	cf.resize(magazines, factories);
	sf.setNewSize(factories);
	uf.setNewSize(factories);
	return true;
}
bool CMscnProblem::setMagazines(int amount)
{
	if (amount < 0) return false;

	magazines = amount;
	cf.resize(magazines, factories);
	cm.resize(shops, magazines);
	sm.setNewSize(magazines);
	um.setNewSize(magazines);
	return true;
}
bool CMscnProblem::setShops(int amount)
{
	if (amount < 0) return false;

	shops = amount;
	cm.resize(shops, magazines);
	ss.setNewSize(shops);
	ps.setNewSize(shops);
	return true;
}

bool CMscnProblem::setInCd(double value, int i, int j)
{
	return setInMatrix(cd, value, i, j);
}
bool CMscnProblem::setInCf(double value, int i, int j)
{
	return setInMatrix(cf, value, i, j);
}
bool CMscnProblem::setInCm(double value, int i, int j)
{
	return setInMatrix(cm, value, i, j);
}

bool CMscnProblem::setInSd(double value, int i)
{
	return setInTable(sd, value, i);
}
bool CMscnProblem::setInSf(double value, int i)
{
	return setInTable(sf, value, i);
}
bool CMscnProblem::setInSm(double value, int i)
{
	return setInTable(sm, value, i);
}
bool CMscnProblem::setInSs(double value, int i)
{
	return setInTable(ss, value, i);
}
bool CMscnProblem::setInUd(double value, int i)
{
	return setInTable(ud, value, i);
}
bool CMscnProblem::setInUf(double value, int i)
{
	return setInTable(uf, value, i);
}
bool CMscnProblem::setInUm(double value, int i)
{
	return setInTable(um, value, i);
}
bool CMscnProblem::setInPs(double value, int i)
{
	return setInTable(ps, value, i);
}
void CMscnProblem::readFromFile(const char * fileName)
{
	std::ifstream file(fileName);

	char trash;

}


void CMscnProblem::saveToFile(const char * fileName)
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
	file << "sd \n";
	saveTableToFile(file, sd);
	file << "\n";
	file << "sf \n";
	saveTableToFile(file, sf);
	file << "\n";
	file << "ss \n";
	saveTableToFile(file, ss);
	file << "\n";
	file << "cd \n";
	saveMatrixToFile(file, cd);
	file << "cf \n";
	saveMatrixToFile(file, cf);
	file << "cm \n";
	saveMatrixToFile(file, cm);
	file << "ud \n";
	saveTableToFile(file, ud);
	file << "\n";
	file << "uf \n";
	saveTableToFile(file, uf);
	file << "\n";
	file << "um \n";
	saveTableToFile(file, um);
	file << "\n";
	file << "p \n";
	saveTableToFile(file, ps);

	file.close();
}

double CMscnProblem::getQuality(double * pdSolution, int tableLen, int * err)
{
	*err = errorCheck(pdSolution, tableLen);
	if (*err != 0) return false;

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

	return calculateProfit();
}

bool CMscnProblem::constrainedSatisfied(double * pdSolution, int tableLen,int * err)
{
	*err = errorCheck(pdSolution,tableLen);
	if (*err != 0) return false;

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


	for (int i = 0; i < delivers; i++)
	{
		if (xd.sumInRow(i) > sd.getValue(i)) return false;
	}

	for (int i = 0; i < factories; ++i)
	{
		if (xf.sumInRow(i) > sf.getValue(i)) return false;
	}

	for (int i = 0; i < magazines; ++i)
	{
		if (xm.sumInRow(i) > sm.getValue(i)) return false;
	}

	for (int i = 0; i < shops; ++i)
	{
		if (xm.sumInColumn(i) > ss.getValue(i)) return false;
	}

	for (int i = 0; i < factories; ++i)
	{
		if (xd.sumInColumn(i) > xf.sumInRow(i)) return false;
	}

	for (int i = 0; i < magazines; ++i)
	{
		if (xd.sumInColumn(i) > xm.sumInRow(i)) return false;
	}

	return true;
}

double CMscnProblem::calculateProfit()
{
	return calculateP() - calculateKu() - calculateKt();
}

bool CMscnProblem::readFile(char* fileName)
{	
	return true;
}

void CMscnProblem::debuggingPrint()
{
	std::cout << "cd" << "\n";
	cd.print();
	std::cout << "cf" << "\n";
	cf.print();
	std::cout << "cm" << "\n";
	cm.print();

	std::cout << "xf" << "\n";
	xf.print();
	std::cout << "xm" << "\n";
	xm.print();
	std::cout << "xd" << "\n";
	xd.print();

	std::cout << "cd" << "\n";
	sd.printTable();
	std::cout << "sf" << "\n";
	sf.printTable();
	std::cout << "sm" << "\n";
	sm.printTable();
	std::cout << "ss" << "\n";
	ss.printTable();
	std::cout << "ud" << "\n";
	ud.printTable();
	std::cout << "uf" << "\n";
	uf.printTable();
	std::cout << "um" << "\n";
	um.printTable();
	std::cout << "ps" << "\n";
	ps.printTable();
}

int CMscnProblem::errorCheck(double * pdSolution, int tableLen)
{
	int size = delivers * factories + factories * magazines + magazines * shops;
	if (tableLen != size) return -1;
	else if (pdSolution == NULL) return -2;
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (pdSolution[i] < 0) return -3;
		}
		return 0;
	}
}

double CMscnProblem::calculateKt()
{
	double resultDelivery = 0;

	for (int i = 0; i < delivers; i++)
		for (int j = 0; j < factories; j++)
			resultDelivery += cd.get(i, j) * xd.get(j, i);

	double resultMagazine = 0;

	for (int i = 0; i < factories; i++)
		for (int j = 0; j < magazines; j++)
			resultMagazine += cf.get(i, j) * xf.get(j, i);

	double resultShop = 0;

	for (int i = 0; i < magazines; i++)
		for (int j = 0; j < shops; j++)
			resultShop += cm.get(i, j) * xm.get(j, i);

	return resultDelivery + resultMagazine + resultShop;
}

double CMscnProblem::calculateKu()
{
	double resultDelivery = 0;

	for (int i = 0; i < delivers; i++)
		for (int j = 0; j < factories; j++)
			if (xd.sumInRow(j) > 0) resultDelivery += ud.getValue(i);

	double resultMagazine = 0;

	for (int i = 0; i < factories; i++)
		for (int j = 0; j < magazines; j++)
			if (xf.sumInRow(j) > 0) resultMagazine += uf.getValue(i);

	double resultShop = 0;


	for (int i = 0; i < magazines; i++)
		for (int j = 0; j < shops; j++)
			if (xm.sumInRow(j) > 0) resultMagazine += um.getValue(i);

	return resultDelivery + resultMagazine + resultShop;
}

double CMscnProblem::calculateP()
{
	double result = 0;
	for (int i = 0; i < magazines; i++)
		for (int j = 0; j < shops; j++)
			result += ps.getValue(j) * xm.get(i, j);
	return result;
}

bool CMscnProblem::setInMatrix(CMatrix &mat, double value, int i, int j)
{
	if (value < 0 || !mat.checkRowsAndColumns(i,j)) return false;

	mat.set(value, i, j);
	return true;

}
bool CMscnProblem::setInTable(CTable &table, double value, int i)
{
	if (value < 0 || table.getTableLen() < i) return false;

	table.setValue(i, value);

	return true;

}

bool CMscnProblem::setInVector(std::vector<double> &vec, double value, int i)
{
	if (value < 0) return false;

	vec[i] = value;

	return true;

}