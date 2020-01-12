#pragma once
#include "pch.h"
#include <random>
#include <cstdlib>
#include <cstdio>
#include <ctime>


class CRandom
{
public:
	CRandom(int seed) 
	{
		if (seed < 0) seed = -1 * seed;
		this->seed = seed;
		srand(seed);
	}
	CRandom()
	{
		seed = time(NULL);
		srand(seed);
	}
	int nextInt(int left, int right)
	{
		int randomInt = rand() % right + left;
		return randomInt;
	}

	double nextDouble(double left, double right)
	{
		double f = (double)rand() / RAND_MAX;
		return left + f * (right - left);
	}
private:
	unsigned int seed;

};