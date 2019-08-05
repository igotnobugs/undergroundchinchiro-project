#include <iostream>
#include <string>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "playNote.h"

using namespace std;

//FINAL PROJECT - undergroundchinchiro-project

//Constants
int STARTING_MONEY = 90000; //Amount of money player starts
int PISSER_CHANCE = 5; //A simulated chance of dice going out of bounds
int MIN_WAGER = 100; // The minimum allowabled wager
int MAX_ROUND = 10; //Max amount of rounds
int MAX_BUST = 3; //Max amount of busts before moving on
int DEFAULT_TIME = 200; //Default milliseconds to wait to show next dice or for tunes
string DICE_TYPE[7] = { "Pisser", "Peasant", "Bust", "Pairs", "Royal", "Triples", "Snake Eyes" }; //Array position equals to rank
enum Payout { //<type> = <payout multiplier>
	Pisser = 1, Peasant = 2, Bust = 2, Pairs = 2, Royal = 3, Triple = 4, SnakeEyes = 6, Default = 2
};

//The Roll struct
struct Roll {
	Payout type = Default;//Default Payout will be x2
	int rank = -1; //Snake Eyes(6), Triples(5), Royal(4), Pairs(3), Bust(2), Peasant(1), Pisser(0)
	int value = -1; //Number of the roll for Triples but for Pairs is the unpaired number
	int paired = -1; //Number of the paired number in Pairs
	int dice[3] = { 0, 0, 0 }; //The dice array 
	int size = 3; //Should equal to dice array size
};

//The User struct, includes the Roll
struct User {
	string name; //Name of the User
	int money = 0; //Amount of money this user has
	int wager = 0; //Amount wagered/bet
	Roll roll; //Roll of the user
};

bool enableDebug = false;
int curRound = 0;

#pragma region All Functions
//Checks player's bet against a number of factors (Less than MIN_WAGER, more than their Current Money, or a char)
int ValidateWager(int bet, User player) {
	cin.clear(); //Incase player inputs a char
	cin.ignore(INT_MAX, '\n');
	cout << endl;
	if (bet == 0) {
		cout << "[TIPS]" << endl;
		cout << "Input [1] for the Minimum Wager" << endl;
		cout << "Input [2] for the Previous Wager" << endl;
		cout << "Input [3] for an All-In" << endl;
		cout << "Input [4] for 20,000." << endl;
		cout << "Input [99] for Debug" << endl;
	}
	else if (bet < 1) {	
		cout << "Focus on the game, " << player.name << "." << endl;
		return 0;
	}
	else if (bet > player.money) {
		cout << "You only have " << player.money << " Perico, " << player.name << "." << endl;
		return 0;
	}
	else if (bet < MIN_WAGER) {
		cout << "The minimum wager is " << MIN_WAGER << " Perico, " << player.name << "." << endl;
		return 0;
	}
	cout << endl;
	return bet;
}
//Asks player how much to wager then store that if valid.
int DoWager(User dealer, User player) {
	int wager = 0;
	while (wager == 0) {
		cout << "How much do you want to wager? The minimum wager is " << MIN_WAGER << ". Enter 0 for tips." << endl;
		cin >> wager;
		//bet special conditions
		switch (wager) {
		case 0: //Tips
			PlayNote(C, 3, 200);
			break;
		case 1: //bet Minimum Wager
			wager = MIN_WAGER;
			break;
		case 2: //bet the same as last time
			wager = player.wager;
			break;
		case 3: //ALL IN
			wager = player.money;
			break;
		case 4: //bet 20,000
			wager = 20000;
			break;
		case 11400314:
			PlayTuneLaSalle();
			break;
		case 81:
			PlayTuneMario(1);
			break;
		case 89:
			PlayTuneMegalovania();
			break;
		case 99: //Debug
			PlayNote(E, 3 - enableDebug, 200, 2);
			enableDebug = enableDebug ? false : true; //switch
			cout << "Debug " << enableDebug << endl;
			break;
		}
		wager = ValidateWager(wager, player); //check if wager is not invalid
	}
	return wager;
}
//Prints the roll as is or in an Ascending order but Value is first displayed for Pairs
void PrintRoll(Roll roll, bool sort = false, bool quick = false) {
	if (sort) {
		//Sort Dice in Ascending order if not PAIRED
		if (roll.rank != 3) {
			for (int i = 0; i < roll.size; i++) {
				int check = roll.dice[i];
				int swapIndex = i;
				for (int ii = i; ii < roll.size; ii++) {
					//Find number greater than check then store that
					if (roll.dice[ii] < check) {
						check = roll.dice[ii];
						swapIndex = ii;
					}
				}
				//If check is not equal to dice[i] start swapping
				if (roll.dice[i] != check) {
					roll.dice[swapIndex] = roll.dice[i];
					roll.dice[i] = check;
				}
			}
		}
		else {
			//Let value be the first number then the pairs
			roll.dice[0] = roll.value;
			roll.dice[1] = roll.paired;
			roll.dice[2] = roll.paired;
		}
	}
	for (int i = 0; i < roll.size; i++) {
		Sleep(DEFAULT_TIME / (1 + (quick)));
		PlayNote(C, roll.dice[i] + 1, 200); //Each digit, different octave
		cout << roll.dice[i] << " ";
	}
	return;
}
//Debug purposes, inputing 0 makes roll a Pisser
Roll PlaceDice(Roll roll) {
	for (int i = 0; i < roll.size; i++) {
		int num = -1;
		while (num == -1) {
			cout << "Input Value for dice[" << i << "]: ";
			num = _getch();
			num = num - 48; //Fix
			cout << num << endl;
		}
		if (num == 0) { //Pisser
			for (int i = 0; i < roll.size; i++) {
				roll.dice[i] = 0;
			}
			return roll;
		}
		roll.dice[i] = num;
	}
	return roll;
}
//Evaluates the roll and give its values
Roll EvaluateDice(Roll roll) {
	if (roll.dice[0] == 0) { //Pisser check for Debug
		roll.rank = 0;
		roll.type = Pisser;
		return roll;
	}
	//Find Tripled/Paired numbers
	int sameNums = 0;
	for (int i = 0; i < roll.size; i++) {
		int check = roll.dice[i];
		for (int ii = i + 1; ii < roll.size; ii++) {
			if (check == roll.dice[ii]) {
				sameNums++;
			}
		}
		//TRIPLE if number == all but not a 1
		if ((sameNums == 2) && (check != 1)) {
			roll.rank = 5;
			roll.value = roll.dice[i];
			roll.type = Triple;
			return roll;
		}
		//PAIR if only 1 number is the same
		if (sameNums == 1) {
			roll.rank = 3;
			roll.paired = roll.dice[i];
			//Find number != paired and set that as value
			for (int ii = 0; ii < roll.size; ii++) {
				if (roll.paired != roll.dice[ii]) {
					roll.value = roll.dice[ii];
					roll.type = Pairs;
					return roll;
				}
			}
		}
	}
	int sum = 0;
	for (int i = 0; i < roll.size; i++) {
		sum += roll.dice[i]; 
	}
	switch (sum) {
	case 3: //1+1+1
		roll.rank = 6;
		roll.type = SnakeEyes;
		break;
	case 6: //1+2+3
		roll.rank = 1;
		roll.type = Peasant;
		break;
	case 15: //4+5+6
		roll.rank = 4;
		roll.type = Royal;
		break;
	default: //Everything else
		roll.rank = 2;
		roll.type = Bust;
		break;
	}
	return roll;
}
//Recursively calls itself when roll is a bust until maximum retries is reached.
Roll RollDice(int retries, User user, bool enableDebug = false) {
	Roll newRoll;
	switch (retries) {
	case 3:
		cout << user.name << " is throwing the dice." << endl;
		break;
	case 2:
		cout << user.name << " is throwing the dice again." << endl;
		break;
	case 1:
		cout << user.name << " is throwing the dice for the third time." << endl;
		break;
	default:
		cout << "Error on RollDice" << endl;
		system("pause");
		break;
	}
	if (enableDebug) { //Debug Check
		newRoll = PlaceDice(newRoll);
		newRoll = EvaluateDice(newRoll);
		return newRoll;
	}
	cout << "Rolling . . ." << endl;
	if (PISSER_CHANCE >= rand() % 101) { //Pisser check
		newRoll.rank = 0;
		newRoll.type = Pisser;
		return newRoll;
	}
	//Roll amount of dice based on size
	for (int i = 0; i < newRoll.size; i++) {
		newRoll.dice[i] = (rand() % 6) + 1;
		Sleep(DEFAULT_TIME);
		PlayNote(C, newRoll.dice[i] + 1, 200); //Each digit, different octave
		cout << newRoll.dice[i] << " ";
	}
	newRoll = EvaluateDice(newRoll);
	if ((newRoll.rank == 2) && (retries > 1)) { //if Bust and retries greater than 1
		cout << " - Bust!" << endl;
		cout << endl;
		return RollDice(retries - 1, user);
	}
	cout << endl;	
	return newRoll;
}
//Prints the Type of the Roll and play a tune based on rank
void ShowRoll(Roll roll) {
	Sleep(DEFAULT_TIME);
	cout << endl;
	cout << DICE_TYPE[roll.rank] << ": ";
	PrintRoll(roll, true);
	cout << endl;
	if (roll.rank == 3 || roll.rank == 5) { //Show Value when Triples or Paired
		cout << "Value : " << roll.value << endl;
	}	
	PlayTuneDefault(roll.rank);
	return;
}
//Compare Rolls and return an int. No compare needed if dealer got a pisser. (0 - Draw, 1 - Dealer Win, 2 - Player Win)
int CompareRoll(Roll dealerRoll, Roll playerRoll) {
	//Instant win for Player if Dealer is Pisser
	if (dealerRoll.rank == 0) { return 2; }
	if (dealerRoll.rank == playerRoll.rank) { // Both has the same ranks
		if (dealerRoll.rank == 6) { return 0; }	// Both Snake Eyes
		//If pairs or triples, highest value wins
		if (dealerRoll.value > playerRoll.value) { return 1; }
		return 2; //Player wins on Bust, Peasant, Triples and Pairs with same or greater value
	}
	if (dealerRoll.rank > playerRoll.rank) { //If Dealer has higher rank they win unless...
		//Exclusive Draw, Player Pisser while Dealer is Bust or Peasant
		if ((playerRoll.rank == 0) && ((dealerRoll.rank == 2) || (dealerRoll.rank == 1))) { return 0; }
		return 1;
	}
	return 2; //Everything else is win for Player
}
//Display comparison, and the result
void DisplayResult(int result, User dealerUser, User playerUser) {
	//If dealer is pisser, no need to compare
	if (dealerUser.roll.rank != 0) {
		//Dice values compare
		PrintRoll(dealerUser.roll, true, true);
		cout << "VS ";
		PrintRoll(playerUser.roll, true, true);
		cout << endl;
		//Rank compare
		cout << DICE_TYPE[dealerUser.roll.rank] << " VS " << DICE_TYPE[playerUser.roll.rank] << endl;
		cout << endl;
		//If same Rank, Value compare
		if ((dealerUser.roll.rank == playerUser.roll.rank) && ((playerUser.roll.rank == 3) || (playerUser.roll.rank == 5))) {
			cout << "Value: ";
			if (dealerUser.roll.value > playerUser.roll.value) {
				cout << dealerUser.roll.value << " > " << playerUser.roll.value << endl;
				cout << endl;
			}
			else {
				cout << dealerUser.roll.value << " < " << playerUser.roll.value << endl;
				cout << endl;
			}
		}
	}
	switch (result) {
	case 0:
		cout << "DRAW" << endl;	
		break;
	case 1:
		cout << dealerUser.name << " WON!" << endl;
		break;
	case 2:
		cout << playerUser.name << " WON!" << endl;
		break;
	}
	PlayTuneDefault(7 + result);
	return;
}
//Return the payout based on result
int GivePayout(int result, User player, User dealer) {
	int winnings = player.wager;
	switch (result) {
	case 0: //Draw - Get nothing
		cout << "It's a draw.";
		return 0;
		break;
	case 1: //Lose - Reduce money based on wager 
		if (player.roll.rank == 1) { winnings *= player.roll.type; } //if player is peasant has to pay twice	
		cout << player.name << " has to pay " << winnings << " Perico to " << dealer.name;
		winnings *= -1 ; //Negative for substraction
		break;
	case 2: //Win
		winnings *= player.roll.type;
		cout << "Wager: " << player.wager << ", Multiplier: " << player.roll.type << endl;
		cout << player.name << " won " << winnings << " Perico.";
		break;
	default:
		cout << "INVALID RESULT - " << result;
		system("pause");
		break;
	}
	return winnings;
}
//Return an int based on the ammount of money
int EvaluateEnding(int curMoney) {
	//Game ends sooner due to lack of money
	if (curMoney < 0) {	return 0; } //Worst Ending
	if (curMoney < MIN_WAGER) {	return 1; } //Bad Ending
	//Game reached MAX_ROUNDS
	if (curMoney < 90000) { return 2; } //Meh ending
	else if (curMoney > 500000) { return 4; } //Best Ending
	else { return 3; } //Good Ending
}
//Display Ending based on the evaluation
void DisplayEnding(int evaluation, User player, User dealer) {
	switch (evaluation) {
	case 0: //Worse
		cout << player.name << "-san went home with a debt of " << player.money * -1 << " Perico to " << dealer.name << endl;
		cout << endl;
		cout << "WORST ENDING!!" << endl;
		PlayTuneMario(3);
		break;
	case 1: //Bad Ending
		cout << player.name << "-san left with only " << player.money << " Perico left.\nIt wasn't even enough for the minimum bet." << endl;
		cout << endl;
		cout << "BAD ENDING!" << endl;
		PlayTuneMario(0);
		break;
	case 2: //Meh
		cout << player.name << "-san left the with " << player.money << " Perico.\nHe returned with less than he started with.\nIt certainely wasn't worth it." << endl;
		cout << endl;
		cout << "Meh Ending" << endl;
		break;
	case 3: //Good
		cout << player.name << "-san came back more than he started by having " << player.money << " Perico.\nHe felt going back for another round!" << endl;
		cout << endl;
		cout << "GOOD ENDING!" << endl;
		PlayTuneMario(1);
		break;
	case 4: //Best
		cout << player.name << "-san got " << player.money << " Perico. He got half a million!" << endl;
		cout << "He thought about spending it on blackjacks and hookers." << endl;
		cout << endl;
		cout << "BEST ENDING!!" << endl;
		PlayTuneMario(2);
		break;
	default:
		cout << "Invalid Value on Ending evaluation!";
		system("pause");
		break;
	}
	cout << endl;
	cout << "GAME OVER" << endl;
	return;
}
//Check if player has enough money for next round, if no money ask if they want to retry the game.
int CheckUserMoney(User player, User dealer, bool allowRestart) {
	if (player.money >= MIN_WAGER) { return 1; } 
	if (!allowRestart) { return MAX_ROUND; }
	cout << endl;
	cout << dealer.name << ": Ah, " << player.name << ", You don't have enough Perico..." << endl;
	cout << endl;
	cout << "Retry? (y/n)" << endl;
	int choice = -1;
	while ((choice != 'y') && (choice != 'n')) {
		choice = _getch();
	}
	if (choice == 'y') {
		return 0; //Restart the round
	}
	else { return MAX_ROUND; } //End game early
}
//Start up Sequence, Windows XP start up tune
void StartUpSequence(bool enable) {
	if (!enable) return;
	cout << "Jerry Presents";
	PlayTuneDefault(32);
	cout << " - UNDERGROUND CHINCHINRO!" << endl;
	system("pause");
	return;
}
//Print the text to show a bunch of information
void PrintInfoText(int curRound, int curMoney, int wager, bool clearScreen) {
	if (clearScreen) { system("cls"); }
	cout << "Round: " << curRound << " / 10" << endl;
	cout << "You have: ";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	GetConsoleScreenBufferInfo(hConsole, &csbInfo);
	int lastColor = csbInfo.wAttributes;
	int color;
	if (curMoney < 60000) { color = 14; } //Yellow
	else if (curMoney < 30000) { color = 12; } //Red
	else { color = 11; }  //Light-Blue
	SetConsoleTextAttribute(hConsole, color);
	cout << curMoney << " Perica" << endl;
	SetConsoleTextAttribute(hConsole, lastColor);
	if (wager != 0) {
		cout << "Your wager is: " << wager << " Perica" << endl;
	}
	else { cout << endl; } 
	cout << endl;
}
#pragma endregion

int main() {
	//Initialization
	srand(time(NULL)); //Randomize Seed
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //Set default color of text
	User dealerUser = { "OTSUKI" };
	User playerUser = { "KAIJI" , STARTING_MONEY };
	
	StartUpSequence(true);

	//Game Loop
	while (MAX_ROUND > curRound) {
		curRound++;
		Roll newRoll; //Give users new rolls with default values
		dealerUser.roll = newRoll;
		playerUser.roll = newRoll;

		//Phase 1 - Player Bets/Wager
		PrintInfoText(curRound, playerUser.money, 0, true);	
		playerUser.wager = DoWager(dealerUser, playerUser);

		//Phase 2 - Dealer Rolls
		PrintInfoText(curRound, playerUser.money, playerUser.wager, true);		
		dealerUser.roll = RollDice(MAX_BUST, dealerUser, enableDebug);
		ShowRoll(dealerUser.roll);
		system("pause");

		//If Dealer rolled a Pisser skip Player Roll Phase
		if (dealerUser.roll.rank != 0) {
			//Phase 3 - Player Rolls
			PrintInfoText(curRound, playerUser.money, playerUser.wager, true);
			playerUser.roll = RollDice(MAX_BUST, playerUser, enableDebug);
			ShowRoll(playerUser.roll);
			system("pause");
		}

		//Phase 4 - Comparison/Results
		PrintInfoText(curRound, playerUser.money, playerUser.wager, true);
		cout << "-------RESULT---------" << endl; 
		int result = CompareRoll(dealerUser.roll, playerUser.roll);
		DisplayResult(result, dealerUser, playerUser);

		//Phase 5 - Payout
		cout << endl;
		cout << "-------PAYOUT---------" << endl;
		playerUser.money += GivePayout(result, playerUser, dealerUser);
		cout << endl;

		system("pause");
		system("cls");
		curRound *= CheckUserMoney(playerUser, dealerUser, false); //Check money of user
		if (curRound == 0) { playerUser.money = STARTING_MONEY; } //If player restarted
	}
	//Phase 6 - Ending
	cout << "-------ENDING---------" << endl;
	cout << endl;
	int endingResult = EvaluateEnding(playerUser.money);
	DisplayEnding(endingResult, playerUser, dealerUser);

	system("pause");
	cout << endl;
	return 0;
}