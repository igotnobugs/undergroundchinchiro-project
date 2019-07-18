#include <windows.h>
#include "playNote.h"

void PlayTuneLaSalle() {
	PlayNote('D', 6, 600); //Hail
	PlayNote('G', 5, 600); //Hail

	PlayNote('D', 6, 400); //Al
	PlayNote('G', 5, 400); //Ma
	PlayNote('E', 5, 400); //Ma
	PlayNote('G', 5, 400); //TER

	PlayNote('D', 6, 500); //Hail
	Sleep(100);
	PlayNote('D', 6, 200); //To
	PlayNote('E', 6, 500); //De
	Sleep(100);
	PlayNote('E', 6, 200); //La
	PlayNote('F', 6, 700); //Salle

	PlayNote('F', 6, 200); //We'll
	PlayNote('F', 6, 600); //Hold
	PlayNote('C', 6, 200); //Your
	PlayNote('C', 6, 400); //Ba
	PlayNote('E', 6, 400); //nner
	PlayNote('D', 6, 400); //High
	PlayNote('C', 6, 400); //And
	PlayNote('B', 5, 400); //Bright
	Sleep(200);
	PlayNote('B', 5, 400); //A
	PlayNote('E', 6, 400); //Shield
	PlayNote('B', 5, 400); //Of
	PlayNote('C', 6, 400); //Green
	PlayNote('D', 6, 400); //And
	PlayNote('E', 6, 600); //White
	Sleep(200);
	PlayNote('G', 5, 400);
	PlayNote('D', 6, 600);
	PlayNote('G', 5, 300);
	PlayNote('E', 5, 400);
	PlayNote('G', 5, 400);
	PlayNote('D', 6, 400);
	PlayNote('G', 5, 400);
	PlayNote('E', 5, 400);
	Sleep(200);
	PlayNote('G', 5, 400);
	PlayNote('D', 6, 600);
	PlayNote('D', 6, 300);
	PlayNote('E', 6, 400);
	Sleep(200);
	PlayNote('E', 6, 400);
	PlayNote('F', 6, 700);
	Sleep(300);
	PlayNote('G', 6, 400);
	PlayNote('G', 6, 300);
	PlayNote('C', 6, 400);
	PlayNote('D', 6, 400);
	PlayNote('E', 6, 400);
	PlayNote('C', 6, 600);
	PlayNote('G', 5, 400);
	PlayNote('D', 6, 400);
	PlayNote('C', 6, 600);

	PlayNote('B', 5, 600);
	PlayNote('C', 6, 800);
}