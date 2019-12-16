#include "pch.h"
#include <vector>
#include "CMatrix.h"
#include "CTable.h"
#include <fstream>

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

	bool setInSd(double value, int i);
	bool setInSf(double value, int i);
	bool setInSm(double value, int i);
	bool setInSs(double value, int i);
	bool setInUd(double value, int i);
	bool setInUf(double value, int i);
	bool setInUm(double value, int i);
	bool setInPs(double value, int i);

	void saveToFile(const char* fileName);
	
	double getQuality(double* pdSolution, int tableLen, int* err);
	bool constrainedSatisfied(double* pdSolution, int tableLen, int* err);

	bool readFile(char* fileName);

	void debuggingPrint();

	int errorCheck(double* pdSolution, int tableLen);
private:
	
	void saveTableToFile(std::fstream& fs, CTable& table)
	{
		for (int i = 0; i < table.getTableLen(); i++)
		{
			fs << table.getValue(i) << ";";
		}
	}
	void saveMatrixToFile(std::fstream& fs, CMatrix& matrix)
	{
		for (int ii = 0; ii < matrix.getRows(); ii++)
		{
			for (int jj = 0; jj < matrix.getColumns(); jj++)
			{
				fs << matrix.get(ii, jj) << ";";
			}
			fs << "\n";
		}
	}

	double calculateProfit();
	double calculateKt();
	double calculateKu();
	double calculateP();
	bool setInMatrix(CMatrix& mat, double value, int i, int j);
	bool setInTable(CTable &vec, double value, int i);
	bool setInVector(std::vector<double> &vec, double value, int i);

	int delivers;
	int factories;
	int magazines;
	int shops;

	CMatrix cd;
	CMatrix cf;
	CMatrix cm;

	CMatrix xd;
	CMatrix xf;
	CMatrix xm;

	CTable sd;
	CTable sf;
	CTable sm;
	CTable ss;
	CTable ud;
	CTable uf;
	CTable um;
	CTable ps;
};