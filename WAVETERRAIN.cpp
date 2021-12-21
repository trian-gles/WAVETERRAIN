#include <stdio.h>
#include <stdlib.h>
#include <ugens.h>
#include <math.h>
#include <PField.h>
#include <Instrument.h>
#include "WAVETERRAIN.h"			  // declarations for this instrument class
#include <rt.h>
#include <rtdefs.h>
#include <iostream>

// Construct an instance of this instrument and initialize some variables.
// Using an underbar as the first character of a data member is a nice
// convention to follow, but it's not necessary, of course.  It helps you
// to see at a glance whether you're looking at a local variable or a
// data member.

WAVETERRAIN::WAVETERRAIN()
{
}


// Destruct an instance of this instrument, freeing any memory you've allocated.

WAVETERRAIN::~WAVETERRAIN()
{
	for(int i = 0; i < wavetableSize; i++){
		delete terrainArr[i];
	}
	delete terrainArr;
}

// any function that can fill a terrain in x and y from 0 to 1
double WAVETERRAIN::f(double x, double y)
{
	return sin(2 * M_PI * x) * sin(2 * M_PI * y);
}

double* WAVETERRAIN::getCoors(double phase)
{
	double* coors = new double[2];
	coors[0] = radius * wavetableSize * sin(M_PI * 2 * phase) + center[0];
	coors[1] = radius * wavetableSize * cos(M_PI * 2 * phase) + center[1];
	return coors;
}

 double WAVETERRAIN::tableLookup(int x, int y)
{
	while (x < 0){
		x += wavetableSize;
	}


	while (y < 0){
		y += wavetableSize;
	}

	x %= wavetableSize;
	y %= wavetableSize;
	return terrainArr[x][y];
}

double WAVETERRAIN::bilinearInterpolation(double* coors)
{
	double x = coors[0];
	double y = coors[1];
	double x1 = floor(x);
	double x2 = ceil(x);
	double y1 = floor(y);
	double y2 = ceil(y);

	double q11 = tableLookup((int) x1, (int) y1);
	double q12 = tableLookup((int) x1, (int) y2);
	double q21 = tableLookup((int) x2, (int) y1);
	double q22 = tableLookup((int) x2, (int) y2);

	double fxy1 =  (q11 * (x2 - x) / (x2 - x1)) + (q21 * (x - x1) / (x2 - x1));
	double fxy2 =  (q12 * (x2 - x) / (x2 - x1)) + (q22 * (x - x1) / (x2 - x1));
	return (fxy1 * (y2 - y) / (y2 - y1)) + (fxy2 * (y - y1) / (y2 - y1));

}

// Called by the scheduler to initialize the instrument. Things done here:
//   - read, store and check pfields
//   - set output file (or bus) pointer
//   - init instrument-specific things
// If there's an error here (like invalid pfields), call and return die() to
// report the error.  If you just want to warn the user and keep going,
// call warn() or rterror() with a message.

int WAVETERRAIN::init(double p[], int n_args)
{		// store this for use in doupdate()

	/* Args:
		p0: inskip
		p1: dur
		p2: amp
		p3: freq
		p4: radius (0 - 0.5)
		p5: center x (0 - 1)
		p6: center y (0 - 1)
		p7: wavetable size
*/
	int idk = rtsetoutput(p[0], p[1], this);
	amp = p[2];
	freq = p[3];
	radius = p[4];
	wavetableSize = p[7];
	center[0] = p[5] * wavetableSize;
	center[1] = p[6] * wavetableSize;
	std::cout << "wavetableSize: " << wavetableSize << "\n";
	std::cout << "center x: " << center[0] << " y: " << center[1] << "\n";
	// build the terrain
	terrainArr = new double*[wavetableSize];
	for(int i = 0; i < wavetableSize; i++){
		terrainArr[i] = new double[wavetableSize];
		for (int j = 0; j < wavetableSize; j++){
			terrainArr[i][j] = f(i / (double)wavetableSize, j / (double)wavetableSize);
		}
	}
	return nSamps();
}


// For non-interactive (script-driven) sessions, the constructor and init()
// for every instrument in the script are called before any of them runs.
// By contrast, configure() is called right before the instrument begins
// playing.  If we were to allocate memory at init time, then all notes in
// the score would allocate memory then, resulting in a potentially excessive
// memory footprint.  So this is the place to allocate any substantial amounts
// of memory you might be using.

int WAVETERRAIN::configure()
{
	return 0;	// IMPORTANT: Return 0 on success, and -1 on failure.
}



// Called by the scheduler for every time slice in which this instrument
// should run.  This is where the real work of the instrument is done.

int WAVETERRAIN::run()
{
	float out[2];

	for (int i = 0; i < framesToRun(); i++) {
		float out[2];
		int cf = currentFrame();
		double phase = cf * freq / SR;
		double* coors = getCoors(phase);
		out[0] = bilinearInterpolation(coors) * amp;
		out[1] = out[0];
		std::cout << "outputting val " << out[0] << "\n";
		rtaddout(out);
		increment();
		delete coors;
	}

	// Return the number of frames we processed.
	return framesToRun();
}


// The scheduler calls this to create an instance of this instrument
// and to set up the bus-routing fields in the base Instrument class.
// This happens for every "note" in a score.

Instrument *makeWAVETERRAIN()
{
	WAVETERRAIN *inst = new WAVETERRAIN();
	inst->set_bus_config("WAVETERRAIN");

	return inst;
}


// The rtprofile introduces this instrument to the RTcmix core, and
// associates a script function name (in quotes below) with the instrument.
// This is the name the instrument goes by in a script.

void rtprofile()
{
	RT_INTRO("WAVETERRAIN", makeWAVETERRAIN);
}


