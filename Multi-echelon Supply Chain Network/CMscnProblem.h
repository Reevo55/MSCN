#pragma once
#include "pch.h"
#include "CSolution.h"
#include "CTable.h"
#include "CMatrix.h"
#include "CRandom.h"
#include "constants.h"
#include "CProblem.h"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <fstream>
#include <iostream>




class CMscnProblem : public CProblem
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
	double getQuality(double* pdSolution, int* err);
	double getQualityIfNotGoodImprove(CSolution& input_solution);

	bool constrainedSatisfied(CSolution& input_solution, int* err);
	bool constrainedSatisfied(double* pdSolution, int* err);

	void debuggingPrint();

	int errorCheck(CSolution& input_solution);

	void generateInstances(int iInstanceSeed);
	double* randomizeSolution(CRandom& rand);

	int sizeOfSolution(){return delivers * factories + factories * magazines + shops * magazines;}

	void fixSolutionTable(double* pdSolution, int length);

private:
	
	void saveTableToFile(std::fstream& fs, CTable& table);
	void saveMatrixToFile(std::fstream& fs, CMatrix& matrix);
	void saveMatrixMinMaxToFile(std::fstream& fs, CMatrix& min, CMatrix& max);

	void readTableFromFile(std::fstream& fs, CTable& table);
	void readMatrixFromFile(std::fstream& fs, CMatrix& matrix, int rows, int columns);
	void readMinAndMax(std::fstream& fs, CMatrix& min, CMatrix& max, int rows, int columns);

	double calculateProfit(CSolution& solution);
	double calculateKt(CSolution& solution);
	double calculateKu(CSolution& solution);
	double calculateP(CSolution& solution);

	bool setInMatrix(CMatrix& mat, double value, int i, int j);
	bool setInTable(CTable &vec, double value, int i);
	bool setInVector(std::vector<double> &vec, double value, int i);

	void fixRow(CMatrix& mat, int row);

	int delivers;
	int factories;
	int magazines;
	int shops;

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
