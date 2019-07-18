#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "printInfoText.h"
#include "playMarioTune.h"
#include "playNote.h"
#include "playLaSalle.h"

using namespace std;

//FINAL PROJECT - undergroundchinchiro-project

//The Users. Dealer and the Player
struct User {
	//Name of the User
	string name;
	//amount of money this user has
	int money = 0;
	//amount wagered/bet
	int wager = 0;
} dealerUser, playerUser;


//The Roll struct
struct Roll {
	//Snake Eyes, Triples, Royal, Pairs, Bust, Peasant, Pisser
	string type;
	//Snake Eyes(6), Triples(5), Royal(4), Pairs(3), Bust(2), Peasant(1), Pisser(0)
	int rank = -1;
	//The value of the roll for Triples but for Pairs is the other unpaired number
	int value = -1;
	//The number of the paired number in Pairs
	int paired = -1;
	//The dice array 
	int dice[3] = { 0, 0, 0 };
};

//Asks User how much to bet. Then store that bet as their wager.
User DoWager(User user);

//Returns 0 if User input an invalid bet (Less than minimum, more than max, or a char) else returns bet value. 
int ValidateWager(int money, User user);

//Roll n amount of dice depending on the dice array size
//Returns a struct which represents the new roll values.
Roll RollDice();

//Prints the roll
void PrintRoll(Roll roll);

//Prints the roll
//In an Ascending order but Value is first displayed for Pairs
void PrintSortedRoll(Roll roll);

//Evaluates and Prints the Type of the Roll
void EvaluateRoll(Roll roll);

//Roll dice consecutively until ...
Roll RollConsecDice(User user, int amount);

//Compare Rolls and return an int.
//No compare needed if dealer got a pisser.
int CompareRoll(Roll dealerRoll, Roll playerRoll);

//Display Compare, and the result
void DisplayResult(int result, Roll dealerRoll, Roll playerRoll);

//Givethe payout based on result
void GivePayout(int result);

//0 - Worst. 1 - Bad, 2 - Meh, 3 - Good, 4 - Best;
int EvaluateEnding(int curMoney);

//Display Ending based on evaluation
void DisplayEnding(int result);

//Check if user as enough money for next round, if no money asks for retry.
void CheckUserMoney(User user);

//Constants
int STARTING_MONEY = 90000; //Amount of money player starts
float PISSER_CHANCE = 5; //A simulated chance of dice going out of bounds
int MIN_WAGER = 100; // The minimum allowabled wager
int MAX_ROUND = 10; //Max amount of rounds
int MAX_BUST = 3; //Max amount of busts before moving on
int DEFAULT_TIME = 500; //Default milliseconds to wait to show next dice 
float LAST_DICE_MULT = 1.5; //Multiplier to DEFAULT_TIME to wait to show the last dice 
int LAST_TIME_CHANCE = 33; //Chance to do the mutliplier for DEFAULT_TIME for last dice
int LAST_TENSION_TIME = 2000; //Milliseconds to wait for the last number to show, will be used on larger wagers.
int LAST_TENSION_CHANCE = 66; //Chance to use the LAST_TENSION_TIME instead of DEFAULT_TIME for last dice on larger wagers
int LARGE_WAGER_PERCENT = 60; //Percent of what constitutes as a large wager in relation to the current money.
int SNAKE_EYES_MULT = 5; //WAGER * MULT recieved when SNAKE EYES
int TRIPLES_MULT = 3; //WAGER * MULT recieved when TRIPLES
int ROYAL_MULT = 2; //WAGER * MULT recieved when ROYAL
int PAIRS_MULT = 1; //WAGER * MULT recieved when PAIRS
int PEASANT_MULT = 2; //WAGER * MULT taken when PEASANT

int ch = ' ';
bool includeIntro = false; //Enable to include intro scene
bool includeStartUp = true; //Enable opening tune
int curRound = 0; //current round
Roll dealerRoll;
Roll playerRoll;
int main() {
	srand(time(NULL)); //Randomize Seed
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //Set default color of text

	//Initialization
	dealerUser.name = "OTSUKI";
	playerUser.name = "KAIJI";
	playerUser.money = STARTING_MONEY;

	//WINDOWS XP START UP Sound OPENING if true
	if (includeStartUp) {
		cout << "Jerry Presents" << endl;
		PlayNote('D', 6, 400);
		PlayNote('C', 5, 200);
		PlayNote('A', 5, 300);
		cout << endl;
		PlayNote('G', 5, 500);
		PlayNote('D', 6, 200);
		cout << "UNDERGROUND CHINCHINRO!" << endl;
		PlayNote('A', 5, 600);
		cout << endl;
		system("pause");
	}

	//Introduction runs if includeIntro is true
	if (includeIntro) {
		bool wantPlay = true;
		while ((ch != 'y') && (ch != 'n')) {
			cout << playerUser.name << "-san, do you want to play the Underground Chinchiro? (y/n)" << endl;
			ch = _getch();
		}

		if (ch == 'y') {
			//Offer a tutorial
			ch = ' '; //Reset
			system("cls");
			while ((ch != 'y') && (ch != 'n')) {
				cout << "Hmmm, Want me to remind you how it works? (y/n)" << endl;
				ch = _getch();
			}
		}
		else if (ch == 'n') {
			//Instant Game Over
			curRound = 99;
			wantPlay = false;
			system("cls");
			cout << "GAME OVER" << endl;
			cout << playerUser.name << " kept his " << playerUser.money << " Perico and lived happily every after." << endl;
			system("pause");
			return 0;
		}

		//Tutorial --- in progress
		if (wantPlay) {
			if (ch == 'y') {
				system("cls");
				cout << "Well, listen closely " << playerUser.name << "." <<endl;
				system("pause");
			}
			else if (ch == 'n') {
				cout << "Well, let's start then. This time however I'll be the only dealer. Try to get as much money as possible in 10 rounds." << endl;
				system("pause");
			}
		}
	}

	//Game Loop
	while (MAX_ROUND > curRound) {
		//Increase/Next Round
		curRound++;

		//RESET
		Roll dealerRoll;
		Roll playerRoll;

		//For new round set wager display to 0
		PrintInfoText(curRound, playerUser.money, 0, true);
		cout << endl;

		//Phase 1 - Player Bets/Wager
		playerUser = DoWager(playerUser);

		//Clear to print new info text with the wager
		PrintInfoText(curRound, playerUser.money, playerUser.wager, true);
		cout << endl;

		//Phase 2 - Dealer Rolls
		dealerRoll = RollConsecDice(dealerUser, MAX_BUST);
		EvaluateRoll(dealerRoll);
		system("pause");
		cout << endl;

		//Clear again
		PrintInfoText(curRound, playerUser.money, playerUser.wager, true);
		cout << endl;

		//If dealer didnt roll a Pisser else skip player roll phase
		if (dealerRoll.rank != 0) {
			//Phase 3 - Player Rolls
			playerRoll = RollConsecDice(playerUser, MAX_BUST);
			EvaluateRoll(playerRoll);
			system("pause");
			cout << endl;
		} 

		//Clear again
		PrintInfoText(curRound, playerUser.money, playerUser.wager, true);
		cout << endl;

		//Phase 4 - Results/Compare
		cout << "-------RESULT---------" << endl;
		int result; //0 Draw, 1 - Dealer win. 2 - Player win	
		result = CompareRoll(dealerRoll, playerRoll);
		DisplayResult(result, dealerRoll, playerRoll);
	
		//Phase 5 - Payout
		cout << endl;
		cout << "-------PAYOUT---------" << endl;
		GivePayout(result);
		cout << endl;

		system("pause");
		system("cls");
		//Check money of users
		CheckUserMoney(playerUser);
	}

	//Phase 6 - Ending
	cout << "-------ENDING---------" << endl;
	cout << endl;	
	int endingResult = EvaluateEnding(playerUser.money);
	DisplayEnding(endingResult);

	system("pause");
	cout << endl;
	return 0;
}

User DoWager(User user) {
	int bet = 0;
	while (bet == 0) {
		cout << "How much do you want to bet?" << endl;
		cin >> bet;
		//bet special conditions
		switch (bet) {
		case 1: //bet Minimum Wager
			bet = MIN_WAGER;
			break;
		case 2: //bet the same as last time
			bet = user.wager;
			break;
		case 3: //ALL IN
			bet = user.money;
			break;
		case 4: //bet 20,000
			bet = 20000;
			break;
		case 11400314:
			PlayTuneLaSalle();
			break;
		case 81:
			PlayTuneMario(1);
			break;
		}
		bet = ValidateWager(bet, user); //check if wager is not invalid
	}
	//user.money -= bet; //Reduce money based on bet
	user.wager = bet; //Set wager as bet
	return user;
}

int ValidateWager(int bet, User user) {
	if (bet < 1) {
		cout << endl;
		cout << dealerUser.name << ": Focus on the game, " << playerUser.name << "-san" << endl;
		//Incase player inputs a char
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	else if (bet > user.money) {
		cout << endl;
		cout << dealerUser.name << ": You only have " << user.money << " Perico, " << playerUser.name << "-san" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	else if (bet < MIN_WAGER) {
		cout << endl;
		cout << dealerUser.name << ": The minimum wager is " << MIN_WAGER << " Perico, " << playerUser.name << "-san" << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	//If none of the above
	return bet;
}

Roll RollConsecDice(User user, int max) {
	int retries = 0;
	Roll newRoll;

	//While the roll is not a Pisser/Peasant and hasn't exceeded max	
	while ((newRoll.rank <= 2) && (retries < max)) {
		cout << user.name << " has thrown the dice." << endl;
		newRoll = RollDice();
		PrintRoll(newRoll);

		//If Bust roll again
		if (newRoll.rank == 2) {
			retries++;
			Sleep(DEFAULT_TIME);
			cout << "- Bust" << endl;;
			cout << endl;
			PlayNote('D', 5, 500);
			Sleep(DEFAULT_TIME);
		}
		else {
			retries = max;
			cout << endl;
		}
	}
	//Return roll that is not a bust or the last one
	return newRoll;
}

Roll RollDice() {
	Roll newRoll;
	cout << "Rolling . . ." << endl;
	//Pisser check
	if (PISSER_CHANCE >= rand() % 101) {
		newRoll.type = "Pisser";
		newRoll.rank = 0;
		return newRoll;
	}
	//Get dice array size
	int size = sizeof(newRoll.dice) / sizeof(newRoll.dice[0]);
	int sum = 0;
	//Roll amount of dice based on size
	for (int i = 0; i < size; i++) {
		newRoll.dice[i] = (rand() % 6) + 1;
		sum += newRoll.dice[i]; //Get the sum for later if neeeded
	}
	int sameNums = 0;
	//Finding Paired numbers are more probable, so do this first
	for (int i = 0; i < size; i++) {
		//Use first dice as check
		int check = newRoll.dice[i];
		//Check it against the rest
		for (int ii = i + 1; ii < size; ii++) {
			if (check == newRoll.dice[ii]) {
				sameNums++; //Add sameNums check has a same number
			}
		}
		//TRIPLE if first number is same as the rest but not a 1
		if ((sameNums == 2) && (check != 1)) {
			newRoll.type = "Triples";
			newRoll.rank = 5;
			newRoll.value = newRoll.dice[i]; 
			return newRoll;
		}
		//PAIR if at least one is same
		if (sameNums == 1) {
			newRoll.type = "Pairs";
			newRoll.rank = 3;
			newRoll.paired = newRoll.dice[i];
			//Find the number not equal to paired value.
			for (int ii = 0; ii < size; ii++) {
				if (newRoll.paired != newRoll.dice[ii]) {
					//Set that as the value
					newRoll.value = newRoll.dice[ii];
					return newRoll;
				}
			}
		}
	}
	//All equally have low chance to get
	//1-2-3 Peasant
	if (sum == 6) {
		newRoll.type = "Peasant";
		newRoll.rank = 1;
		return newRoll;
	}
	//4-5-6 Royal
	if (sum == 15) {
		newRoll.type = "Royal";
		newRoll.rank = 4;
		return newRoll;
	}
	//1-1-1 Snake eyes 
	if (sum == 3) {
		newRoll.type = "Snake-Eyes";
		newRoll.rank = 6;
		return newRoll;
	}
	//Last if nothing else, bust
	newRoll.type = "Bust";
	newRoll.rank = 2;
	return newRoll;
}

void PrintRoll(Roll roll) {
	if (roll.rank != 0) {
		for (int i = 0; i < 3; i++) {
			Sleep(DEFAULT_TIME);
			PlayNote('C', roll.dice[i] + 1, 200);
			cout << roll.dice[i] << " ";
		}
	}
	else {
		//skip
	}
}

void PrintSortedRoll(Roll roll) {
	Roll sortedRoll = roll;
	//Sort Dice in ascending order if not PAIRED
	if (sortedRoll.type != "Pairs") {
		for (int i = 0; i < 3; i++) {
			int check = sortedRoll.dice[i];
			int swapIndex = i;
			for (int ii = i; ii < 3; ii++) {
				//Find number greater than check then store that
				if (sortedRoll.dice[ii] < check) {
					check = sortedRoll.dice[ii];
					swapIndex = ii;
				}
			}
			//If check is not equal to dice[i] start swapping
			if (sortedRoll.dice[i] != check) {
				sortedRoll.dice[swapIndex] = sortedRoll.dice[i];
				sortedRoll.dice[i] = check;
			}
		}
	}
	else {
		//Sort value as first number then the pairs
		sortedRoll.dice[0] = roll.value;
		sortedRoll.dice[1] = roll.paired;
		sortedRoll.dice[2] = roll.paired;
	}

	for (int i = 0; i < 3; i++) {
		//Sleep(DEFAULT_TIME * (1 + ((LAST_DICE_MULT - 1) * ((LAST_TIME_CHANCE > rand() % 101) && (i == 2)))));	
		//Sleep(DEFAULT_TIME);
		//PlayNote('D', 6, 200);
		PlayNote('C', roll.dice[i] + 1, 200);
		cout << sortedRoll.dice[i] << " ";
	}
};

void EvaluateRoll(Roll roll) {
	//Sleep(DEFAULT_TIME);
	cout << endl;
	switch (roll.rank) {
	case 0:
		Sleep(DEFAULT_TIME); //Wait for a bit.
		cout << "Roll is a Pisser" << endl;
		PlayNote('C', 3, 200);
		PlayNote('C', 2, 200);
		break;
	case 1:
		cout << "Roll is a Peasant -> ";
		PrintSortedRoll(roll);
		cout << endl;
		PlayNote('C', 3, 200);
		PlayNote('C', 2, 200);
		break;
	case 2:
		cout << "Roll is a Bust -> ";
		PrintSortedRoll(roll);
		cout << endl;
		PlayNote('C', 3, 200);
		PlayNote('C', 2, 200);
		break;
	case 3:
		cout << "Roll is Pairs -> ";
		PrintSortedRoll(roll);
		cout << endl;
		PlayNote('C', 3, 200);
		PlayNote('C', 4, 500);
		PlayNote('C', 5, 700);
		break;
	case 4:
		cout << "Roll is Royal -> ";
		PrintSortedRoll(roll);
		PlayNote('C', 4, 400);
		PlayNote('C', 5, 200);
		PlayNote('C', 5, 200);
		PlayNote('C', 6, 700);
		cout << endl;
		break;
	case 5:
		cout << "Roll is Triples!" << endl;
		PlayNote('C', 4, 400);
		PlayNote('D', 5, 400);
		PlayNote('E', 5, 400);
		break;
	case 6:
		cout << "Roll is Snake Eyes!!" << endl;
		PlayNote('C', 4, 400);
		PlayNote('B', 3, 400);
		PlayNote('A', 3, 400);
		break;
	}
}

int CompareRoll(Roll dealerRoll, Roll playerRoll) {
	//Instant win for player, isser
	if (dealerRoll.rank == 0) {
		return 2;
	}

	//In an event of same ranks
	if (dealerRoll.rank == playerRoll.rank) {
		//If pairs or triples
		if (dealerRoll.value > playerRoll.value) {
			return 1; 
		}
		//If snake eyes
		if (dealerRoll.rank == 6){
			return 0; //Same snake eyes is Draw
		}
		//Player wins on Bust Peasant and Pairs with same or greater value
		return 2;
	}

	//If dealer has higher rank they win
	if (dealerRoll.rank > playerRoll.rank) {
		//but a pisser on player if dealer is a bust/peasant is a draw
		if ((playerRoll.rank == 0) && ((dealerRoll.rank == 2) || (dealerRoll.rank == 1))) {
			return 0;
		}
		return 1;
	}
	//everything else win for player
	return 2;
}

void DisplayResult(int result, Roll dealerRoll, Roll playerRoll) {
	//If dealer is pisser, no need to compare
	if (dealerRoll.rank != 0) {
		//Dice values compare
		PrintSortedRoll(dealerRoll);
		cout << "VS ";
		PrintSortedRoll(playerRoll);
		cout << endl;
		//Type compare
		cout << dealerRoll.type << " VS " << playerRoll.type << endl;
		cout << endl;
		//Pairs and Triples, Value compare
		if ((dealerRoll.rank == playerRoll.rank) && ((playerRoll.rank == 3) || (playerRoll.rank == 5))) {
			if (dealerRoll.value > playerRoll.value) {
				cout << dealerRoll.value << " > " << playerRoll.value << endl;
				cout << endl;
			}
			else {
				cout << dealerRoll.value << " < " << playerRoll.value << endl;
				cout << endl;
			}
		}
	}
	
	switch (result) {
	case 0:
		cout << "DRAW" << endl;
		PlayNote('C', 3, 200);
		PlayNote('C', 3, 500);
		PlayNote('C', 3, 700);
		break;
	case 1:
		cout << dealerUser.name << " WON!" << endl;
		PlayNote('C', 4, 200);
		PlayNote('C', 3, 500);
		PlayNote('C', 2, 700);
		break;
	case 2:
		cout << playerUser.name << " WON!" << endl;
		PlayNote('C', 3, 200);
		PlayNote('C', 3, 300);
		PlayNote('C', 4, 700);
		break;
	}
}

void GivePayout(int result) {
	int winnings = playerUser.wager;

	switch (result) {
	case 0:
		//No payout it's a draw
		cout << "It's a draw";
		//playerUser.money += winnings; //Get wagered money back
		//cout << playerUser.name << " got their " << winnings << " Perico back.";
		break;
	case 1:
		//Reduce money based on wager but if player is peasant
		if (playerRoll.rank == 1) {
			//has to pay twice his bet to the void
			winnings *= PEASANT_MULT;				
		}
		playerUser.money -= winnings;
		cout << playerUser.name << " has to pay " << winnings << " Perico to " << dealerUser.name;
		break;

	case 2: 
		//Snake eyes
		if (playerRoll.rank == 6) {
winnings *= SNAKE_EYES_MULT;
playerUser.money += winnings;
		}
		//Triples
		else if (playerRoll.rank == 5) {
		winnings *= TRIPLES_MULT;
		playerUser.money += winnings;
		}
		//Royal
		else if (playerRoll.rank == 4) {
		winnings *= ROYAL_MULT;
		playerUser.money += winnings;
		}
		//PAIR
		else if (playerRoll.rank == 3) {
		winnings *= PAIRS_MULT;
		playerUser.money += winnings;
		}
		else {
		//ANYTHING ELSE
		playerUser.money += winnings;
		}
		cout << playerUser.name << " won " << winnings << " Perico.";
		break;
	}
}

int EvaluateEnding(int curMoney) {
	if (curMoney < 0) {
		//Worst Ending
		return 0;
	}
	if (curMoney < MIN_WAGER) {
		//Bad Ending
		return 1;
	}
	if (curRound == 10) {
		if (curMoney < 90000) {
			//Meh ending
			return 2;
		}
		else if (curMoney > 500000) {
			//Best Ending
			return 4;
		}
		else {
			return 3;
			//Good Ending
		}
	}
	cout << "This shouldn't happen";
	return 0;
}

void DisplayEnding(int result) {
	switch (result) {
	case 0: //Worse
		cout << playerUser.name << "-san went home with a debt of " << playerUser.money * -1 << " Perico." << endl;
		cout << endl;
		cout << "WORST ENDING!!" << endl;
		break;
	case 1: //Bad Ending
		cout << playerUser.name << "-san left with only " << playerUser.money << " Perico left." << endl;
		cout << "It wasn't even enough for the minimum bet." << endl;
		cout << endl;
		cout << "BAD ENDING!" << endl;
		PlayTuneMario(0);
		break;
	case 2: //Meh
		cout << playerUser.name << "-san left the with " << playerUser.money * -1 << " Perico. " << endl;
		cout << "He returned with less than he started with." << endl;

		cout << "It certainely wasn't worth it." << endl;
		cout << endl;
		cout << "Meh Ending" << endl;
		break;
	case 3: //Good
		cout << playerUser.name << "-san came back more than he started by having " << playerUser.money << " Perico." << endl;
		cout << "He felt going back for another round!" << endl;
		cout << endl;
		cout << "GOOD ENDING!" << endl;
		break;
	case 4: //Best
		cout << playerUser.name << "-san got " << playerUser.money * -1 << " Perico. He got half a million!" << endl;
		cout << "He thought about spending it on blackjacks and hookers." << endl;
		cout << endl;
		cout << "BEST ENDING!!" << endl;
		break;
	}
	cout << "GAME OVER" << endl;
}

void CheckUserMoney(User user) {
	if (user.money < MIN_WAGER) {
		cout << endl;
		cout << dealerUser.name << ": Ah, " << playerUser.name << "-san, You don't have enough Perico..." << endl;
		cout << endl;
		cout << "Retry? (y/n)" << endl;
		int choice = ' ';
		while ((choice != 'y') && (choice != 'n')) {
			choice = _getch();
		}
		if (choice == 'y') {
			playerUser.money = STARTING_MONEY;
			curRound = 0;
		}
		else {		
			curRound = MAX_ROUND;
		}
		cout << endl;
	}

}