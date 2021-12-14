#include <Windows.h>
#include "artist.h"

void artist::create_plane()
{
		//0123
	pl[0].c = RGB(120, 0, 120);
	pl[0].plane[0] = 0; pl[0].plane[1] = 1; pl[0].plane[2] = 2; pl[0].plane[3] = 3; pl[0].plane[4] = -1;
	pl[0].z = (z[pl[0].plane[0]] + z[pl[0].plane[1]] + z[pl[0].plane[2]] + z[pl[0].plane[3]]) / 4;
		//4567
	pl[1].c = RGB(120, 0, 0);
	pl[1].plane[0] = 4; pl[1].plane[1] = 5; pl[1].plane[2] = 6; pl[1].plane[3] = 7; pl[1].plane[4] = -1;
	pl[1].z = (z[pl[1].plane[0]] + z[pl[1].plane[1]] + z[pl[1].plane[2]] + z[pl[1].plane[3]]) / 4;
		//0154
	pl[2].c = RGB(0, 120, 0);
	pl[2].plane[0] = 0; pl[2].plane[1] = 1; pl[2].plane[2] = 5; pl[2].plane[3] = 4; pl[2].plane[4] = -1;
	pl[2].z = (z[pl[2].plane[0]] + z[pl[2].plane[1]] + z[pl[2].plane[2]] + z[pl[2].plane[3]]) / 4;
		//3267
	pl[3].c = RGB(120, 120, 0);
	pl[3].plane[0] = 3; pl[3].plane[1] = 2; pl[3].plane[2] = 6; pl[3].plane[3] = 7; pl[3].plane[4] = -1;
	pl[3].z = (z[pl[3].plane[0]] + z[pl[3].plane[1]] + z[pl[3].plane[2]] + z[pl[3].plane[3]]) / 4;
		//0473
	pl[4].c = RGB(0, 0, 120);
	pl[4].plane[0] = 0; pl[4].plane[1] = 4; pl[4].plane[2] = 7; pl[4].plane[3] = 3; pl[4].plane[4] = -1;
	pl[4].z = (z[pl[4].plane[0]] + z[pl[4].plane[1]] + z[pl[4].plane[2]] + z[pl[4].plane[3]]) / 4;
		//1562
	pl[5].c = RGB(0, 120, 120);
	pl[5].plane[0] = 1; pl[5].plane[1] = 5; pl[5].plane[2] = 6; pl[5].plane[3] = 2; pl[5].plane[4] = -1;
	pl[5].z = (z[pl[5].plane[0]] + z[pl[5].plane[1]] + z[pl[5].plane[2]] + z[pl[5].plane[3]]) / 4;

		//8 13 11
	pl[6].c = RGB(0, 90, 90);
	pl[6].plane[0] = 8; pl[6].plane[1] = 13; pl[6].plane[2] = 11; pl[6].plane[3] = 8; pl[6].plane[4] = -1;
	pl[6].z = (z[pl[6].plane[0]] + z[pl[6].plane[1]] + z[pl[6].plane[2]] + z[pl[6].plane[3]]) / 4;

		//8 9 10 11
	pl[7].c = RGB(0, 90, 0);
	pl[7].plane[0] = 8; pl[7].plane[1] = 9; pl[7].plane[2] = 10; pl[7].plane[3] = 11; pl[7].plane[4] = -1;
	pl[7].z = (z[pl[7].plane[0]] + z[pl[7].plane[1]] + z[pl[7].plane[2]] + z[pl[7].plane[3]]) / 4;

	//8 9 14 15 13
	pl[8].c = RGB(0, 0, 90);
	pl[8].plane[0] = 8; pl[8].plane[1] = 9; pl[8].plane[2] = 14; pl[8].plane[3] = 15; pl[8].plane[4] = 13;
	pl[8].z = (z[pl[8].plane[0]] + z[pl[8].plane[1]] + z[pl[8].plane[2]] + z[pl[8].plane[3]]) / 4;

	//9 14 16 10
	pl[9].c = RGB(90, 90, 0);
	pl[9].plane[0] = 9; pl[9].plane[1] = 14; pl[9].plane[2] = 16; pl[9].plane[3] = 10; pl[9].plane[4] = -1;
	pl[9].z = (z[pl[9].plane[0]] + z[pl[9].plane[1]] + z[pl[9].plane[2]] + z[pl[9].plane[3]]) / 4;

	//11 10 16 15 13
	pl[10].c = RGB(90, 0, 90);
	pl[10].plane[0] = 11, pl[10].plane[1] = 10; pl[10].plane[2] = 16; pl[10].plane[3] = 15; pl[10].plane[4] = 13;
	pl[10].z = (z[pl[10].plane[0]] + z[pl[10].plane[1]] + z[pl[10].plane[2]] + z[pl[10].plane[3]]) / 4;
	
}

void artist::paint()
{
	HWND hwnd = GetConsoleWindow();
	HDC dc = GetDC(hwnd);
	HDC memDC = CreateCompatibleDC(dc);
	HBITMAP memBM = CreateCompatibleBitmap(dc, 1080, 600);
	SelectObject(memDC, memBM);

	create_plane();
	system("cls");
	for (int i = 0; i < P - 1; i++)
		for (int j = 0; j < P - i - 1; j++)
		{
			if (pl[j].z > pl[j + 1].z)
			{
				plane_c buf = pl[j];
				pl[j] = pl[j + 1];
				pl[j + 1] = buf;
			}
		}

	int mas_buf[N][4];
	for (int i = 0; i < N; i++)
	{
		mas_buf[i][0] = x[i];
		mas_buf[i][1] = y[i];
		mas_buf[i][2] = z[i];
		mas_buf[i][3] = 1;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			matrix[i][j] = 0;
	}

	/* косоугольная */
	matrix[3][3] = 1;
	int a = 45;
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[3][3] = 1;
	matrix[0][2] = -cos(a * 3.141592 / 180);
	matrix[1][2] = -sin(a * 3.141592 / 180);

	float buf[4], buf1[4];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 4; j++)
			buf1[j] = 0;

		buf[0] = (float)mas_buf[i][0];
		buf[1] = (float)mas_buf[i][1];
		buf[2] = (float)mas_buf[i][2];
		buf[3] = (float)mas_buf[i][3];

		for (int k = 0; k < 4; k++)
			for (int t = 0; t < 4; t++)
				buf1[k] += buf[t] * matrix[t][k];

		mas_buf[i][0] = (int)buf1[0];
		mas_buf[i][1] = (int)buf1[1];
	}

	for (int i = 0; i < P; i++)
	{
		SelectObject(memDC, GetStockObject(DC_PEN));
		SetDCPenColor(memDC, pl[i].c);
		
		int x_min = mas_buf[pl[i].plane[0]][0], x_max = mas_buf[pl[i].plane[0]][0];
		int y_min = mas_buf[pl[i].plane[0]][1], y_max = mas_buf[pl[i].plane[0]][1];

		MoveToEx(memDC, mas_buf[pl[i].plane[0]][0], mas_buf[pl[i].plane[0]][1], NULL);
		LineTo(memDC, mas_buf[pl[i].plane[1]][0], mas_buf[pl[i].plane[1]][1]);
		LineTo(memDC, mas_buf[pl[i].plane[2]][0], mas_buf[pl[i].plane[2]][1]);
		LineTo(memDC, mas_buf[pl[i].plane[3]][0], mas_buf[pl[i].plane[3]][1]);

		if (pl[i].plane[4] == -1)
		{
			LineTo(memDC, mas_buf[pl[i].plane[0]][0], mas_buf[pl[i].plane[0]][1]);
			for (int j = 0; j < 4; j++)
			{
				if (x_min > mas_buf[pl[i].plane[j]][0])
					x_min = mas_buf[pl[i].plane[j]][0];
				if (x_max < mas_buf[pl[i].plane[j]][0])
					x_max = mas_buf[pl[i].plane[j]][0];

				if (y_min > mas_buf[pl[i].plane[j]][1])
					y_min = mas_buf[pl[i].plane[j]][1];
				if (y_max < mas_buf[pl[i].plane[j]][1])
					y_max = mas_buf[pl[i].plane[j]][1];
			}
		}
		else
		{
			LineTo(memDC, mas_buf[pl[i].plane[4]][0], mas_buf[pl[i].plane[4]][1]);
			LineTo(memDC, mas_buf[pl[i].plane[0]][0], mas_buf[pl[i].plane[0]][1]);
			for (int j = 0; j < 5; j++)
			{
				if (x_min > mas_buf[pl[i].plane[j]][0])
					x_min = mas_buf[pl[i].plane[j]][0];
				if (x_max < mas_buf[pl[i].plane[j]][0])
					x_max = mas_buf[pl[i].plane[j]][0];

				if (y_min > mas_buf[pl[i].plane[j]][1])
					y_min = mas_buf[pl[i].plane[j]][1];
				if (y_max < mas_buf[pl[i].plane[j]][1])
					y_max = mas_buf[pl[i].plane[j]][1];
			}
		}

		SelectObject(memDC, GetStockObject(DC_PEN));
		SetDCPenColor(memDC, pl[i].c);

		bool flag1 = 0, flag2 = 0;
		for (int y = y_min + 1; y <= y_max - 1; y++)
		{
			flag1 = 0;
			flag2 = 0;
			int x1 = x_min;
			int x2 = x_max;
			while (!flag1 || !flag2)
			{
				if (flag1 == 0)
					if (GetPixel(memDC, x1, y) == pl[i].c)
						flag1 = 1;
					else
						x1++;
				if (flag2 == 0)
					if (GetPixel(memDC, x2, y) == pl[i].c)
						flag2 = 1;
					else
						x2--;
				if (x1 == x2 /*|| x1 > x_max || x2 < x_min*/)
					break;
			}
			if (x1 >= x2 || x1 >= x_max || x2 <= x_min)
				continue;
			MoveToEx(memDC, x1, y, NULL);
			LineTo(memDC, x2, y);
			
		}
	}

	shadow(memDC);

	BitBlt(dc, 0, 0, 1080, 600, memDC, 0, 0, SRCCOPY);
	DeleteDC(memDC);
	DeleteObject(memBM);
}

void artist::shadow(HDC dc) {
	int x_sh[N], y_sh[N], z_sh[N];
	int A, B, C, D;
	int m, n, p;

	centre();

	int x_light = 400;
	int y_light = 0;
	int z_light = 10;

	int xPl[3], yPl[3], zPl[3];
	xPl[0] = 470; yPl[0] = 350; zPl[0] = 20;
	xPl[1] = 570; yPl[1] = 350; zPl[1] = 20;
	xPl[2] = 490; yPl[2] = 370; zPl[2] = 180;

	A = (yPl[1] - yPl[0]) * (zPl[2] - zPl[0]) - (yPl[2] - yPl[0]) * (zPl[1] - zPl[0]);
	B = (zPl[1] - zPl[0]) * (xPl[2] - xPl[0]) - (zPl[2] - zPl[0]) * (xPl[1] - xPl[0]);
	C = (xPl[1] - xPl[0]) * (yPl[2] - yPl[0]) - (xPl[2] - xPl[0]) * (yPl[1] - yPl[0]);
	D = -(A * xPl[0] + B * yPl[0] + C * zPl[0]);

	for (int i = 0; i < N; i++)
	{
		int m = x_light - x[i];
		int n = y_light - y[i];
		int p = z_light - z[i];

		float t = (float)(-A * x[i] - B * y[i] - C * z[i] - D) / (A * m + B * n + C * p);

		x_sh[i] = m * t + x[i];
		y_sh[i] = n * t + y[i];
		z_sh[i] = p * t + z[i];
	}

	int mas_buf[N][4];
	for (int i = 0; i < N; i++)
	{
		mas_buf[i][0] = x_sh[i];
		mas_buf[i][1] = y_sh[i];
		mas_buf[i][2] = z_sh[i];
		mas_buf[i][3] = 1;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			matrix[i][j] = 0;
	}

	/* косоугольная */
	matrix[3][3] = 1;
	int a = 45;
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	matrix[3][3] = 1;
	matrix[0][2] = -cos(a * 3.141592 / 180);
	matrix[1][2] = -sin(a * 3.141592 / 180);

	float buf[4], buf1[4];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 4; j++)
			buf1[j] = 0;

		buf[0] = (float)mas_buf[i][0];
		buf[1] = (float)mas_buf[i][1];
		buf[2] = (float)mas_buf[i][2];
		buf[3] = (float)mas_buf[i][3];

		for (int k = 0; k < 4; k++)
			for (int t = 0; t < 4; t++)
				buf1[k] += buf[t] * matrix[t][k];

		mas_buf[i][0] = (int)buf1[0];
		mas_buf[i][1] = (int)buf1[1];
	}

	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(255, 255, 255));

	MoveToEx(dc, mas_buf[0][0], mas_buf[0][1], NULL);
	LineTo(dc, mas_buf[1][0], mas_buf[1][1]);
	LineTo(dc, mas_buf[2][0], mas_buf[2][1]);
	LineTo(dc, mas_buf[3][0], mas_buf[3][1]);
	LineTo(dc, mas_buf[0][0], mas_buf[0][1]);

	MoveToEx(dc, mas_buf[4][0], mas_buf[4][1], NULL);
	LineTo(dc, mas_buf[5][0], mas_buf[5][1]);
	LineTo(dc, mas_buf[6][0], mas_buf[6][1]);
	LineTo(dc, mas_buf[7][0], mas_buf[7][1]);
	LineTo(dc, mas_buf[4][0], mas_buf[4][1]);

	MoveToEx(dc, mas_buf[0][0], mas_buf[0][1], NULL);
	LineTo(dc, mas_buf[4][0], mas_buf[4][1]);

	MoveToEx(dc, mas_buf[1][0], mas_buf[1][1], NULL);
	LineTo(dc, mas_buf[5][0], mas_buf[5][1]);

	MoveToEx(dc, mas_buf[2][0], mas_buf[2][1], NULL);
	LineTo(dc, mas_buf[6][0], mas_buf[6][1]);

	MoveToEx(dc, mas_buf[3][0], mas_buf[3][1], NULL);
	LineTo(dc, mas_buf[7][0], mas_buf[7][1]);

	paint(dc, 0, 8, mas_buf, RGB(200, 200, 200));

	MoveToEx(dc, mas_buf[8][0], mas_buf[8][1], NULL);
	LineTo(dc, mas_buf[9][0], mas_buf[9][1]);
	LineTo(dc, mas_buf[10][0], mas_buf[10][1]);
	LineTo(dc, mas_buf[11][0], mas_buf[11][1]);
	LineTo(dc, mas_buf[8][0], mas_buf[8][1]);

	MoveToEx(dc, mas_buf[10][0], mas_buf[10][1], NULL);
	LineTo(dc, mas_buf[12][0], mas_buf[12][1]);
	LineTo(dc, mas_buf[13][0], mas_buf[13][1]);
	LineTo(dc, mas_buf[11][0], mas_buf[11][1]);

	MoveToEx(dc, mas_buf[8][0], mas_buf[8][1], NULL);
	LineTo(dc, mas_buf[13][0], mas_buf[13][1]);

	MoveToEx(dc, mas_buf[9][0], mas_buf[9][1], NULL);
	LineTo(dc, mas_buf[12][0], mas_buf[12][1]);

	paint(dc, 8, 14, mas_buf, RGB(200, 200, 200));
}

void artist::paint(HDC dc, int i1, int i2, int mas_buf[][4], COLORREF color)
{
	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, color);
	int x_max = mas_buf[i1][0], x_min = mas_buf[i1][0];
	int y_max = mas_buf[i1][1], y_min = mas_buf[i1][1];

	for (int i = i1; i < i2; i++)
	{
		if (x_max < mas_buf[i][0])
			x_max = mas_buf[i][0];

		if (x_min > mas_buf[i][0])
			x_min = mas_buf[i][0];

		if (y_max < mas_buf[i][1])
			y_max = mas_buf[i][1];

		if (y_min > mas_buf[i][1])
			y_min = mas_buf[i][1];
	}

	bool flag1 = 0, flag2 = 0;
	for (int y = y_min; y <= y_max; y++)
	{
		int x1 = x_min;
		int x2 = x_max;
		while (!flag1 || !flag2)
		{
			if (flag1 == 0)
				if (GetPixel(dc, x1, y) == RGB(255, 255, 255))
					flag1 = 1;
				else
					x1++;
			if (flag2 == 0)
				if (GetPixel(dc, x2, y) == RGB(255, 255, 255))
					flag2 = 1;
				else
					x2--;
			if (x1 == x2 || x1 > x_max || x2 < x_min)
				break;
		}
		MoveToEx(dc, x1, y, NULL);
		LineTo(dc, x2 + 1, y);
		flag1 = 0;
		flag2 = 0;
	}

	SelectObject(dc, GetStockObject(DC_PEN));
	SetDCPenColor(dc, RGB(255, 255, 255));
}
