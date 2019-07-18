#include <iostream>
#include <windows.h>
#include "printInfoText.h"
using namespace std;

void printInfoText(int curRound, int curMoney, int wager) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "Round: " << curRound << " / 10" <<endl;
	cout << "You have: ";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	cout << curMoney << " Perica" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	if (wager != 0) {
		cout << "Your wager is: " << wager << " Perica" << endl;
	}
	else {
		cout << endl;
	}
}