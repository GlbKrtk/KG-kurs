#pragma once
#define N 17
#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>
#include <math.h>

class base
{
public:
	base(); 

	//xyz = (1 ��� x, 2 ��� y, 3 ��� z) pm = (1 ��� �������������� �����������, -1 - ��� ��������������)
	void moving(int xyz, int pm); 
	void scaling(int pm); 
	void turn(int xyz, int pm); 

protected:
	int x[N], y[N], z[N];
	int CentreX, CentreY, CentreZ;
	float matrix[4][4];

	void centre();

private:
	void multiplication(); 
};