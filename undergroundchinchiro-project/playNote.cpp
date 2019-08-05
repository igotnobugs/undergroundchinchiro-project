#include "playNote.h"

void PlayNote(Note note, int octave, DWORD duration, int reps) {
	Note n = note;
	float pos = n + (12 * ((float)octave - 1)); 
	DWORD freq = (DWORD)(pow(2, (pos - 49) / 12) * 440); 
	for (int i = 0; i < reps; i++) {
		Beep(freq, duration);
	}
}