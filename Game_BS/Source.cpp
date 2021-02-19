#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool isStarted = false;

const int rows = 11;
const int columns = 11;
const int maxShots = 35;

int currentShot = 1;
int input;

string Board[rows][columns];
string result;
class Location
{
public:
	void Add(Location rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}
	bool operator==(Location rhs)
	{
		return x == rhs.x
			&& y == rhs.y;
	}
	bool operator!=(Location rhs)
	{
		return x != rhs.x
			&& y != rhs.y;
	}
	int x;
	int y;
};
Location shots[maxShots];

void gameRules()
{
	system("CLS");
	cout << "Welcome to BattleShip!\n" << endl;
	cout << "The object of the game is to sink every ship on the board\n";
	cout << "5 ships of random orientation and location\n";
	cout << "Have been placed around the board. Upon being prompted enter \n";
	cout << "the coordinates of the shot you wish to make sepperated by a space\n";
	cout << "Then press enter";
	cout << endl << "ie. 2 3 [ENTER]" << endl;
	cout << "[Hit] A hit is marked with H\n[Miss] a miss is marked with M\n[Sunk]A sunk ship is marked with S\n" << endl;
	cout << endl << "The game ends when all ships have been sunk or you run out of shots\n You only get 35 shots.\n";
	cout << endl << "[1] Alright let's play!\n";
	cin >> input;
	
	if (input == 1)
	{
		isStarted = true;
	}
}

class Ship
{
public:
	Ship(int in_size, bool in_isPlayers)
	{
		size = in_size;
		isPlayers = in_isPlayers;
		in_ship();
		insertShip();
	}
	int size = 5;
	int hitCount = 0;
	string symbol = "X";
	bool isPlayers;
	bool isVert = false;
	bool isSunk = false;

	Location loc = { 0, 0 };
	Location sLocs[5];

	string isVertT;
	void genLocs()
	{
		Location delta_loc = { 0,0 };

		sLocs[0].x = loc.x;
		sLocs[0].y = loc.y;

		if (isVert)
		{
			delta_loc = { 0,1 };
		}
		else
		{
			delta_loc = { 1,0 };
		}
		for (int i = 0; i < size; i++)
		{
			if (i > 0)
			{
				sLocs[i].x = (sLocs[0].x + (delta_loc.x * i));
				sLocs[i].y = (sLocs[0].y + (delta_loc.y * i));
			}
		}

	}
	void isOnBoard()
	{
		if (loc.x < 1)
		{
			loc.x = 1;
		}
		if (loc.y < 1)
		{
			loc.y = 1;
		}
		if (loc.y >= rows)
		{
			loc.y = rows - 1;
		}
		if (loc.x >= columns)
		{
			loc.x = columns - 1;
		}
		if (isVert && loc.y + size > rows)
		{
			loc.y = rows - size;
		}
		if (!isVert && loc.x + size > columns)
		{
			loc.x = columns - size;
		}
	}
	void in_ship()
	{
		if (isPlayers)
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
		else
		{
			loc.x = rand() % 10 + 1;
			loc.y = rand() % 10 + 1;
			int vert = rand() % 100;
			if (vert >= 30)
			{
				isVert = true;
			}
			else
			{
				isVert = false;
			}
			symbol = ".";
		}
		isOnBoard();
	}
	void insertShip()
	{
		if (!isVert)
		{
			for (int i = 0; i < size; i++)
			{
				Board[loc.y][loc.x + i] = symbol;
			}
		}
		if (isVert)
		{
			for (int i = 0; i < size; i++)
			{
				Board[loc.y + i][loc.x] = symbol;
			}
		}
		genLocs();
	}
	void testShot(Location shot_loc)
	{
		bool isHit = false;
		for (int i = 0; i < size; i++)
		{
			if (sLocs[i] == shot_loc)
			{
				isHit = true;
				hitCount++;
			}
		}
		if (isHit)
		{
			Board[shot_loc.y][shot_loc.x] = "H";
			isHit = false;
		}
		if (!isHit && (Board[shot_loc.y][shot_loc.x] != "H" && Board[shot_loc.y][shot_loc.x] != "S"))
		{
			Board[shot_loc.y][shot_loc.x] = "M";
		}
		if (hitCount == size)
		{
			symbol = "S";
			isSunk = true;
			insertShip();
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
	system("CLS");
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

void getShot(int shotNum)
{
	cout << "Please enter the X then Y coordinate of your shot: ";

	cin >> shots[shotNum].x >> shots[shotNum].y;

	currentShot++;
}

void gameIsOver()
{
	cout << "GAME OVER" << endl;
	cout << result;
	cin >> input;
}

int main()
{
	srand(time(NULL));

	if (!isStarted)
	{
		cout << "Please select an option below then press enter: " << endl;
		cout << "[1] Start Game" << endl;
		cout << "[2] Read Rules" << endl;
		cin >> input;
		if (input == 1)
		{
			isStarted = true;
			system("CLS");
		}
		if (input == 2)
		{
			gameRules();
		}
	}
	if (isStarted)
	{
		clear();
		showBoard();

		Ship Carrier(6, false);
		showBoard();

		Ship Battleship(5, false);
		showBoard();
		
		Ship Cruiser(4, false);
		showBoard();
		
		Ship Sub(3, false);
		showBoard();
		
		Ship Destroyer(2, false);
		showBoard();
		
		for (int i = 0; i < currentShot; i++)
		{
			if (currentShot == maxShots)
			{
				result = "You Lose :(";
				break;
			}

			if (Carrier.isSunk
				&& Battleship.isSunk
				&& Cruiser.isSunk
				&& Sub.isSunk
				&& Destroyer.isSunk)
			{
				result = "You Win!";
				break;
			}

			getShot(i);
			Carrier.testShot(shots[i]);
			Battleship.testShot(shots[i]);
			Cruiser.testShot(shots[i]);
			Sub.testShot(shots[i]);
			Destroyer.testShot(shots[i]);
			showBoard();
		}
		gameIsOver();
	}
}