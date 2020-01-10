#include "pch.h"

#include <fstream>
#include <string>
#include <iostream>

#include "CMscnProblem.h"


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
bool CMscnProblem::setInMinXd(double value, int i, int j)
{
	return setInMatrix(xdMin, value, i, j);
}
bool CMscnProblem::setInMaxXd(double value, int i, int j)
{
	return setInMatrix(xdMax, value, i, j);
}
bool CMscnProblem::setInMinXf(double value, int i, int j)
{
	return setInMatrix(xfMin, value, i, j);
}
bool CMscnProblem::setInMaxXf(double value, int i, int j)
{
	return setInMatrix(xfMax, value, i, j);
}
bool CMscnProblem::setInMinXm(double value, int i, int j)
{
	return setInMatrix(xmMin, value, i, j);
}
bool CMscnProblem::setInMaxXm(double value, int i, int j)
{
	return setInMatrix(xmMax, value, i, j);
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
	std::fstream file(fileName);

	std::string trash;
	char garbage;

	file >> garbage;
	file >> delivers;
	file >> garbage;
	file >> factories;
	file >> garbage;
	file >> magazines;
	file >> garbage;
	file >> shops;

	std::getline(file, trash);
	std::getline(file, trash);


	readTableFromFile(file, sd);

	std::getline(file, trash);

	readTableFromFile(file, sf);

	std::getline(file, trash);

	readTableFromFile(file, sm);

	std::getline(file, trash);

	readTableFromFile(file, ss);

	std::getline(file, trash);

	readMatrixFromFile(file, cd, delivers, factories);
	
	std::getline(file, trash);

	readMatrixFromFile(file, cf, factories, magazines);

	std::getline(file, trash);

	readMatrixFromFile(file, cm, magazines, shops);

	std::getline(file, trash);

	readTableFromFile(file, ud);

	std::getline(file, trash);

	readTableFromFile(file, uf);

	std::getline(file, trash);

	readTableFromFile(file, um);

	std::getline(file, trash);

	readTableFromFile(file, ps);

	std::getline(file,trash);

	readMinAndMax(file, xdMin, xdMax, delivers, factories);

	std::getline(file, trash);

	readMinAndMax(file, xfMin, xfMax, factories, magazines);

	std::getline(file, trash);

	readMinAndMax(file, xmMin, xmMax, magazines, shops);


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
	file << "sm \n";
	saveTableToFile(file, sm);
	file << "\n";
	file << "ss \n";
	saveTableToFile(file, ss);
	file << "\n";
	file << "cd \n";
	saveMatrixToFile(file, cd);
	file << "\n";
	file << "cf \n";
	saveMatrixToFile(file, cf);
	file << "\n";
	file << "cm \n";
	saveMatrixToFile(file, cm);
	file << "\n";
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

double CMscnProblem::getQuality(CSolution& input_solution, int * err)
{
	if (err != NULL)
	{
		*err = errorCheck(input_solution);
		if (*err != 0) return false;
	}

	solution = input_solution;

	return calculateProfit();
}


double CMscnProblem::getQuality(int * err)
{
	if (err != NULL)
	{
		*err = errorCheck(solution);
		if (*err != 0) return false;
	}

	return calculateProfit();
}

bool CMscnProblem::constrainedSatisfied(CSolution& input_solution, int * err)
{
	if (err != NULL)
	{
		*err = errorCheck(input_solution);
		if (*err != 0) return false;
	}

	solution = input_solution;

	for (int i = 0; i < delivers; i++)
	{
		if (solution.getXd().sumInRow(i) > sd.getValue(i)) return false;
	}

	for (int i = 0; i < factories; ++i)
	{
		if (solution.getXf().sumInRow(i) > sf.getValue(i)) return false;
	}

	for (int i = 0; i < magazines; ++i)
	{
		if (solution.getXm().sumInRow(i) > sm.getValue(i)) return false;
	}

	for (int i = 0; i < shops; ++i)
	{
		if (solution.getXm().sumInColumn(i) > ss.getValue(i)) return false;
	}

	for (int i = 0; i < factories; ++i)
	{
		if (solution.getXd().sumInColumn(i) > solution.getXf().sumInRow(i)) return false;
	}

	for (int i = 0; i < magazines; ++i)
	{
		if (solution.getXd().sumInColumn(i) > solution.getXm().sumInRow(i)) return false;
	}

	return true;
}


bool CMscnProblem::constrainedSatisfied(int * err)
{
	if (err != NULL)
	{
		*err = errorCheck(solution);
		if (*err != 0) return false;
	}

	for (int i = 0; i < delivers; i++)
	{
		if (solution.getXd().sumInRow(i) > sd.getValue(i)) return false;
	}

	for (int i = 0; i < factories; ++i)
	{
		if (solution.getXf().sumInRow(i) > sf.getValue(i)) return false;
	}

	for (int i = 0; i < magazines; ++i)
	{
		if (solution.getXm().sumInRow(i) > sm.getValue(i)) return false;
	}

	for (int i = 0; i < shops; ++i)
	{
		if (solution.getXm().sumInColumn(i) > ss.getValue(i)) return false;
	}

	for (int i = 0; i < factories; ++i)
	{
		if (solution.getXd().sumInColumn(i) > solution.getXf().sumInRow(i)) return false;
	}

	for (int i = 0; i < magazines; ++i)
	{
		if (solution.getXd().sumInColumn(i) > solution.getXm().sumInRow(i)) return false;
	}

	return true;
}
double CMscnProblem::calculateProfit()
{
	return calculateP() - calculateKu() - calculateKt();
}

void CMscnProblem::debuggingPrint()
{
	std::cout << "D ";
	std::cout << delivers << "\n";
	std::cout << "F ";
	std::cout << factories << "\n";
	std::cout << "M ";
	std::cout << magazines << "\n";
	std::cout << "S ";
	std::cout << shops << "\n";

	std::cout << "cd" << "\n";
	cd.print();
	std::cout << "cf" << "\n";
	cf.print();
	std::cout << "cm" << "\n";
	cm.print();

	/*std::cout << "xf" << "\n";
	solution.getXf().print();
	std::cout << "xm" << "\n";
	solution.getXm().print();
	std::cout << "xd" << "\n";
	solution.getXd().print();*/

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

int CMscnProblem::errorCheck(CSolution& input_solution)
{
	if (input_solution.getXd().getMaxSize() != delivers * factories) return -1;
	if (input_solution.getXf().getMaxSize() != factories * magazines) return -1;
	if (input_solution.getXm().getMaxSize() != magazines * shops) return -1;
	
	return 0;
}

void CMscnProblem::generateInstances(int iInstanceSeed)
{
	CRandom random(iInstanceSeed);
	
	ud.randomizeInTable(random, DEF_MSCN_RAND_U_MIN, DEF_MSCN_RAND_U_MAX);
	uf.randomizeInTable(random, DEF_MSCN_RAND_U_MIN, DEF_MSCN_RAND_U_MAX);
	um.randomizeInTable(random, DEF_MSCN_RAND_U_MIN, DEF_MSCN_RAND_U_MAX);
	sd.randomizeInTable(random, DEF_MSCN_RAND_S_MIN, DEF_MSCN_RAND_S_MIN);
	sf.randomizeInTable(random, DEF_MSCN_RAND_S_MIN, DEF_MSCN_RAND_S_MIN);
	sm.randomizeInTable(random, DEF_MSCN_RAND_S_MIN, DEF_MSCN_RAND_S_MIN);
	ss.randomizeInTable(random, DEF_MSCN_RAND_S_MIN, DEF_MSCN_RAND_S_MIN);
	cd.randomizeInMatrix(random, DEF_MSCN_RAND_C_MIN, DEF_MSCN_RAND_C_MAX);
	cf.randomizeInMatrix(random, DEF_MSCN_RAND_C_MIN, DEF_MSCN_RAND_C_MAX);
	cm.randomizeInMatrix(random, DEF_MSCN_RAND_C_MIN, DEF_MSCN_RAND_C_MAX);

}

void CMscnProblem::saveTableToFile(std::fstream & fs, CTable & table)
{
	for (int i = 0; i < table.getTableLen(); i++)
	{
		fs << table.getValue(i) << " ";
	}
}

void CMscnProblem::saveMatrixToFile(std::fstream & fs, CMatrix & matrix)
{
	for (int ii = 0; ii < matrix.getRows(); ii++)
	{
		for (int jj = 0; jj < matrix.getColumns(); jj++)
		{
			fs << matrix.get(ii, jj) << " ";
		}
	}
}

void CMscnProblem::readTableFromFile(std::fstream & fs, CTable & table)
{
	std::vector<double> vector;

	std::string str;

	std::getline(fs, str);

	std::istringstream ss(str);
	double num;
	while (ss >> num)
	{
		vector.push_back(num);
	}


	table.setNewSize(vector.size());
	for (int i = 0; i < table.getTableLen(); i++)
	{
		table.setValue(i, vector[i]);
	}
}

void CMscnProblem::readMatrixFromFile(std::fstream & fs, CMatrix & matrix, int rows, int columns)
{
	std::vector<double> vector;

	std::string str;

	std::getline(fs, str);

	std::istringstream ss(str);
	double num;
	while (ss >> num)
	{
		vector.push_back(num);
	}
	if (columns*rows != vector.size()) return;

	matrix.resize(rows, columns);
	int helpVec = 0;


	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			matrix.set(vector[helpVec], i, j);
			helpVec++;
		}
}

void CMscnProblem::readMinAndMax(std::fstream & fs, CMatrix & min, CMatrix & max, int rows, int columns)
{
	std::vector<double> vector;

	std::string str;

	std::getline(fs, str);

	std::istringstream ss(str);
	double num;
	while (ss >> num)
	{
		vector.push_back(num);
	}
	if (columns*rows * 2 != vector.size()) return;

	min.resize(rows, columns);
	max.resize(rows, columns);

	int helpVec = 0;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			min.set(vector[helpVec], i, j);
			helpVec++;
			max.set(vector[helpVec], i, j);
		}
}

double CMscnProblem::calculateKt()
{
	double resultDelivery = 0;

	for (int i = 0; i < delivers; i++)
		for (int j = 0; j < factories; j++)
			resultDelivery += cd.get(i, j) * solution.getXd().get(j, i);

	double resultMagazine = 0;

	for (int i = 0; i < factories; i++)
		for (int j = 0; j < magazines; j++)
			resultMagazine += cf.get(i, j) * solution.getXf().get(j, i);

	double resultShop = 0;

	for (int i = 0; i < magazines; i++)
		for (int j = 0; j < shops; j++)
			resultShop += cm.get(i, j) * solution.getXm().get(j, i);

	return resultDelivery + resultMagazine + resultShop;
}

double CMscnProblem::calculateKu()
{
	double resultDelivery = 0;

	for (int i = 0; i < delivers; i++)
		for (int j = 0; j < factories; j++)
			if (solution.getXd().sumInRow(j) > 0) resultDelivery += ud.getValue(i);

	double resultMagazine = 0;

	for (int i = 0; i < factories; i++)
		for (int j = 0; j < magazines; j++)
			if (solution.getXf().sumInRow(j) > 0) resultMagazine += uf.getValue(i);

	double resultShop = 0;


	for (int i = 0; i < magazines; i++)
		for (int j = 0; j < shops; j++)
			if (solution.getXm().sumInRow(j) > 0) resultMagazine += um.getValue(i);

	return resultDelivery + resultMagazine + resultShop;
}

double CMscnProblem::calculateP()
{
	double result = 0;
	for (int i = 0; i < magazines; i++)
		for (int j = 0; j < shops; j++)
			result += ps.getValue(j) * solution.getXm().get(i, j);
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


void CMscnProblem::randomizeSolution(CRandom& rand)
{
	for (int i = 0; i < solution.getXd().getRows(); i++)
		for (int j = 0; j < solution.getXd().getColumns(); j++)
		{
			solution.setInXd(rand.nextDouble(xdMin.get(i,j), xdMax.get(i,j)), i, j);
		}

	for (int i = 0; i < solution.getXf().getRows(); i++)
		for (int j = 0; j < solution.getXf().getColumns(); j++)
		{
			solution.setInXf(rand.nextDouble(xfMin.get(i, j), xfMax.get(i, j)), i, j);
		}

	for (int i = 0; i < solution.getXm().getRows(); i++)
		for (int j = 0; j < solution.getXm().getColumns(); j++)
		{
			solution.setInXm(rand.nextDouble(xmMin.get(i, j), xmMax.get(i, j)), i, j);
		}
}

bool CMscnProblem::checkIfMinMaxIsRight(CSolution& solution)
{
	for(int i=0; i < delivers; i++)
		for (int j = 0; j < factories; j++)
		{
			if (!(xdMin.get(i, j) < solution.getXd().get(i, j) < xdMax.get(i, j)))
				return false;
		}
	for (int i = 0; i < factories; i++)
		for (int j = 0; j < magazines; j++)
		{
			if (!(xfMin.get(i, j) < solution.getXf().get(i, j) < xfMax.get(i, j)))
				return false;
		}
	for (int i = 0; i < magazines; i++)
		for (int j = 0; j < shops; j++)
		{
			if (!(xmMin.get(i, j) < solution.getXm().get(i, j) < xmMax.get(i, j)))
				return false;
		}

	return true;
}
