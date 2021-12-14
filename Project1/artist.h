#pragma once
// количество плоскостей
#define P 11
#include <Windows.h>
#include "base.h"

//структура, описывающая плоскость
struct plane_c
{
	int plane[5];
	float z;
	COLORREF c;
};

class artist : public base
{
	plane_c pl[P];

	void create_plane();
	void paint(HDC dc, int i1, int i2, int mas_buf[][4], COLORREF color);

public:
	void paint();
	void shadow(HDC memDC);
	
};