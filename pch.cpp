//
// pch.cpp
//

#include "pch.h"
#include <iostream>
using namespace std;

int add(int a, int b) {
	return a + b;
}

int subtract(int a, int b) {
	return a - b;
}

int maxA[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

int getWeekday(int year, int month, int day)
{
	bool valid = IsCorrect(year, month, day);
	while (!valid)
	{
		return -1;
	}
	maxA[1] = 28;
	int result = getResult(year, month, day) + 1;
	if (result > 0 && result < 8) {
		return result;
	}
	return -1;
}

bool IsCorrect(int y, int m, int d)
{
	if (y < 1)
		return false;
	else
	{
		if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
			maxA[1] = 29;
		if (m < 0 || m>12)
			return false;
		else
		{
			if (d > maxA[m - 1])
				return false;
			else
				return true;
		}
	}
}
int getResult(int y, int m, int d)
{
	long totalDays = 0;
	for (int i = 1; i < y; i++)
	{
		if (((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0))
			totalDays += 366;
		else
			totalDays += 365;
	}
	if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
		maxA[1] = 29;
	else
		maxA[1] = 28;
	for (int i = 1; i < m; i++)
	{
		totalDays += maxA[i - 1];
	}
	totalDays += (d - 1);
	maxA[1] = 28;
	return (totalDays % 7);
}