// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <cctype>

using namespace ::std;

int  StringComp(string input, int index)
{
	if (input.length() > 1)
	{
		for (int i = 0; i < input.length() - 1; i++)
		{
			if (input[i] == input[i + 1])
			{
				return 1;
			}

		}
		return 0;
	}
	else
	{
		return 0;
	}
}

// Returns true if the list contains a character in the list
bool DuplicateCheck(string input, char character)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == character)
		{
			return true;
		}
	}
	return false;
}

int DuplicateCharacters(string input)
{
	string DupList = "";
	int count = 0;
	if (input.length() > 1)
	{
		for (int i = 0; i < input.length() - 1; i++)
		{
			if (DuplicateCheck(DupList, input[i]) == false)
			{
				for (int j = i + 1; j < input.length(); j++)
				{
					if (input[i] == input[j])
					{
						count++;
						DupList.push_back(input[i]);
						j = input.length();
					}
				}
			}
		}
	}
	return count;
}

int chartoint(char c)
{
	if (c == '0')
	{
		return 0;
	}
	else if (c == '1')
	{
		return 1;
	}
	else if (c == '2')
	{
		return 2;
	}
	else if (c == '3')
	{
	return 3;
	}
	else if (c == '4')
	{
	return 4;

	}
	else if (c == '5')
	{
	return 5;
	}
	else if (c == '6')
	{
	return 6;
	}
	else if (c == '7')
	{
	return 7;
	}
	else if (c == '8')
	{
	return 8;
	}
	else if (c == '9')
	{
	return 9;
	}


}
	


int SecondHighestDigit(string input)
{
	int highest = 0;
	int sndhighest = 0;

	int digitcount = 0;

	for (int i = 0; i < input.length(); i++)
	{
		if(isdigit(input[i]) > 0)
		{
			digitcount++;
			if (chartoint(input[i]) > highest)
			{
				sndhighest = highest;
				highest = chartoint(input[i]);
			}
			else if (chartoint(input[i]) > sndhighest)
			{
				sndhighest = chartoint(input[i]);
			}
		}
	}
	if (digitcount > 1)
	{
		return sndhighest;
	}
	else
	{
		return -1;
	}
}

vector<int> RotateRight(vector<int> input)
{
	vector<int> Output;
	vector<int> Up, Down, Left, Right;
	Up = { 0,1 };
	Down = { 0,-1 };
	Left = { -1,0 };
	Right = { 1,0 };

	if (input == Up) Output = Right;
	else if (input == Right) Output = Down;
	else if (input == Down) Output = Left;
	else if (input == Left) Output = Up;
	return Output;
}

vector<int> RotateLeft(vector<int> input)
{
	vector<int> Output;
	vector<int> Up, Down, Left, Right;
	Up = { 0,1 };
	Down = { 0,-1 };
	Left = { -1,0 };
	Right = { 1,0 };

	if (input == Up) Output = Left;
	else if (input == Right) Output = Up;
	else if (input == Down) Output = Right;
	else if (input == Left)	Output = Down;
	return Output;
}

int TurnCheck(vector<int> Position, vector<int> Direction)
{
	if (Direction[0] != 0)
	{
		if (Direction[0] == -(Position[0] / Position[0]))
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else if (Direction[1] != 0)
	{
		if (Direction[1] == -(Position[0] / Position[0]))
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

}


int main()
{

	int Count = 0;
	vector<int> Direction = { 0,1 };
	vector<int> Position = { 0,0 };

	string input = "FxLxLxFx";

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == 'L') Direction = RotateLeft(Direction);
		else if (input[i] == 'R') Direction = RotateRight(Direction);
		else if (input[i] == 'F')
		{
			Position[0] = Position[0] + Direction[0];
			Position[1] = Position[1]+ Direction[1];
		}
	}

	cout << Position[0] << "," << Position[1] << endl;
	cout << Direction[0] << "," << Direction[1] << endl;

	Count += TurnCheck(Position, Direction);
	Count += Position[0] + Position[1];
	cout << "Steps:" << Count << endl;
  
	system("Pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
