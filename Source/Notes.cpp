// notes.cpp
//
// Dec. 30, 2017
// 
// Created file, wrote genNote and playNote
//
// Dec. 31, 2017
//
// Added attack/release functions
//
// Jan 1, 2018
//
// Modified code to work with ms times instead
// of seconds.
//
// Jan 2, 2018
//
// Added documentation & assertions
//
// Jan 5, 2018
//
// Reworked note generation, now generates
// continuous note on call.
//
// Oct 18, 2018
//
// Replaced old C-style note generation table with a C++
// class, NoteList.

#include "Notes.h"

// Definitions -----------------------------------------

#define NUM_NOTES 128
#define MIN_NOTE 0
#define MAX_NOTE 127

//these defaults are an approximation of a standard
//12-tone harmonic scale

#define DEFAULT_RATIO (1.05946)
#define DEFAULT_BASE (8.1)

// NoteList class
NoteList::NoteList() : NoteList(DEFAULT_BASE, DEFAULT_RATIO) { }

NoteList::NoteList(float baseFreq, float ratio) {
    notes = nullptr;
    
    initNotes(baseFreq, ratio);
}

NoteList::~NoteList() {
    if (notes != nullptr)
        delete notes;
}

//initialize the note list with a given base frequency and ratio between notes
//defaults are provided for a standard "tuning"
void NoteList::initNotes(float baseFreq, float ratio)
{
    //delete the old note table if it exists
    if (notes != nullptr)
        delete notes;
        
    //generate new notes, starting at the base freq
    notes = new float[NUM_NOTES];
    notes[0] = baseFreq;

	for (int i = 1; i < NUM_NOTES; i++)
	{
		notes[i] = notes[i-1] * ratio;
	}
}

//return the frequency associated with a midi note in the current scale
float NoteList::getFreq( int note ) {
    //return 0 if the note is not valid (a frequency of 0 won't be audible),
    //but also won't let us know there was an error.
    if (note < MIN_NOTE || note > MAX_NOTE)
        return 0;
        
	return notes[note];
}