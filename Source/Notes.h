/*
    notes.h
    
    Class(es) for handling the generation of midi note scales.
    
    Todo: Scala support for custom microtonal scales!
*/


#pragma once
        
float getStep(int note);
void setRatio(float newStep);
void initNotes();

void initNewScale(float divisions);

class NoteList {
    public:
        NoteList();
        NoteList(float baseFreq, float ratio);
        
        ~NoteList();
        
        void initNotes(float baseFreq, float ratio);
        
        float getFreq(int note);  //return the frequency corresponding to a midi note
        
    private:
        float *notes;
};