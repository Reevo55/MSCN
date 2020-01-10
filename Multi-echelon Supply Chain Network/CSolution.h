#pragma once
#include "pch.h"

#include "CMatrix.h"
#include "CTable.h"

#include <fstream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


class CSolution {
public:
	CSolution() { 
		xd = CMatrix();
		xf = CMatrix();
		xm = CMatrix();
		delivers = 0;
		factories = 0;
		magazines = 0;
		shops = 0;
	};

	CMatrix& getXd() { return xd; }
	CMatrix& getXf() { return xf; }
	CMatrix& getXm() { return xm; }

	bool setInXd(double value, int i, int j);
	bool setInXf(double value, int i, int j);
	bool setInXm(double value, int i, int j);

	void print() { xd.print(); xm.print(); xf.print(); }

	void readFromFile(const char* fileName);
	void readFromDoubleTable(double* pdSolution);

	void saveToFile(const char * fileName);
private:
	void saveMatrixToFile(std::fstream & fs, CMatrix & matrix)
	{
		for (int ii = 0; ii < matrix.getRows(); ii++)
		{
			for (int jj = 0; jj < matrix.getColumns(); jj++)
			{
				fs << matrix.get(ii, jj) << " ";
			}
		}
	}
	bool setInMatrix(CMatrix& mat, double value, int i, int j) 
	{
		if (value < 0 || !mat.checkRowsAndColumns(i, j)) return false;

		mat.set(value, i, j);
		return true;
	}


	void readMatrixFromFile(std::fstream& fs, CMatrix& matrix, int rows, int columns)
	{
		std::vector<double> vector;

		std::string str;

		std::getline(fs, str);
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

	int delivers;
	int factories;
	int magazines;
	int shops;

	CMatrix xd;
	CMatrix xf;
	CMatrix xm;

};