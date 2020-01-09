#pragma once
#include "pch.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <fstream>

#include "CSolution.h"
#include "CTable.h"
#include "CMatrix.h"
#include "CRandom.h"

class CMscnProblem
{
public:
	CMscnProblem();

	bool setDelivers(int amount);
	bool setFactories(int amount);
	bool setMagazines(int amount);
	bool setShops(int amount);

	bool setInCd(double value, int i, int j);
	bool setInCf(double value, int i, int j);
	bool setInCm(double value, int i, int j);
	bool setInMinXd(double value, int i, int j);
	bool setInMaxXd(double value, int i, int j);
	bool setInMinXf(double value, int i, int j);
	bool setInMaxXf(double value, int i, int j);
	bool setInMinXm(double value, int i, int j);
	bool setInMaxXm(double value, int i, int j);


	bool setInSd(double value, int i);
	bool setInSf(double value, int i);
	bool setInSm(double value, int i);
	bool setInSs(double value, int i);
	bool setInUd(double value, int i);
	bool setInUf(double value, int i);
	bool setInUm(double value, int i);
	bool setInPs(double value, int i);

	bool checkIfMinMaxIsRight(CSolution& solution);


	void readFromFile(const char * fileName);

	void saveToFile(const char* fileName);
	
	double getQuality(CSolution& input_solution, int* err);
	bool constrainedSatisfied(CSolution& input_solution, int* err);

	void debuggingPrint();

	int errorCheck(CSolution& input_solution);

	void generateInstances(int iInstanceSeed);

private:
	
	void saveTableToFile(std::fstream& fs, CTable& table);
	void saveMatrixToFile(std::fstream& fs, CMatrix& matrix);
	void readTableFromFile(std::fstream& fs, CTable& table);
	void readMatrixFromFile(std::fstream& fs, CMatrix& matrix, int rows, int columns);
	void readMinAndMax(std::fstream& fs, CMatrix& min, CMatrix& max, int rows, int columns);

	double calculateProfit();
	double calculateKt();
	double calculateKu();
	double calculateP();

	bool setInMatrix(CMatrix& mat, double value, int i, int j);
	bool setInTable(CTable &vec, double value, int i);
	bool setInVector(std::vector<double> &vec, double value, int i);

	void randomizeInTable(CTable& tab, CRandom& random, double min, double max);
	void randomizeInMatrix(CMatrix& mat, CRandom& random, double min, double max);

	int delivers;
	int factories;
	int magazines;
	int shops;

	CSolution solution;

	CMatrix cd;
	CMatrix cf;
	CMatrix cm;

	CTable sd;
	CTable sf;
	CTable sm;
	CTable ss;
	CTable ud;
	CTable uf;
	CTable um;
	CTable ps;

	CMatrix xdMin;
	CMatrix xdMax;
	CMatrix xfMin;
	CMatrix xfMax;
	CMatrix xmMin;
	CMatrix xmMax;

	
};
