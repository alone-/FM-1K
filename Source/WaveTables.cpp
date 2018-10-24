/*
  ==============================================================================

    WaveTables.cpp
    Created: 19 Oct 2018 9:11:02pm
    Author:  lain

  ==============================================================================
*/

#include <math.h>

#include "WaveTables.h"

#define DEFAULT_SAMPLE_RATE (44100)
#define PI (3.1415)

WaveTableCollection::WaveTableCollection() : WaveTableCollection(DEFAULT_SAMPLE_RATE) {}

WaveTableCollection::WaveTableCollection(int sampleRate) {
    tableSize = sampleRate;
    
    initTables();
}

WaveTableCollection::~WaveTableCollection() {
    for (int i = 0; i < NUM_WAVEFORMS; i++) {
        delete tables[i];
    }
    
    delete tables;
}

float* WaveTableCollection::getTable(wave_t table) {
    return tables[table];
} 

float WaveTableCollection::getTableValue(wave_t table, int pos) {
    //bounds checking could be added here at a slight
    //performance cost. pos should be < tableSize  
    return tables[table][pos];
}

void WaveTableCollection::initTables() {
    //make the tables such that they correspond to a 1hz 
    //wave at the current sample rate
    tables = new float*[NUM_WAVEFORMS];
    
    for (int i = 0; i < NUM_WAVEFORMS; i++) {
        tables[i] = new float[tableSize];
    }
    
    initTri();
    initSquare();
    initSaw();
    initSin();
}

void WaveTableCollection::initTri() {
    float val = -1.;
    float step = 2. / ((float)tableSize / 2.);
    
    for (int i = 0; i < tableSize / 2; i++) {
        tables[W_TRI][i] = val;
        val += step;
    }
    for (int i = tableSize / 2; i < tableSize; i++) {
        tables[W_TRI][i] = val;
        val -= step;
    }
}

void WaveTableCollection::initSquare() {
    for (int i = 0; i < tableSize / 2; i++) {
        tables[W_SQR][i] = -1;
    }
    for (int i = tableSize / 2; i < tableSize; i++) {
        tables[W_SQR][i] = 1;
    }
}

//this implementation of a saw wave uses a lot of slight
//variations and curves to create a warmer "organic" sound
void WaveTableCollection::initSaw() {
    float val = -1;
	float step =  2. / (float)tableSize;
	int pos;

	for (pos = 0; pos < (tableSize * 0.975); pos++) 
	{
		tables[W_SAW][pos] = val;
		val += step;
	}
	//level out the end of the saw for a slightly warmer sound
	for (pos = tableSize * 0.975; pos < tableSize * 0.975; pos++)
    {
        tables[W_SAW][pos] = val;
    }
    
    step =  (val + 1) / (float)(tableSize * (1 - 0.975));
    
    for (pos = tableSize * 0.975; pos < tableSize; pos++)
    {
        tables[W_SAW][pos] = val;
        val -= step;
    }
}

void WaveTableCollection::initSin() {
    float step = (2. * PI) / (float)tableSize;
	float phase = 0;
	int pos;

	for ( pos = 0; pos < tableSize; pos++ ) {
		tables[W_SIN][pos] = sin(phase);
		phase += step;
	}
}