#include <Ougens.h>

class WAVETERRAIN : public Instrument {

public:
	WAVETERRAIN();
	virtual ~WAVETERRAIN();
	virtual int init(double *, int);
	virtual int configure();
	virtual int run();
	double f(double x, double y);
	double* getCoors(double phase);
	double tableLookup(int x, int y);
	double bilinearInterpolation(double* coors);
	void setFreq(double freq);
	void doupdate();

private:
	int branch;
	double** terrainArr;
	double phase;
	double phaseInc;
	double radius;
	double center[2];
	double freq;
	double amp;
	int wavetableSize;
};

