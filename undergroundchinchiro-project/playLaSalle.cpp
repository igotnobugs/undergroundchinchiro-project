#include <windows.h>
#include "playNote.h"

void playLaSalle() {
	playNote('D', 6, 600); //Hail
	playNote('G', 5, 600); //Hail

	playNote('D', 6, 400); //Al
	playNote('G', 5, 400); //Ma
	playNote('E', 5, 400); //Ma
	playNote('G', 5, 400); //TER

	playNote('D', 6, 500); //Hail
	Sleep(100);
	playNote('D', 6, 200); //To
	playNote('E', 6, 500); //De
	Sleep(100);
	playNote('E', 6, 200); //La
	playNote('F', 6, 700); //Salle

	playNote('F', 6, 200); //We'll
	playNote('F', 6, 600); //Hold
	playNote('C', 6, 200); //Your
	playNote('C', 6, 400); //Ba
	playNote('E', 6, 400); //nner
	playNote('D', 6, 400); //High
	playNote('C', 6, 400); //And
	playNote('B', 5, 400); //Bright
	Sleep(200);
	playNote('B', 5, 400); //A
	playNote('E', 6, 400); //Shield
	playNote('B', 5, 400); //Of
	playNote('C', 6, 400); //Green
	playNote('D', 6, 400); //And
	playNote('E', 6, 600); //White
	Sleep(200);
	playNote('G', 5, 400);
	playNote('D', 6, 600);
	playNote('G', 5, 300);
	playNote('E', 5, 400);
	playNote('G', 5, 400);
	playNote('D', 6, 400);
	playNote('G', 5, 400);
	playNote('E', 5, 400);
	Sleep(200);
	playNote('G', 5, 400);
	playNote('D', 6, 600);
	playNote('D', 6, 300);
	playNote('E', 6, 400);
	Sleep(200);
	playNote('E', 6, 400);
	playNote('F', 6, 700);
	Sleep(300);
	playNote('G', 6, 400);
	playNote('G', 6, 300);
	playNote('C', 6, 400);
	playNote('D', 6, 400);
	playNote('E', 6, 400);
	playNote('C', 6, 600);
	playNote('G', 5, 400);
	playNote('D', 6, 400);
	playNote('C', 6, 600);

	playNote('B', 5, 600);
	playNote('C', 6, 800);
}