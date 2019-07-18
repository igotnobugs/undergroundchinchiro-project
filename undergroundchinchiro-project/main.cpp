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

//The Roll struct
//[Terms]
//Snake Eyes(1-1-1), Triples(x-x-x), Royal(4-5-6), Pairs(v-x-x), Bust(x-y-z), Peasant (1-2-3), Pisser (n/a)
//[Roll Table]
//Snake Eyes = Gain(wager x5)
//Triples = Gain(wager x3)
//Royal = Gain(wager x2)
//Paires = Gain(wager x1)
//Bust = Nothing so Roll Again but if Bust 3 times in a row -> Lose
//Peasant = Pay(wager x2)
//Pisser = Lose, dice is out of bowl
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
	//Must match id in user Struct
	int userId;
};

//The Users. Dealer and the Player
struct User {
	//Name of the User
	string name;
	//Dealer is 0, Player is 1
	int id = -1;
	//If money is unlimited
	bool unlimitedMoney = false;
	//amount of money this user has
	int money = 0;
	//amount wagered/bet
	int wager = 0;
} dealerUser, playerUser;

//Do wager
User doWager(User user);

//Asks player how much to bet.
//Returns 0 if user input an invalid bet (Less than minimum, more than max, or a char) else returns bet value. 
int wager(int money, int maxMoney);

//Roll n amount of dice depending on the dice array size
//Returns a struct which represents the new roll values.
Roll rollDice();

//Prints the roll
void printRoll(Roll roll);

//Prints the roll
//In an Ascending order but Value is first displayed for Pairs
void printSortedRoll(Roll roll);

//Evaluates and Prints the Type of the Roll
void evaluateRoll(Roll roll);

//Roll dice consecutively until ...
Roll rollConsecDice(User user, int amount);

//Compare Rolls and return an int.
//No compare needed if dealer got a pisser.
int compareRoll(Roll dealerRoll, Roll playerRoll);

//Deals with the payout based on result
void payout(int result);

//0 - Worst. 1 - Bad, 2 - Meh, 3 - Good, 4 - Best;
int evaluateEnding(int curMoney);

//Display Ending based on evaluation
void displayEnding(int result);

//Constants
float PISSER_CHANCE = 5; //A simulated chance of dice going out of bounds
int MIN_WAGER = 100; //The minimum allowabled wager
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
bool includeIntro = false;
int curRound = 0;
Roll dealerRoll;
Roll playerRoll;

int main() {
	srand(time(NULL)); //Randomize Seed

	//Initialization
	dealerUser.name = "DEALER";
	dealerUser.id = 0;
	dealerUser.unlimitedMoney = true;
	playerUser.name = "KAIJI";
	playerUser.id = 1;
	playerUser.money = 90000;

	//WINDOWS XP START UP Sound OPENING
	cout << "Jerry Presents" << endl;
	playNote('D', 6, 400);
	playNote('C', 5, 200);
	playNote('A', 5, 300);
	cout << endl;
	playNote('G', 5, 500);
	playNote('D', 6, 200);
	cout << "UNDERGROUND CHINCHINRO!" << endl;
	playNote('A', 5, 600);
	cout << endl;

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

		//Tutorial
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
	while ((MAX_ROUND > curRound) && (playerUser.money > MIN_WAGER)) {
		//Increase Round
		curRound++;

		//RESET
		Roll dealerRoll;
		Roll playerRoll;


		printInfoText(curRound, playerUser.money, playerUser.wager);
		cout << endl;

		//Phase 1 - Player Bets/Wager
		playerUser = doWager(playerUser);

		//Clear to print new info text with the wager
		system("cls");
		printInfoText(curRound, playerUser.money, playerUser.wager);
		cout << endl;

		//Phase 2 - Dealer Rolls
		//dealerRoll.userId = dealer.id;
		dealerRoll = rollConsecDice(dealerUser, MAX_BUST);
		evaluateRoll(dealerRoll);
		system("pause");
		cout << endl;

		//Clear again
		system("cls");
		printInfoText(curRound, playerUser.money, playerUser.wager);
		cout << endl;

		int result; 
		//Check if dealer didnt roll a Pisser else skip
		if (dealerRoll.rank != 0) {
			//Phase 3 - Player Rolls
			playerRoll = rollConsecDice(playerUser, MAX_BUST);
			evaluateRoll(playerRoll);
			system("pause");
			cout << endl;
		} 

		//Clear again
		system("cls");
		printInfoText(curRound, playerUser.money, playerUser.wager);
		cout << endl;

		//Phase 4 - Results/Compare
		cout << "-------RESULT---------" << endl;
		//0 draw, 1 - Dealer. 2 - Player	
		result = compareRoll(dealerRoll, playerRoll);
		switch (result) {
		case 0:
			cout << "DRAW" << endl;
			playNote('C', 3, 200);
			playNote('C', 3, 500);
			playNote('C', 3, 700);
			break;
		case 1:
			cout << dealerUser.name << " WON!" << endl;
			playNote('C', 4, 200);
			playNote('C', 3, 500);
			playNote('C', 2, 700);
			break;
		case 2:
			cout << playerUser.name << " WON!" << endl;
			playNote('C', 3, 200);
			playNote('C', 3, 300);
			playNote('C', 4, 700);
			break;
		}
	
		//Phase 5 - Payout
		cout << endl;
		cout << "-------PAYOUT---------" << endl;
		payout(result);
		cout << endl;

		system("pause");
		system("cls");
	}

	////Phase 6 - Ending
	cout << "-------ENDING---------" << endl;
	cout << endl;	
	int endingResult = evaluateEnding(playerUser.money);
	displayEnding(endingResult);

	system("pause");
	cout << endl;
	return 0;
}

User doWager(User user) {
	int bet = 0;
	while (bet == 0) {
		cout << "How much do you want to bet?" << endl;
		cout << "You will bet: ";
		cin >> bet;

		if (bet == 11400314) {
			playLaSalle();
		}
		if (bet == 81) {
			playMario();
		}
		bet = wager(bet, user.money);
	}
	user.money = user.money - bet;
	user.wager = bet;
	return user;
}

int wager(int bet, int maxMoney) {
	if (bet < 1) {
		cout << endl;
		cout << dealerUser.name << ": Focus on the game, " << playerUser.name << "-san" << endl;
		//Incase player inputs a char
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return 0;
	}
	else if (bet > maxMoney) {
		cout << endl;
		cout << dealerUser.name << ": You only have " << maxMoney << " Perico, " << playerUser.name << "-san" << endl;
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
	return bet;
}

Roll rollDice() {
	Roll newRoll;
	//Check for Pisser first
	int chance = rand() % 100;
	//cout << "Calculated Chance: " << chance << endl; 
	cout << "Rolling..." << endl;
	if (PISSER_CHANCE > chance) {
		Sleep(DEFAULT_TIME);
		newRoll.type = "Pisser";
		newRoll.rank = 0;
		return newRoll;
	}
	//Get dice array size
	int size = sizeof(newRoll.dice) / sizeof(newRoll.dice[0]);
	int sum = 0;
	//Roll size amount of dice
	for (int i = 0; i < size; i++) {
		newRoll.dice[i] = (rand() % 6) + 1;
		sum += newRoll.dice[i];
	}
	int same = 0;
	//Finding paired numbers are more probable, so do this first
	for (int i = 0; i < size; i++) {
		//Use first dice as check
		int check = newRoll.dice[i];
		//Check it against the rest
		for (int ii = i + 1; ii < size; ii++) {
			if (check == newRoll.dice[ii]) {
				same++;
			}
		}
		//TRIPLE if first number is same as the rest but not a 1
		if ((same == 2) && (check != 1)) {
			newRoll.type = "Triples";
			newRoll.rank = 5;
			newRoll.value = newRoll.dice[i];
			return newRoll;
		}
		//PAIR if at least one is same
		if (same == 1) {
			newRoll.type = "Pairs";
			newRoll.rank = 3;

			newRoll.paired = newRoll.dice[i];
			//IF PAIRED find the number not equal to paired.
			for (int i = 0; i < 3; i++) {
				if (newRoll.paired != newRoll.dice[i]) {
					//Set that as the value
					newRoll.value = newRoll.dice[i];
					return newRoll;
				}
			}
		}
	}

	//1-2-3
	if (sum == 6) {
		newRoll.type = "Peasant";
		newRoll.rank = 1;
		return newRoll;
	}
	//4-5-6
	if (sum == 15) {
		newRoll.type = "Royal";
		newRoll.rank = 4;
		return newRoll;
	}
	//Snake eyes 1-1-1
	if (sum == 3) {
		newRoll.type = "Snake-Eyes";
		newRoll.rank = 6;
		return newRoll;
	}
	//A Bust
	newRoll.type = "Bust";
	newRoll.rank = 2;
	return newRoll;
}

void printRoll(Roll roll) {
	if (roll.rank != 0) {
		for (int i = 0; i < 3; i++) {
			Sleep(DEFAULT_TIME);
			//Beep(1245, 200);
			playNote('C', roll.dice[i] + 1, 200);
			cout << roll.dice[i] << " ";
		}
	}
	else {
		//skip
	}
}

void printSortedRoll(Roll roll) {
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
		Beep(1245, 200);
		cout << sortedRoll.dice[i] << " ";
	}
	//cout << "Type: " << roll.type << endl;
	//cout << "Value: " << roll.value << endl;
	//cout << "Rank: " << roll.rank << endl;
};

Roll rollConsecDice(User user, int amount){
	int retries = 0;
	Roll newRoll;

	//While the roll is not a Pisser/Peasant and hasn't exceeded MAX_BUST	
	while ((newRoll.rank <= 2) && (retries < MAX_BUST)) {
		cout << user.name << " has thrown the dice." << endl;
		newRoll = rollDice();
		printRoll(newRoll);	

		//If Bust roll again
		if (newRoll.rank == 2) {
			retries++;
			Sleep(500);
			cout << "- Bust" << endl;;
			cout << endl;
			Beep(1168, 500);
			Sleep(1000);
		}
		else {
			retries = 99;
			cout << endl;
		}
	}

	//Return roll that is not a bust or the last one
	return newRoll;
}

void evaluateRoll(Roll roll) {
	//Sleep(DEFAULT_TIME);
	cout << endl;
	switch (roll.rank) {
	case 0:
		cout << "Roll is a Pisser" << endl;
		playNote('C', 3, 200);
		playNote('C', 2, 200);
		break;
	case 1:
		cout << "Roll is a Peasant -> ";
		printSortedRoll(roll);
		cout << endl;
		playNote('C', 3, 200);
		playNote('C', 2, 200);
		break;
	case 2:
		cout << "Roll is a Bust -> ";
		printSortedRoll(roll);
		cout << endl;
		playNote('C', 3, 200);
		playNote('C', 2, 200);
		break;
	case 3:
		cout << "Roll is Pairs -> ";
		printSortedRoll(roll);
		cout << endl;
		playNote('C', 3, 200);
		playNote('C', 4, 500);
		playNote('C', 5, 700);
		break;
	case 4:
		cout << "Roll is Royal -> ";
		printSortedRoll(roll);
		cout << endl;
		break;
	case 5:
		cout << "Roll is Triples!" << endl;
		break;
	case 6:
		cout << "Roll is Snake Eyes!!" << endl;
		break;
	}
}

int compareRoll(Roll dealerRoll, Roll playerRoll) {

	printSortedRoll(dealerRoll);
	cout << "VS ";
	printSortedRoll(playerRoll);
	cout << endl;
	cout << dealerRoll.type << " VS " << playerRoll.type << endl;
	cout << endl;

	//Instant win for player
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

void payout(int result) {
	int winnings = playerUser.wager;

	switch (result) {
	case 0:
		//No payout it's a draw
		cout << "It's a draw";
		break;
	case 1:
		//No payout but if player is peasant
		if (playerRoll.rank == 1) {
			//has to pay twice his bet to the void
			winnings *= PEASANT_MULT;		
			playerUser.money -= winnings;
			cout << playerUser.name << " has to pay " << winnings << " Perico to " << dealerUser.name;
		}
		else {
			//skip
			cout << "Nothing...";
		}
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
		else if (playerRoll.rank == 3){
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

int evaluateEnding(int curMoney) {
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
}

void displayEnding(int result) {
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