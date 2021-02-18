#include <iostream>
#include <string>

using namespace std;

const int rows = 11;
const int columns = 11;

string Board[rows][columns];

class Location
{
public:
	void Add(Location rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}
	int x;
	int y;
};

class Ship
{
public:
	int size = 5;
	Location loc = { 0, 0 };
	string isVertT;
	bool isVert = false;

	void in_ship()
	{
		cout << "Please enter the X then Y coordinate of your ship: ";
		cin >> loc.x >> loc.y;

		cout << "Do you want it to be horizontal or vertical (H or V): ";
		cin >> isVertT;

		if (isVertT == "H" || isVertT == "h")
		{
			isVert = false;
		}
		if (isVertT == "V" || isVertT == "v")
		{
			isVert = true;
		}
	}

	void insertShip()
	{
		if (!isVert)
		{
			for (int i = 0; i < size; i++)
			{
				Board[loc.y][loc.x + i] = "X";
			}
		}
		if (isVert)
		{
			for (int i = 0; i < size; i++)
			{
				Board[loc.y + i][loc.x] = "X";
			}
		}
	}
};

void clear()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{

			Board[i][j] = ".";
			Board[0][j] = to_string(j);
			Board[i][0] = to_string(i);

		}
	}
}

void showBoard()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (i != 10 || j != 0)
			{
				cout << " ";
			}
			cout << Board[i][j];
		}
		cout << endl;
	}
}

void insertShips()
{
	
}

Ship ship[5];

int main()
{
	clear();
	showBoard();
	
	ship[0].size = 5;
	ship[0].in_ship();
	ship[0].insertShip();

	showBoard();

	ship[1].size = 4;
	ship[1].in_ship();
	ship[1].insertShip();

	showBoard();

	ship[2].size = 3;
	ship[2].in_ship();
	ship[2].insertShip();

	showBoard();

	ship[3].size = 2;
	ship[3].in_ship();
	ship[3].insertShip();

	showBoard();

	ship[4].size = 2;
	ship[4].in_ship();
	ship[4].insertShip();

	showBoard();
}