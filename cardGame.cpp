#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <iterator>
#include <random>
#include <WinUser.h>
#include "EasyBMP.h"
#include "megumin_picture.h"
#include "Card.cpp"
using namespace std;

class Slot {
public:

	COORD topRight;
	COORD topLeft;
	COORD bottomRight;
	COORD bottomLeft;
};

void calculateSlotPosithion(Slot slotArray[6])
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int startingPointX = 3;
	int startingPointY = 25;
	COORD coord;

	for (int i = 0;i<6;i++)
	{
		coord.Y = startingPointY + 3;

		coord.X = 17 + startingPointX + i * 20;

		coord.X = startingPointX + (i * 20);
		coord.Y = 2 + startingPointY;

		slotArray[i].topLeft.X = coord.X;
		slotArray[i].topLeft.Y = coord.Y;
		SetConsoleCursorPosition(hout, coord);
		SetConsoleTextAttribute(hout, 13);
		cout << "+" << string(16, ' ') << "+";
		SetConsoleTextAttribute(hout, 15);

		slotArray[i].topRight.X = coord.X;
		slotArray[i].topRight.Y = coord.Y;

		coord.X = startingPointX + (i * 20);
		coord.Y = 12 + startingPointY;

		slotArray[i].bottomLeft.X = coord.X;
		slotArray[i].bottomLeft.Y = coord.Y;
		SetConsoleCursorPosition(hout, coord);
		SetConsoleTextAttribute(hout, 13);
		cout << "+" << string(16, ' ') << "+";
		SetConsoleTextAttribute(hout, 15);

		slotArray[i].bottomRight.X = coord.X;
		slotArray[i].bottomRight.Y = coord.Y;
	}
}

void printPictures(int pictureNumber, vector<Card> hand)
{
	HWND console = GetConsoleWindow();
	HDC context = GetDC(console);

	int pictureSize = 0;
	char* bytes = NULL;

	if (pictureNumber == 0)
	{
		pictureSize = megumin_picture_bmp_size;
		bytes = new char[megumin_picture_bmp_size];
		memcpy(bytes, megumin_picture_bmp, megumin_picture_bmp_size);
	}

	BMP image;

	image.ReadFromBuffer((const unsigned char*)bytes, pictureSize);
	for (int i = 0;i < 6;i++)
	{


		for (int x = 0; x < image.TellWidth(); x++)
		{
			for (int y = 0; y < image.TellHeight(); y++)
			{
				int red = image.GetPixel(x, y).Red;
				int green = image.GetPixel(x, y).Green;
				int blue = image.GetPixel(x, y).Blue;
				int alpha = image.GetPixel(x, y).Alpha;

				COLORREF color = RGB(red, green, blue);
				if (alpha == 0)
				{
					SetPixel(context, (x + 25 + 1* 8 - 2)+160*i, y + 400 + 3 * 16 - 3, color);
				}
			}
		}
	}
}

void printCard(vector<Card>& hand)
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	int startingPointX = 3;
	int startingPointY = 25;

	for (int i = 0;i < 6;i++)
	{

		coord.Y = startingPointY+3;

		coord.X = 17+ startingPointX + i*20;

		for (int j = 0;j < 10;j++)
		{
			SetConsoleCursorPosition(hout, coord);
			SetConsoleTextAttribute(hout, 13);
			cout << "|";
			coord.Y++;
		}
		SetConsoleTextAttribute(hout, 15);

		coord.X = startingPointX + (i * 20);
		coord.Y = startingPointY+3;

		for (int j = 0;j < 10;j++)
		{
			SetConsoleCursorPosition(hout, coord);
			SetConsoleTextAttribute(hout, 13);
			cout << "|";
			coord.Y++;
		}
		SetConsoleTextAttribute(hout, 15);

		coord.X = startingPointX + (i * 20);
		coord.Y = 2 + startingPointY;
		SetConsoleCursorPosition(hout, coord);
		SetConsoleTextAttribute(hout, 13);
		cout << "+" << string(16, '-') << "+";
		SetConsoleTextAttribute(hout, 15);

		coord.X = startingPointX + (i * 20);
		coord.Y = 12 + startingPointY;
		SetConsoleCursorPosition(hout, coord);
		SetConsoleTextAttribute(hout, 13);
		cout << "+" << string(16, '-') << "+";
		SetConsoleTextAttribute(hout, 15);
	}

	printPictures(0, hand);

	coord.Y = 1 + startingPointY + 10;
	SetConsoleCursorPosition(hout, coord);
	for (int j = 0;j < 6;j++)
	{
		coord.X = startingPointX+1 + j * 20;
		SetConsoleCursorPosition(hout, coord);
		SetConsoleTextAttribute(hout, 236);
		cout << string(1, ' ');
		cout << hand[j].hpStr;
		SetConsoleTextAttribute(hout, 237);
		cout << hand[j].name;
		SetConsoleTextAttribute(hout, 227);
		cout << hand[j].damageStr;
		cout << string(1, ' ');
		SetConsoleTextAttribute(hout, 15);
	}
}

int main()
{
	srand(time(NULL));

	COORD xy;

	HWND hwnd = GetConsoleWindow();
	
	CONSOLE_SCREEN_BUFFER_INFO cslSize;
	MoveWindow(hwnd, 150, 150, 1050 ,700 , TRUE);
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hout, &cslSize);
	xy.X = cslSize.dwSize.X;
	xy.Y = 41;
	ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);
	SetConsoleScreenBufferSize(hout, xy);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WM_SYSKEYDOWN & ~WM_KEYDOWN & ~WS_MAXIMIZEBOX &~WS_THICKFRAME  &~WS_MINIMIZEBOX);

	vector<Card>hand = {};
	Slot slotArray[6]{};

		calculateSlotPosithion(slotArray);

	int ddd = rand();
	mt19937 g(ddd);




	Card card0("  Serega  ", 20, 10);
	Card card1("  Nikitos ", 20, 1);
	Card card2(" Arseniy  ", 1, 10);
	Card card3("   Dimos  ", 50, 20);
	Card card4("   Gleb   ", 50, 60);
	Card card5("   vlad   ", 0, 00);
	Card card6("    An    ", 10, 11);
	Card card7("   vova   ", 1, 99);
	Card card8("   Ilya   ", 4, 4);
	Card card9("  pushok  ", 1, 3);
	Card card10("   vasya  ", 1, 2);
	Card card11("  Ksyusha ", 1, 77);

	hand.push_back(card0);
	hand.push_back(card1);
	hand.push_back(card2);
	hand.push_back(card3);
	hand.push_back(card4);
	hand.push_back(card5);
	hand.push_back(card6);
	hand.push_back(card7);
	hand.push_back(card8);
	hand.push_back(card9);
	hand.push_back(card10);
	hand.push_back(card11);


	shuffle(hand.begin(), hand.end(), g);

	//printCard(hand);
	char ap = ' ';

	cin >> ap;
}
