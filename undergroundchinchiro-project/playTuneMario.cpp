#include <windows.h>
#include "playNote.h"

void PlayTuneMario(int type) {
	switch (type) {
	case 0://Game Over
		PlayNote('C', 5, 200);
		Sleep(100);
		PlayNote('G', 4, 200);
		Sleep(100);
		PlayNote('E', 4, 400);
		PlayNote('A', 4, 300);
		PlayNote('B', 4, 300);
		PlayNote('A', 4, 300);
		PlayNote('G', 4, 400, true);
		PlayNote('A', 4, 400, true);
		PlayNote('G', 4, 400, true);
		PlayNote('E', 4, 200);
		PlayNote('D', 4, 200);
		PlayNote('E', 4, 600);
		break;
	case 1: //Main - credits to Guest_ub3rphr34k_* in rohitab.com
		PlayNote('F', 6, 200, true);
		PlayNote('G', 6, 200, false, 3);

		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200, false, 3);

		PlayNote('F', 4, 200, true);
		PlayNote('G', 4, 200);
		PlayNote('F', 4, 200, true);
		PlayNote('G', 4, 200);
		PlayNote('G', 4, 400);
		PlayNote('G', 3, 400);

		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200, false, 2);
		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200, false, 2);
		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200);
		PlayNote('A', 5, 200);
		PlayNote('G', 5, 200,true);
		PlayNote('A', 5, 200);
		PlayNote('B', 5, 400);

		PlayNote('A', 5, 200);
		PlayNote('G', 5, 200);
		PlayNote('F', 5, 200);
		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200, false, 2);
		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200, false, 2);
		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200);
		PlayNote('A', 5, 200);
		PlayNote('G', 5, 200,true);
		PlayNote('A', 5, 200);
		PlayNote('B', 5, 400);

		Sleep(200);
		//High pitch
		//Beep(1108, 10);
		PlayNote('D', 6, 200);
		//Beep(1480, 10);
		PlayNote('G', 6, 200);

		Sleep(200);

		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200, false, 2);
		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200, false, 2);
		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200);
		PlayNote('A', 5, 200);
		PlayNote('G', 5, 200, true);
		PlayNote('A', 5, 200);
		PlayNote('B', 5, 400);

		PlayNote('A', 5, 200);
		PlayNote('G', 5, 200);
		PlayNote('F', 5, 200);

		PlayNote('E', 5, 200);
		PlayNote('F', 5, 200);
		PlayNote('G', 5, 200);
		PlayNote('A', 5, 400);
		PlayNote('G', 5, 200);
		PlayNote('F', 5, 200);
		PlayNote('E', 5, 200);

		PlayNote('D', 5, 200);
		PlayNote('E', 5, 200);
		PlayNote('F', 5, 200);
		PlayNote('G', 5, 400);
		PlayNote('F', 5, 200);
		PlayNote('E', 5, 200);
		PlayNote('D', 5, 200);

		PlayNote('C', 5, 200);
		PlayNote('D', 5, 200);
		PlayNote('E', 5, 200);
		PlayNote('F', 5, 200);
		PlayNote('E', 5, 200);
		PlayNote('D', 5, 200);
		PlayNote('B', 4, 200);
		PlayNote('C', 5, 200);

		Sleep(400);

		PlayNote('F', 4, 400);
		PlayNote('G', 4, 200);
		PlayNote('E', 4, 200);
		PlayNote('C', 5, 200);
		PlayNote('B', 4, 200);
		PlayNote('A', 4, 200, true);

		PlayNote('A', 4, 200);
		PlayNote('B', 4, 200);
		PlayNote('C', 5, 200);
		PlayNote('A', 5, 200);
		PlayNote('B', 4, 200);
		PlayNote('A', 5, 200);
		PlayNote('A', 6, 200);
		PlayNote('A', 4, 200);

		PlayNote('G', 4, 200);
		PlayNote('A', 4, 200);
		PlayNote('B', 4, 200);
		PlayNote('G', 5, 200);
		PlayNote('A', 4, 200);
		PlayNote('G', 5, 200);
		PlayNote('G', 6, 200);
		PlayNote('G', 4, 200);

		PlayNote('F', 4, 200);
		PlayNote('G', 4, 200);
		PlayNote('A', 4, 200);
		PlayNote('F', 5, 200);
		PlayNote('G', 4, 200, true);
		PlayNote('F', 5, 200);
		PlayNote('F', 6, 200);
		PlayNote('F', 4, 200);

		PlayNote('E', 4, 200);
		PlayNote('D', 4, 200, true);
		PlayNote('E', 4, 200);
		PlayNote('E', 5, 200);
		PlayNote('F', 5, 200);
		PlayNote('G', 5, 400);

		PlayNote('A', 4, 200);
		PlayNote('B', 4, 200);
		PlayNote('C', 5, 200);
		PlayNote('A', 5, 200);
		PlayNote('B', 4, 200);
		PlayNote('A', 5, 200);
		PlayNote('A', 6, 200);
		PlayNote('A', 4, 200);

		PlayNote('G', 4, 200);
		PlayNote('A', 4, 200);
		PlayNote('B', 4, 200);
		PlayNote('G', 5, 200);
		PlayNote('A', 4, 200);
		PlayNote('G', 5, 200);
		PlayNote('G', 6, 200);
		PlayNote('G', 4, 200);

		PlayNote('F', 4, 200);
		PlayNote('G', 4, 200);
		PlayNote('A', 4, 200);
		PlayNote('F', 5, 200);
		PlayNote('E', 5, 200);
		PlayNote('F', 5, 200);
		PlayNote('F', 5, 200, true);
		PlayNote('G', 5, 200);
		PlayNote('G', 4, 200, false, 4);
		PlayNote('G', 3, 200, false, 3);

		PlayNote('F', 3, 200, true);
		PlayNote('G', 3, 200);
		PlayNote('F', 3, 200, true);
		PlayNote('G', 3, 200);
		PlayNote('G', 3, 200, true);
		PlayNote('A', 3, 200);
		PlayNote('A', 3, 200, true);
		PlayNote('B', 3, 200);
		break;
	}
}