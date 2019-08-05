#include "playNote.h"

void PlayTuneDefault(int type) {
	switch (type) {
	case 0: //Pisser
		PlayNote(C, 3, 200);
		PlayNote(C, 2, 200);
		break;
	case 1: //Peasant
		PlayNote(C, 3, 200);
		PlayNote(C, 2, 200);
		break;
	case 2: //Bust
		PlayNote(C, 3, 200);
		PlayNote(C, 2, 200);
		break;
	case 3: //Pairs
		PlayNote(C, 3, 200);
		PlayNote(C, 4, 500);
		PlayNote(C, 5, 700);
		break;
	case 4: //Royal
		PlayNote(C, 4, 400);
		PlayNote(C, 5, 200);
		PlayNote(C, 5, 200);
		PlayNote(C, 6, 700);
		break;
	case 5: //Triples
		PlayNote(C, 4, 400);
		PlayNote(D, 5, 400);
		PlayNote(E, 5, 400);
		break;
	case 6: //Snake Eyes
		PlayNote(C, 4, 400);
		PlayNote(B, 3, 400);
		PlayNote(A, 3, 400);
		break;
	case 7: //Result - Draw
		PlayNote(C, 3, 200);
		PlayNote(C, 3, 500);
		PlayNote(C, 3, 700);
		break;
	case 8: //Result - Dealer Won
		PlayNote(C, 4, 200);
		PlayNote(C, 3, 500);
		PlayNote(C, 2, 700);
		break;
	case 9: //Result - Player Won
		PlayNote(C, 3, 200);
		PlayNote(C, 3, 300);
		PlayNote(C, 4, 700);
		break;
	case 32://Windows XP Startup Tune
		PlayNote(D, 6, 400);
		PlayNote(C, 5, 200);
		PlayNote(A, 5, 300);
		PlayNote(G, 5, 500);
		PlayNote(D, 6, 200);
		PlayNote(A, 5, 700);
		break;
	default:
		cout << "\a";
		cout << "No corresponding value: " << type << endl;
		system("pause");
		break;
	}
}