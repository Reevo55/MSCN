#ifndef CTABLE_H
#define CTABLE_H

#pragma once

#include "pch.h"
#include <iostream>
#include "CRandom.h"
#include "constants.h"

class CTable
{
public:
	CTable() { name = DEFAULT_TABLE_NAME; table = new double[DEFAULT_TABLE_LENGTH]; tableLen = DEFAULT_TABLE_LENGTH; }
	CTable(std::string name, int tableLen) { this->name = name; table = new double[tableLen]; this->tableLen = tableLen; }
	CTable(const CTable &other);
	CTable(CTable &&other);
	~CTable() { delete table; };
	void setName(std::string name) { this->name = name; };
	bool setNewSize(int tableLen);
	CTable *clone();
	CTable operator-(int other);
	CTable operator+(CTable &other);
	CTable& operator=(const CTable &other);
	CTable& operator=(CTable&& other);
	void printTable();
	double getValue(int offset);
	bool setValue(int offset, double value);
	void fillTable();
	int getTableLen() { return tableLen; }
	void randomizeInTable(CRandom& random, double min, double max)
	{
		for (int i = 0; i < this->getTableLen(); i++)
		{
			this->setValue(i, random.nextDouble(min, max));
		}
	}

	static int copyCounter;
	static int moveCounter;

private:
	void copy(const CTable &other);


	std::string name;
	double *table;
	int tableLen;
};
#endif
