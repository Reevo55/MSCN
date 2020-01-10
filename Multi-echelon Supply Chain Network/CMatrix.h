#pragma once

#include "pch.h"
#include <vector>
#include "CTable.h"
#include "CRandom.h"

class CMatrix
{
public:

	CMatrix() { rows = 2; columns = 2; }

	CMatrix(int rows, int columns)
	{
		resize(rows, columns);
	}

	
	void resize(int rows, int columns)
	{
		this->rows = rows;
		this->columns = columns;
		this->maxSize = rows * columns;
		matrix.setNewSize(maxSize);
	}
	
	bool set(double elem, int rowNr, int columnNr)
	{
		if (rowNr * columnNr > maxSize || rowNr > rows || columnNr > columns) return false;

		int numberInArray = (rowNr * columns) + columnNr;
		matrix.setValue(numberInArray, elem);
		return true;
	}
	
	void fill(double fillingElement)
	{
		for (int i = 0; i < maxSize; i++)
		{
			matrix.setValue(i, fillingElement);
		}
	}
	
	double get(int rowNr, int columnNr)
	{		
		return matrix.getValue((rowNr * columns) + columnNr);
	}

	void print()
	{
		for (int ii = 0; ii < rows; ii++)
		{
			for (int jj = 0; jj < columns; jj++)
			{
				std::cout << get(ii, jj) << " " ;
			}
			std::cout << "\n";
		}
	}

	int getMaxSize() { return maxSize; }
	bool checkRowsAndColumns(int i, int j) { if (i > rows || j > columns) return false; else return true; }

	double sumInRow(int row)
	{
		double res = 0;

		for (int j = 0; j < columns; ++j)
		{
			res += get(row, j);
		}

		return res;

	}

	double sumInColumn(int column)
	{
		double res = 0;

		for (int i = 0; i < columns; ++i)
		{
			res += get(i, column);
		}

		return res;
	}

	int getColumns() { return columns; }
	int getRows() { return rows; }


	void randomizeInMatrix(CRandom& random, double min, double max)
	{
		for (int i = 0; i < this->getRows(); i++)
			for (int j = 0; j < this->getColumns(); j++)
			{
				this->set(random.nextDouble(min, max), i, j);
			}
	}
private:

	int rows;
	int columns;
	int maxSize;
	CTable matrix;
};