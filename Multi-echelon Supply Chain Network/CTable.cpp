#include "pch.h"
#include "CTable.h"


CTable & CTable::operator=(const CTable & other)
{
	delete this->table;
	table = new double;
	copy(other);
	this->name = other.name;
	this->tableLen = other.tableLen;
	return *this;
}

CTable & CTable::operator=(CTable && other)
{
	this->table = other.table;
	this->name = other.name;
	this->tableLen = other.tableLen;

	other.table = nullptr;
	other.tableLen = 0;
	other.name = "";
	return *this;
}

void CTable::printTable()
{
	if (table == NULL) return;

	for (int i = 0; i < tableLen; i++)
	{
		std::cout << table[i] << "\n";
	}
}

double CTable::getValue(int offset)
{
	if (offset < 0 || offset >= tableLen) return 0;

	return table[offset];
}

bool CTable::setValue(int offset, double value)
{
	if (offset < 0 || offset > tableLen) return false;

	this->table[offset] = value;
	return true;
}

void CTable::copy(const CTable & other)
{
	if (this->table != nullptr) delete table;

	table = new double[other.tableLen];
	this->tableLen = other.tableLen;

	for (int i = 0; i < other.tableLen; i++)
	{
		table[i] = other.table[i];
	}
}

void CTable::fillTable()
{
	if (this->table == NULL) return;

	for (int i = 0; i < tableLen; i++)
	{
		this->table[i] = i;
	}
}

CTable::CTable(const CTable & other)
{
	copy(other);
	this->name = other.name;
	this->tableLen = other.tableLen;

}

CTable::CTable(CTable && other)
{
	this->table = other.table;
	this->name = other.name;
	this->tableLen = other.tableLen;


	other.table = nullptr;
}

bool CTable::setNewSize(int tableLen)
{
	if (tableLen < 0) return false;
	if (this->tableLen == tableLen) return true;
	if (this->table == NULL) table = new double[tableLen];

	double* helpTab = new double[tableLen];

	for (int i = 0; i < tableLen; i++)
	{
		if (i < this->tableLen) helpTab[i] = this->table[i];
	}

	delete table;

	table = helpTab;
	this->tableLen = tableLen;
	return true;
}

CTable * CTable::clone()
{
	return new CTable(*this);
}

CTable CTable::operator-(int other)
{
	CTable substracted;
	substracted.setNewSize(0);
	if (other >= this->tableLen) return std::move(substracted);
	substracted.setNewSize(this->tableLen - other);

	for (int i = 0; i < tableLen - other; i++)
	{
		substracted.setValue(i, table[i]);
	}
	substracted.tableLen = tableLen - other;

	//return std::move(substracted);
	return substracted;

}

CTable CTable::operator+(CTable & other)
{
	CTable added;
	added.setNewSize(other.tableLen + this->tableLen);

	for (int i = 0; i < other.tableLen; i++)
	{
		added.setValue(i, other.table[i]);
	}

	for (int i = 0; i < this->tableLen; i++)
	{
		added.setValue(i + other.tableLen, this->table[i]);
	}

	added.tableLen = other.tableLen + this->tableLen;

	return std::move(added);

}
