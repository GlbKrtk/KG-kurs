#include <Windows.h>
#include "base.h"

base::base()
{
	x[0] = 380; y[0] = 250; z[0] = 110;
	x[1] = 380; y[1] = 150; z[1] = 110;
	x[2] = 490; y[2] = 150; z[2] = 110;
	x[3] = 490; y[3] = 250; z[3] = 110;

	x[4] = 370; y[4] = 230; z[4] = 10;
	x[5] = 370; y[5] = 130; z[5] = 10;
	x[6] = 480; y[6] = 130; z[6] = 10;
	x[7] = 480; y[7] = 230; z[7] = 10;

	x[8] = 300; y[8] = 230; z[8] = 60;
	x[9] = 330; y[9] = 160; z[9] = 60;
	x[10] = 360; y[10] = 170; z[10] = 110;
	x[11] = 330; y[11] = 240; z[11] = 110;
	x[12] = 400; y[12] = 160; z[12] = 10;
	x[13] = 370; y[13] = 220; z[13] = 10;

	int vec1[3], vec2[3];
	int A, B, C, D;
	float t;
	int m, n, p;

	vec1[0] = x[1] - x[0];
	vec2[0] = x[5] - x[0];

	vec1[1] = y[1] - y[0];
	vec2[1] = y[5] - y[0];

	vec1[2] = z[1] - z[0];
	vec2[2] = z[5] - z[0];

	A = vec1[1] * vec2[2] - vec2[1] * vec1[2];
	B = vec1[2] * vec2[0] - vec2[2] * vec1[0];
	C = vec1[0] * vec2[1] - vec2[0] * vec1[1];
	D = -(A * x[0] + B * y[0] + C * z[0]);

	m = x[9] - x[12]; n = y[9] - y[12]; p = z[9] - z[12];
	t = (float)(-A * x[12] - B * y[12] - C * z[12] - D) / (A * m + B * n + C * p);
	x[14] = m * t + x[12]; y[14] = n * t + y[12]; z[14] = p * t + z[12];

	m = x[13] - x[12]; n = y[13] - y[12]; p = z[13] - z[12];
	t = (float)(-A * x[12] - B * y[12] - C * z[12] - D) / (A * m + B * n + C * p);
	x[15] = m * t + x[12]; y[15] = n * t + y[12]; z[15] = p * t + z[12];

	m = x[10] - x[12]; n = y[10] - y[12]; p = z[10] - z[12];
	t = (float)(-A * x[12] - B * y[12] - C * z[12] - D) / (A * m + B * n + C * p);
	x[16] = m * t + x[12]; y[16] = n * t + y[12]; z[16] = p * t + z[12];

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i == j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;

	centre();
}

void base::multiplication()
{
	float buf[4], buf1[4];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 4; j++)
			buf1[j] = 0;

		buf[0] = (float)x[i];
		buf[1] = (float)y[i];
		buf[2] = (float)z[i];
		buf[3] = 1;

		for (int k = 0; k < 4; k++)
			for (int t = 0; t < 4; t++)
				buf1[k] += buf[t] * matrix[t][k];

		x[i] = (int)buf1[0];
		y[i] = (int)buf1[1];
		z[i] = (int)buf1[2];
	}

}

void base::centre()
{
	CentreX = 0;
	CentreY = 0;
	CentreZ = 0;
	int n = 14;
	for (int i = 0; i < n; i++)
	{
		CentreX += x[i];
		CentreY += y[i];
		CentreZ += z[i];
	}
	CentreX /= n;
	CentreY /= n;
	CentreZ /= n;
}

void base::moving(int xyz, int pm)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i == j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;

	float i;
	if (pm == 1)
		i = 10;
	else
		i = -10;
	if (xyz == 1)
		matrix[3][0] = i;
	if (xyz == 2)
		matrix[3][1] = i;
	if (xyz == 3)
		matrix[3][2] = i;

	multiplication();
}

void base::scaling(int pm)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i == j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;

	centre();

	float Sxy;
	if (pm == 1)
		Sxy = (float)1.1;
	else
		Sxy = (float)0.9;
	matrix[0][0] = matrix[1][1] = matrix[2][2] = Sxy;
	matrix[3][0] = CentreX * (1 - Sxy);
	matrix[3][1] = CentreY * (1 - Sxy);
	matrix[3][2] = CentreZ * (1 - Sxy);

	multiplication();
}

void base::turn(int xyz, int pm)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i == j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;

	centre();

	int fi;
	if (pm == 1)
		fi = 5;
	else
		fi = -5;

	if (xyz == 1)
	{
		matrix[1][1] = matrix[2][2] = (float)cos(fi * M_PI / 180);
		matrix[1][2] = (float)sin(fi * M_PI / 180);
		matrix[2][1] = (float)-sin(fi * M_PI / 180);

		matrix[3][1] = CentreY * (1 - (float)cos(fi * M_PI / 180)) + CentreZ * (float)sin(fi * M_PI / 180);
		matrix[3][2] = CentreZ * (1 - (float)cos(fi * M_PI / 180)) - CentreY * (float)sin(fi * M_PI / 180);
	}

	if (xyz == 2)
	{
		matrix[0][0] = matrix[2][2] = (float)cos(fi * M_PI / 180);
		matrix[0][2] = (float)-sin(fi * M_PI / 180);
		matrix[2][0] = (float)sin(fi * M_PI / 180);

		matrix[3][0] = CentreX * (1 - (float)cos(fi * M_PI / 180)) - CentreZ * (float)sin(fi * M_PI / 180);
		matrix[3][2] = CentreZ * (1 - (float)cos(fi * M_PI / 180)) + CentreX * (float)sin(fi * M_PI / 180);
	}

	if (xyz == 3)
	{
		matrix[0][0] = matrix[1][1] = (float)cos(fi * M_PI / 180);
		matrix[0][1] = (float)sin(fi * M_PI / 180);
		matrix[1][0] = (float)-sin(fi * M_PI / 180);

		matrix[3][0] = CentreX * (1 - (float)cos(fi * M_PI / 180)) + CentreY * (float)sin(fi * M_PI / 180);
		matrix[3][1] = CentreY * (1 - (float)cos(fi * M_PI / 180)) - CentreX * (float)sin(fi * M_PI / 180);
	}

	multiplication();
}