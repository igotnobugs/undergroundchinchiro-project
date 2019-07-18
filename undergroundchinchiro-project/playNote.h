#pragma once
#include <windows.h>

//Play a single note, Starts at C octave 1, only Sharp (e.g. Db -> C#)
void PlayNote(char note, int octave, DWORD duration, bool isSharp = false, int reps = 1);