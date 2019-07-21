#include "playNote.h"

void PlayTuneMario(int type) {
	switch (type) {
	case 0://Game Over
		PlayNote(C, 5, 200);
		Sleep(100);
		PlayNote(G, 4, 200);
		Sleep(100);
		PlayNote(E, 4, 400);
		PlayNote(A, 4, 300);
		PlayNote(B, 4, 300);
		PlayNote(A, 4, 300);
		PlayNote(Gs, 4, 400);
		PlayNote(As, 4, 400);
		PlayNote(Gs, 4, 400);
		PlayNote(E, 4, 200);
		PlayNote(D, 4, 200);
		PlayNote(E, 4, 600);
		break;
	case 1: //Main - credits to Guest_ub3rphr34k_* in rohitab.com
		PlayNote(Fs, 6, 200);
		PlayNote(G, 6, 200, 3);

		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200, 3);

		PlayNote(Fs, 4, 200);
		PlayNote(G, 4, 200);
		PlayNote(Fs, 4, 200);
		PlayNote(G, 4, 200);
		PlayNote(G, 4, 400);
		PlayNote(G, 3, 400);

		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200, 2);
		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200, 2);
		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200);
		PlayNote(A, 5, 200);
		PlayNote(Gs, 5, 200);
		PlayNote(A, 5, 200);
		PlayNote(B, 5, 400);

		PlayNote(A, 5, 200);
		PlayNote(G, 5, 200);
		PlayNote(F, 5, 200);
		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200, 2);
		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200, 2);
		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200);
		PlayNote(A, 5, 200);
		PlayNote(Gs, 5, 200);
		PlayNote(A, 5, 200);
		PlayNote(B, 5, 400);

		Sleep(200);
		//High pitch
		//Beep(1108, 10);
		PlayNote(D, 6, 200);
		//Beep(1480, 10);
		PlayNote(G, 6, 200);

		Sleep(200);

		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200, 2);
		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200, 2);
		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200);
		PlayNote(A, 5, 200);
		PlayNote(Gs, 5, 200);
		PlayNote(A, 5, 200);
		PlayNote(B, 5, 400);

		PlayNote(A, 5, 200);
		PlayNote(G, 5, 200);
		PlayNote(F, 5, 200);

		PlayNote(E, 5, 200);
		PlayNote(F, 5, 200);
		PlayNote(G, 5, 200);
		PlayNote(A, 5, 400);
		PlayNote(G, 5, 200);
		PlayNote(F, 5, 200);
		PlayNote(E, 5, 200);

		PlayNote(D, 5, 200);
		PlayNote(E, 5, 200);
		PlayNote(F, 5, 200);
		PlayNote(G, 5, 400);
		PlayNote(F, 5, 200);
		PlayNote(E, 5, 200);
		PlayNote(D, 5, 200);

		PlayNote(C, 5, 200);
		PlayNote(D, 5, 200);
		PlayNote(E, 5, 200);
		PlayNote(F, 5, 200);
		PlayNote(E, 5, 200);
		PlayNote(D, 5, 200);
		PlayNote(B, 4, 200);
		PlayNote(C, 5, 200);

		Sleep(400);

		PlayNote(F, 4, 400);
		PlayNote(G, 4, 200);
		PlayNote(E, 4, 200);
		PlayNote(C, 5, 200);
		PlayNote(B, 4, 200);
		PlayNote(As, 4, 200);

		PlayNote(A, 4, 200);
		PlayNote(B, 4, 200);
		PlayNote(C, 5, 200);
		PlayNote(A, 5, 200);
		PlayNote(B, 4, 200);
		PlayNote(A, 5, 200);
		PlayNote(A, 6, 200);
		PlayNote(A, 4, 200);

		PlayNote(G, 4, 200);
		PlayNote(A, 4, 200);
		PlayNote(B, 4, 200);
		PlayNote(G, 5, 200);
		PlayNote(A, 4, 200);
		PlayNote(G, 5, 200);
		PlayNote(G, 6, 200);
		PlayNote(G, 4, 200);

		PlayNote(F, 4, 200);
		PlayNote(G, 4, 200);
		PlayNote(A, 4, 200);
		PlayNote(F, 5, 200);
		PlayNote(Gs, 4, 200);
		PlayNote(F, 5, 200);
		PlayNote(F, 6, 200);
		PlayNote(F, 4, 200);

		PlayNote(E, 4, 200);
		PlayNote(Ds, 4, 200);
		PlayNote(E, 4, 200);
		PlayNote(E, 5, 200);
		PlayNote(F, 5, 200);
		PlayNote(G, 5, 400);

		PlayNote(A, 4, 200);
		PlayNote(B, 4, 200);
		PlayNote(C, 5, 200);
		PlayNote(A, 5, 200);
		PlayNote(B, 4, 200);
		PlayNote(A, 5, 200);
		PlayNote(A, 6, 200);
		PlayNote(A, 4, 200);

		PlayNote(G, 4, 200);
		PlayNote(A, 4, 200);
		PlayNote(B, 4, 200);
		PlayNote(G, 5, 200);
		PlayNote(A, 4, 200);
		PlayNote(G, 5, 200);
		PlayNote(G, 6, 200);
		PlayNote(G, 4, 200);

		PlayNote(F, 4, 200);
		PlayNote(G, 4, 200);
		PlayNote(A, 4, 200);
		PlayNote(F, 5, 200);
		PlayNote(E, 5, 200);
		PlayNote(F, 5, 200);
		PlayNote(Fs, 5, 200);
		PlayNote(G, 5, 200);
		PlayNote(G, 4, 200, 4);
		PlayNote(G, 3, 200, 3);

		PlayNote(Fs, 3, 200);
		PlayNote(G, 3, 200);
		PlayNote(Fs, 3, 200);
		PlayNote(G, 3, 200);
		PlayNote(Gs, 3, 200);
		PlayNote(A, 3, 200);
		PlayNote(As, 3, 200);
		PlayNote(B, 3, 200);
		break;
	case 2: //Rescue
		PlayNote(C, 5, 200);
		PlayNote(G, 4, 200);
		PlayNote(E, 4, 200);
		PlayNote(C, 5, 200);
		PlayNote(G, 4, 200);
		PlayNote(E, 4, 200);
		PlayNote(C, 5, 600);

		PlayNote(Cs, 5, 200);
		PlayNote(Gs, 4, 200);
		PlayNote(F, 4, 200);
		PlayNote(Cs, 5, 200);
		PlayNote(Gs, 4, 200);
		PlayNote(F, 4, 200);
		PlayNote(Cs, 5, 600);

		PlayNote(Ds, 5, 200);
		PlayNote(As, 4, 200);
		PlayNote(G, 4, 200);
		PlayNote(Ds, 5, 200);
		PlayNote(As, 4, 200);
		PlayNote(G, 4, 200);
		PlayNote(Ds, 5, 400);
		PlayNote(F, 5, 300);
		PlayNote(F, 5, 300);
		PlayNote(F, 5, 300);
		PlayNote(G, 5, 900);
		break;
	case 3: //Death
		PlayNote(C, 4, 100);
		PlayNote(Cs, 4, 100);
		PlayNote(D, 4, 100);
		Sleep(400);
		PlayNote(B, 3, 200);
		PlayNote(F, 4, 200);
		Sleep(200);
		PlayNote(F, 4, 200);
		PlayNote(F, 4, 200);
		Sleep(100);
		PlayNote(E, 4, 200);
		Sleep(100);
		PlayNote(D, 4, 200);
		Sleep(100);
		PlayNote(C, 4, 200);

		PlayNote(E, 3, 200);
		PlayNote(G, 2, 200);
		PlayNote(E, 3, 200);
		PlayNote(C, 3, 200);
		break;

	default:
		cout << "\a";
		cout << "No corresponding value: " << type << endl;
		system("pause");
		break;
	}
}