#pragma once
#include <windows.h>

//Play a single note, Starts at C octave 1
void playNote(char note, int octave, DWORD duration, bool isSharp = false);