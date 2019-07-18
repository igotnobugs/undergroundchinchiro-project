#include <windows.h>
#include <iostream>
#include <math.h>

using namespace std;

void playNote(char note, int octave, DWORD duration, bool isSharp = false) {
	int tone = 0;
	if (note == 'C') {
		tone = 4;
	}
	else if (note == 'D') {
		tone = 6;
	}
	else if (note == 'E') {
		tone = 8;
	}
	else if (note == 'F') {
		tone = 9;
	}
	else if (note == 'G') {
		tone = 11;
	}
	else if (note == 'A') {
		tone = 13;
	}
	else if (note == 'B') { 
		tone = 15;
	}
	else { //Error should sound very low and very long
		Beep(100, 500);
		Beep(100, 500);
		Beep(100, 500);
	}
	
	float pos = tone + (12 * (octave - 1));
	DWORD freq = pow(2, (pos - 49) / 12) * 440;
	Beep(freq, duration);
}