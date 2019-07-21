#pragma once
#include <windows.h>
#include <iostream>
#include <math.h>

enum Note {
	C = 4, 
	Cs = 5, Db = 5,
	D = 6, 
	Ds = 7, Eb = 7,
	E = 8,
	F = 9, 
	Fs = 10, Gb = 11,
	G = 11,
	Gs = 12, Ab = 12,
	A = 13,
	As = 14, Bb = 14,
	B = 15
};

using namespace std;
//Play a single note, Starts at C octave 1. Use Sleep(n) for rests
void PlayNote(Note note, int octave, DWORD duration, int reps = 1);
//Play the Hail De La Salle Hymn
void PlayTuneLaSalle();
//Play Some Mario Tunes
void PlayTuneMario(int type);
//Play San's Music
void PlayTuneMegalovania();
//Play Default Tunes 0-6 Rank Based
void PlayTuneDefault(int type);