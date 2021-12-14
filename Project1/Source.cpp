#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "artist.h"

using namespace std;

int main()
{
	artist shapes;
	shapes.paint();
	do
	{
		switch (_getch())
		{
		case'w':
			shapes.moving(2, -1);
			break;
		case'a':
			shapes.moving(1, -1);
			break;
		case's':
			shapes.moving(2, 1);
			break;
		case'd':
			shapes.moving(1, 1);
			break;
		case'q':
			shapes.moving(3, 1);
			break;
		case'e': 
			shapes.moving(3, -1);
			break;
		case'z':
			shapes.scaling(1);
			break;
		case'x': 
			shapes.scaling(-1);
			break;
		case'7':
			shapes.turn(1, 1);
			break;
		case'1':
			shapes.turn(1, -1);
			break;
		case'9':
			shapes.turn(2, 1);
			break;
		case'3':
			shapes.turn(2, -1);
			break;
		case'6':
			shapes.turn(3, 1);
			break;
		case'4':
			shapes.turn(3, -1);
			break;
		default:
			return 0;
		}
		shapes.paint();
	} while (1);
}
