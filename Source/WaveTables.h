/*
  ==============================================================================

    WaveTables.h
    Created: 19 Oct 2018 9:11:02pm
    Author:  lain

    WaveTableCollection class:
    Purpose:
        generate wave tables
        store wave tables
        retrieve from wave tables
  ==============================================================================
*/

#pragma once

//WAVE type enumeration
typedef enum WAVE { W_TRI, W_SQR, W_SAW, W_SIN, NUM_WAVEFORMS} wave_t;

//WaveTableCollection class
class WaveTableCollection {
    public:
        WaveTableCollection();
        WaveTableCollection(int sampleRate);
        ~WaveTableCollection();
        
        //preferred method of retreiving a single value from a table
        float getTableValue(wave_t table, int pos);
        
        //more dangerous, return a pointer to the table itself.
        //requires slightly less overhead and allows the table to be
        //modified if this is desirable!
        float* getTable(wave_t table);
        
    protected:
        virtual void initTables();
        virtual void initTri();
        virtual void initSquare();
        virtual void initSaw();
        virtual void initSin();
    private:        
        //the tables
        float** tables;
        int tableSize;
};