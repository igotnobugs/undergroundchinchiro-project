#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <conio.h>

using namespace std;

// function declaration
int wager(int money);


struct Roll {
	string type; // Snake Eyes, Triples, Pairs ,etc
	int rank; // Higher is better. Snake Eyes has higher ranking than Triples 
	int value; // The value of the roll for Triples and Pairs (eg. 6-4-4 value is 6)
	int dice[3]; // The actual value rolled for each die
};

// Rolls the 3 dice and determine its value. Returns a struct which represents the roll.
Roll rollDice() {
	Roll newRoll;
	int sum = 0;
	int same = 0;
	int paired = 0;

	//Roll 3 dice
	for (int i = 0; i < 3; i++) {
		newRoll.dice[i] = (rand() % 6) + 1;
		sum += newRoll.dice[i];
	}

	//Check if sum is 6 // 1 + 2 + 3
	//If yes, Output lost
	if (sum == 6) {
		newRoll.type = "Lost";
		newRoll.rank = -1;
		newRoll.value = -1;
		return newRoll;
	}

	//Find paired numbers
	for (int i = 0; i < 3; i++) {
		int check = newRoll.dice[i];
		for (int ii = i + 1; ii < 3; ii++) {
			if (check == newRoll.dice[ii]) {
				same++;
			}
		}

		if (same == 2) {
			//If Triple then return
			newRoll.type = "Triples";
			newRoll.rank = 2;
			newRoll.value = newRoll.dice[i];
			return newRoll;
			break;
		}

		if (same == 1) {
			//If Pairs continue
			newRoll.type = "Pairs";
			newRoll.rank = 1;
			paired = newRoll.dice[i];
			//IF PAIRED find the number not equal to paired
			for (int i = 0; i < 3; i++) {
				if (paired != newRoll.dice[i]) {
					newRoll.value = newRoll.dice[i];
					return newRoll;
				}
			}
		}
	}
	

	
	//None Shown//might be Bust or 4-5-6
	newRoll.type = "Bust";
	newRoll.rank = 0;
	newRoll.value = 0;
	return newRoll;
	
}

int main() {
	//FINAL PROJECT - undergroundchinchiro-project

	srand(time(NULL)); //Randomize Seed

	//ROLL TABLE
	/* _getch()
	/Mutliply
	---x5
	1-1-1 = 3 
	---x3
	6-6-6 = 23328
	5-5-5 = 9375
	4-4-4 = 3072
	3-3-3 = 729
	2-2-2 = 96
	---x2
	4-5-6 = 120
	//x must be pairs

	---x1 //   
	6-x-x // 
	5-x-x //
	4-x-x // 
	3-x-x //
	2-x-x //  
	1-x-x // 
	---Lose
	1-2-3 // 14 //  84
	Pisser - 5% Dice out of ball
	Bust - no match/Roll again 3 times or lose
	*/

	int curMoney = 90000;
	int playerWager = 0;

	int MIN_WAGER = 100;
	float PISSER_CHANCE = 5; //100

	Roll playerRoll;
	Roll dealerRoll;

	int curRound = 0;
	int MAX_ROUND = 10;
	
	while (MAX_ROUND > curRound) {
		//Increase Round
		curRound++;
		//Text
		cout << "Round: " << curRound << endl;
		cout << "You have: " << curMoney << " Perica" << endl;

		//Dealer Rolls
		

		//How much input bet
		playerWager = 0;
		cout << "How much do you want to bet?" << endl;
		while ((playerWager < MIN_WAGER) || (playerWager > curMoney)) {
			cin >> playerWager;
			
		}
		curMoney -= playerWager;

		//Player Rolls
		int bet = wager(playerWager);
		playerRoll = rollDice();


		cout << endl;
		cout << "-------RESULT---------" << endl;
		//Result of the current round
		//cout << "You betted " << bet << endl;
		
		cout << "Dice: " << playerRoll.dice[0] << " " << playerRoll.dice[1] << " " << playerRoll.dice[2] << endl;
		cout << "Type: " << playerRoll.type << endl;
		cout << "Value: " << playerRoll.value << endl;
		cout << "Rank: " << playerRoll.rank << endl;


		system("pause");
		system("cls");
	}

	//Result of the game
	cout << "You have: " << curMoney << " Perica" << endl;
	
	cout << endl;



	system("pause");
	cout << endl;
	return 0;

}



// Ask user how much to bet. Returns bet value. Returns 0 if user can't bet anymore (below minimum bet).
int wager(int money) {
	return money;
}

// Prints the roll
void printRoll(Roll roll) {

};


int max(int num1, int num2) {
	// local variable declaration
	int result;

	if (num1 > num2)
		result = num1;
	else
		result = num2;

	return result;
}