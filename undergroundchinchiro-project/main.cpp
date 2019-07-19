#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "printInfoText.h"
#include "playTuneMario.h"
#include "playNote.h"
#include "playTuneLaSalle.h"
#include "playTuneMegalovania.h"

using namespace std;

//FINAL PROJECT - undergroundchinchiro-project

//Constants
int STARTING_MONEY = 90000; //Amount of money player starts
float PISSER_CHANCE = 5; //A simulated chance of dice going out of bounds
int MIN_WAGER = 100; // The minimum allowabled wager
int MAX_ROUND = 10; //Max amount of rounds
int MAX_BUST = 3; //Max amount of busts before moving on
int DEFAULT_TIME = 200; //Default milliseconds to wait to show next dice 
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
bool includeIntro = true; //Enable to include intro scene
bool includeStartUp = true; //Enable opening tune
bool enableDebug = false;
int curRound = 0; //current round

//The Roll struct
struct Roll {
	string type = "None"; //Snake Eyes, Triples, Royal, Pairs, Bust, Peasant, Pisser
	int rank = -1; //Snake Eyes(6), Triples(5), Royal(4), Pairs(3), Bust(2), Peasant(1), Pisser(0)
	int value = -1; //Number of the roll for Triples but for Pairs is the unpaired number
	int paired = -1; //Number of the paired number in Pairs
	int dice[3] = { 0, 0, 0 }; //The dice array 
};

//The Users struct, includes the Roll
struct User {	
	string name; //Name of the User
	int money = 0; //Amount of money this user has
	int wager = 0; //Amount wagered/bet
	Roll roll; //Roll of the user
};

#pragma region All Functions
//Checks player's bet against a number of factors (Less than MIN_WAGER, more than their Current Money, or a char)
int ValidateWager(int bet, User dealer, User player) {
	//Incase player inputs a char
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	if (bet < 1) {
		cout << endl;
		cout << dealer.name << ": Focus on the game, " << player.name << "-san" << endl;
		return 0;
	}
	else if (bet > player.money) {
		cout << endl;
		cout << dealer.name << ": You only have " << player.money << " Perico, " << player.name << "-san" << endl;
		return 0;
	}
	else if (bet < MIN_WAGER) {
		cout << endl;
		cout << dealer.name << ": The minimum wager is " << MIN_WAGER << " Perico, " << player.name << "-san" << endl;
		return 0;
	}
	//If none of the above
	return bet;
}
//Asks player how much to bet then store that bet as their wager if valid.
User DoWager(User dealer, User player) {
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
			bet = player.wager;
			break;
		case 3: //ALL IN
			bet = player.money;
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
		case 99: //Debug
			PlayNote('E', 3 - enableDebug, 200, false, 2);
			enableDebug = enableDebug ? false : true; //switch
			cout << "Debug " << enableDebug << endl;
			break;
		}
		bet = ValidateWager(bet, dealer, player); //check if wager is not invalid
	}
	player.wager = bet; //Set wager as bet
	return player; //Return updated User
}
//Roll n amount of dice depending on the dice array size, returns new Roll struct based on results.
Roll RollDice() {
	Roll newRoll;
	cout << "Rolling . . ." << endl;
	//Pisser check
	if (PISSER_CHANCE >= rand() % 101) {
		newRoll.type = "Pisser";
		newRoll.rank = 0;
		return newRoll;
	}
	//Get dice array size, byte of the array divided by byte of its element
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
	//For the remaining
	switch (sum) {
	case 3: //1+1+1
		newRoll.type = "Snake-Eyes";
		newRoll.rank = 6;
		break;
	case 6: //1+2+3
		newRoll.type = "Peasant";
		newRoll.rank = 1;
		break;
	case 15: //4+5+6
		newRoll.type = "Royal";
		newRoll.rank = 4;
		break;
	default: //Everything else
		newRoll.type = "Bust";
		newRoll.rank = 2;
		break;
	}
	return newRoll;
}
//Prints the roll as is or in an Ascending order but Value is first displayed for Pairs
void PrintRoll(Roll roll, bool sort = false) {
	int size = sizeof(roll.dice) / sizeof(roll.dice[0]);
	if (sort) {
		//Sort Dice in Ascending order if not PAIRED
		if (roll.type != "Pairs") {
			for (int i = 0; i < size; i++) {
				int check = roll.dice[i];
				int swapIndex = i;
				for (int ii = i; ii < size; ii++) {
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
	for (int i = 0; i < size; i++) {
		Sleep(DEFAULT_TIME);
		PlayNote('C', roll.dice[i] + 1, 200); //Each digit, different octave
		cout << roll.dice[i] << " ";
	}
}
//Debug - For visual purposes
Roll PlaceDice(Roll newRoll, int dice1, int dice2, int dice3) {
	newRoll.dice[0] = dice1;
	PlayNote('D', dice1, 200);
	newRoll.dice[1] = dice2;
	PlayNote('D', dice2, 200);
	newRoll.dice[2] = dice3;
	PlayNote('D', dice3, 200);
	return newRoll;
}
//Roll dice consecutively until reached the max
Roll RollConsecDice(User user, int max, bool enableDebug = false) {
	int rank = 1;
	int value = 1;
	int retries = 0;
	Roll newRoll;
	if (!enableDebug) {
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
	else { //Debug
		cout << "Input rank: ";
		cin >> rank;
		if ((rank == 5) && (rank == 3)) {
			cout << "Input value: ";
			cin >> value;
		}
		cout << "Placing Dice Manually. . ." << endl;
		Sleep(DEFAULT_TIME);
		int size = sizeof(newRoll.dice) / sizeof(newRoll.dice[0]);
		switch (rank) {
		case 6:
			newRoll.type = "Snake Eyes";
			newRoll = PlaceDice(newRoll, 1, 1, 1);
			break;
		case 5:
			newRoll.type = "Triples";
			newRoll.value = value;
			newRoll = PlaceDice(newRoll, value, value, value);
			break;
		case 4:
			newRoll.type = "Royal";
			newRoll = PlaceDice(newRoll, 4, 5, 6);
			break;
		case 3:
			newRoll.type = "Pairs";
			newRoll.value = value;
			newRoll.paired = 3;
			newRoll = PlaceDice(newRoll, value, 3, 3);
			break;
		case 2:
			newRoll.type = "Bust";
			newRoll = PlaceDice(newRoll, 1, 4, 3);
			break;
		case 1:
			newRoll.type = "Peasant";
			newRoll = PlaceDice(newRoll, 1, 2, 3);
			break;
		case 0:
			newRoll.type = "Pisser";
			newRoll = PlaceDice(newRoll, 0, 0, 0);
			break;
		default:
			cout << "Invalid Rank" << endl;
			system("pause");
			break;
		}
		newRoll.rank = rank;
		return newRoll;
	}
}
//Prints the Type of the Roll and some tunes
void ShowRoll(Roll roll) {
	Sleep(DEFAULT_TIME);
	cout << endl;
	cout << "Roll is a " << roll.type << " -> ";
	PrintRoll(roll, true);
	switch (roll.rank) {
	case 0: //Pisser
		Sleep(DEFAULT_TIME);
		PlayNote('C', 3, 200);
		PlayNote('C', 2, 200);
		break;
	case 1: //Peasant
		cout << endl;
		PlayNote('C', 3, 200);
		PlayNote('C', 2, 200);
		break;
	case 2: //Bust
		cout << endl;
		PlayNote('C', 3, 200);
		PlayNote('C', 2, 200);
		break;
	case 3: //Pairs
		cout << endl;
		PlayNote('C', 3, 200);
		PlayNote('C', 4, 500);
		PlayNote('C', 5, 700);
		break;
	case 4: //Royal
		PlayNote('C', 4, 400);
		PlayNote('C', 5, 200);
		PlayNote('C', 5, 200);
		PlayNote('C', 6, 700);
		cout << endl;
		break;
	case 5: //Triples
		PlayNote('C', 4, 400);
		PlayNote('D', 5, 400);
		PlayNote('E', 5, 400);
		break;
	case 6: //Snake Eyes
		PlayNote('C', 4, 400);
		PlayNote('B', 3, 400);
		PlayNote('A', 3, 400);
		break;
	default:
		cout << "\a";
		cout << "Dice Roll has unknown rank value: " << roll.rank << endl;
		system("pause");
		break;
	}
	cout << endl;
}
//Compare Rolls and return an int. No compare needed if dealer got a pisser.
int CompareRoll(Roll dealerRoll, Roll playerRoll) {
	//Instant win for player, pisser
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
		if (dealerRoll.rank == 6) {
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
//Display comparison, and the result
void DisplayResult(int result, User dealerUser, User playerUser) {
	//If dealer is pisser, no need to compare
	if (dealerUser.roll.rank != 0) {
		//Dice values compare
		PrintRoll(dealerUser.roll, true);
		cout << "VS ";
		PrintRoll(playerUser.roll, true);
		cout << endl;
		//Type compare
		cout << dealerUser.roll.type << " VS " << playerUser.roll.type << endl;
		cout << endl;
		//Pairs and Triples, Value compare
		if ((dealerUser.roll.rank == playerUser.roll.rank) && ((playerUser.roll.rank == 3) || (playerUser.roll.rank == 5))) {
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
//Return the payout based on result
int GivePayout(int result, User player, User dealer) {
	int winnings = player.wager;
	switch (result) {
	case 0: //Draw
		cout << "It's a draw";
		return 0;
		break;
	case 1: //Lose
			//Reduce money based on wager but if player is peasant
		if (player.roll.rank == 1) {
			//has to pay twice
			winnings *= PEASANT_MULT;
		}
		cout << player.name << " has to pay " << winnings << " Perico to " << dealer.name;
		winnings *= -1; //Negative for substraction
		break;
	case 2: //Win
		switch (player.roll.rank) {
		case 6: //Snake Eyes
			winnings *= SNAKE_EYES_MULT;
			break;
		case 5: //Triples
			winnings *= TRIPLES_MULT;
			break;
		case 4: //Royal
			winnings *= ROYAL_MULT;
			break;
		case 3: //Pair
			winnings *= PAIRS_MULT;
			break;
		default:
			//ANYTHING ELSE
			player.money += winnings;
			break;
		}
		cout << player.name << " won " << winnings << " Perico.";
		break;
	default:
		cout << "INVALID RESULT" << result;
		break;
	}
	return winnings;
}
//Return an int based on the ammount of money
int EvaluateEnding(int curMoney) {
	//When game ends sooner because of money
	if (curMoney < 0) {
		//Worst Ending
		return 0;
	}
	if (curMoney < MIN_WAGER) {
		//Bad Ending
		return 1;
	}
	if (curMoney == STARTING_MONEY) {
		return 5;
	}
	//Finished game
	if (curMoney < 90000) {
		//Meh ending
		return 2;
	}
	else if (curMoney > 500000) {
		//Best Ending
		return 4;
	}
	else {
		//Good Ending
		return 3;
	}
}
//Display Ending based on the evaluation
void DisplayEnding(int evaluation, User player, User dealer) {
	switch (evaluation) {
	case 0: //Worse
		cout << player.name << "-san went home with a debt of " << player.money * -1 << " Perico to " << dealer.name << endl;
		cout << endl;
		cout << "WORST ENDING!!" << endl;
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
		break;
	case 4: //Best
		cout << player.name << "-san got " << player.money << " Perico. He got half a million!" << endl;
		cout << "He thought about spending it on blackjacks and hookers." << endl;
		cout << endl;
		cout << "BEST ENDING!!" << endl;
		break;
	case 5: //Same Money or Left
		cout << player.name << "-san managed to keep " << player.money << " Perico." << endl;
		cout << "He left happy and satisfied that he didn't lose anything." << endl;
		cout << endl;
		cout << "NORMAL ENDING!!" << endl;
		break;
	}
	cout << endl;
	cout << "GAME OVER" << endl;
}
//Check if player has enough money for next round, if no money asks for if they want to retry the game.
void CheckUserMoney(User player, User dealer) {
	if (player.money < MIN_WAGER) {
		cout << endl;
		cout << dealer.name << ": Ah, " << player.name << "-san, You don't have enough Perico..." << endl;
		cout << endl;
		cout << "Retry? (y/n)" << endl;
		int choice = ' ';
		while ((choice != 'y') && (choice != 'n')) {
			choice = _getch();
		}
		if (choice == 'y') {
			player.money = STARTING_MONEY; //Give money back
			curRound = 0; //Restart the round
		}
		else {
			curRound = MAX_ROUND; //End game early
		}
		cout << endl;
	}

}
//Start up Sequence
void StartUpSequence(bool enable) {
	if (enable) {
		cout << "Jerry Presents" << endl;
		PlayNote('D', 6, 400);
		PlayNote('C', 5, 200);
		PlayNote('A', 5, 300);
		cout << endl;
		PlayNote('G', 5, 500);
		PlayNote('D', 6, 200);
		cout << "UNDERGROUND CHINCHINRO!" << endl;
		PlayNote('A', 5, 700);
		system("pause");
	}
}
//Start the Introduction or Tutorial
void StartIntroduction(bool enable, User player) {
	system("cls");
	bool wantPlay = true;
	while ((ch != 'y') && (ch != 'n')) {
		cout << player.name << "-san, do you want to play the Underground Chinchiro? (y/n)" << endl;
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
		curRound = MAX_ROUND;
		wantPlay = false;
		system("cls");
		//cout << "GAME OVER" << endl;
		//cout << player.name << " kept his " << player.money << " Perico and lived happily every after." << endl;
		//system("pause");
	}

	//Tutorial --- in progress
	if (wantPlay) {
		if (ch == 'y') {
			system("cls");
			cout << "Well, listen closely " << player.name << "." << endl;
			system("pause");
			cout << "I will be only dealer this time and try to get as much money as possible in 10 rounds. " << player.name << "." << endl;
			system("pause");
			cout << "It's simple. We throw 3 dice and compare our rolls to each other." << endl;
			system("pause");
			cout << "Goal is to get Pairs or Triples, Triples is higher than Pairs by the way." << endl;
			system("pause");
			cout << "For pairs the other number is the value to compare for that roll." << endl;
			system("pause");
			cout << "And... well, I think it's much better to learn as we play." << endl;
			system("pause");
			cout << "I promize I won't cheat this time." << endl;
			system("pause");
			cout << "Ah, Be careful in throwing the dice alright?" << endl;
			system("pause");
			cout << "Let's go!" << endl;
			system("pause");
			cout << "Hints:\nBet: 1 - Minimum Wager, 2 - Last Wager, 3 - All-In, 4 - 20,000" << endl;
			system("pause");
		}
		else if (ch == 'n') {
			cout << "Well, let's start then. This time however I'll be the only dealer. Try to get as much money as possible in 10 rounds." << endl;
			system("pause");
			cout << "Hints:\nBet: 1 - Minimum Wager, 2 - Last Wager, 3 - All-In, 4 - 20,000" << endl;
			system("pause");
		}
	}
}
#pragma endregion

int main() {
	srand(time(NULL)); //Randomize Seed
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //Set default color of text

	//Initialization
	User dealerUser = {"OTSUKI"};
	User playerUser = { "KAIJI" , STARTING_MONEY };

	PlayTuneMegalovania();

	//WINDOWS XP START UP Sound OPENING if true
	StartUpSequence(includeStartUp);
	
	//Introduction runs if includeIntro is true
	StartIntroduction(includeIntro, playerUser);

	//Game Loop
	while (MAX_ROUND > curRound) {
		//Increase or Next Round
		curRound++;

		//RESET Dice values
		for (int i = 0; i < 3; i++) {
			dealerUser.roll.dice[i] = 0;
			playerUser.roll.dice[i] = 0;
		}

		//For new round set wager display to 0
		PrintInfoText(curRound, playerUser.money, 0, true);
		cout << endl;

		//Phase 1 - Player Bets/Wager
		playerUser = DoWager(dealerUser, playerUser);

		//Clear to print new info text with the wager
		PrintInfoText(curRound, playerUser.money, playerUser.wager, true);
		cout << endl;

		//Phase 2 - Dealer Rolls

		dealerUser.roll = RollConsecDice(dealerUser, MAX_BUST, enableDebug);
		ShowRoll(dealerUser.roll);
		system("pause");
		cout << endl;

		PrintInfoText(curRound, playerUser.money, playerUser.wager, true);
		cout << endl;

		//If Dealer didnt roll a Pisser else skip Player roll phase
		if (dealerUser.roll.rank != 0) {
			//Phase 3 - Player Rolls
			playerUser.roll = RollConsecDice(playerUser, MAX_BUST, enableDebug);
			ShowRoll(playerUser.roll);
			system("pause");
			cout << endl;
		}

		PrintInfoText(curRound, playerUser.money, playerUser.wager, true);
		cout << endl;

		cout << "-------RESULT---------" << endl; //Phase 4 - Results/Compare
		int result; //0 Draw, 1 - Dealer win. 2 - Player win	
		result = CompareRoll(dealerUser.roll, playerUser.roll);
		DisplayResult(result, dealerUser, playerUser);

		//Phase 5 - Payout
		cout << endl;
		cout << "-------PAYOUT---------" << endl;
		playerUser.money += GivePayout(result, playerUser, dealerUser);
		cout << endl;

		system("pause");
		system("cls");
		//Check money of users
		CheckUserMoney(playerUser, dealerUser);
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