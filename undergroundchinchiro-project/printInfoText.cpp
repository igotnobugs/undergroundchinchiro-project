#include <iostream>
#include <windows.h>
#include "printInfoText.h"
using namespace std;

void PrintInfoText(int curRound, int curMoney, int wager, bool clearScreen) {
	if (clearScreen) {
		system("cls");
	}

	cout << "Round: " << curRound << " / 10" << endl;
	cout << "You have: ";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbInfo; 
	GetConsoleScreenBufferInfo(hConsole, &csbInfo);
	int lastColor = csbInfo.wAttributes;
	int color;
	if (curMoney < 60000) {
		color = 14; //Yellow
	}
	else if (curMoney < 30000) {
		color = 12; //Red
	}
	else {
		color = 11; //Light-Blue
	}
	SetConsoleTextAttribute(hConsole, color);
	cout << curMoney << " Perica" << endl;
	SetConsoleTextAttribute(hConsole, lastColor);

	if (wager != 0) {
		cout << "Your wager is: " << wager << " Perica" << endl;
	}
	else {
		cout << endl;
	}
}