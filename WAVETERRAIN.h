#include <Ougens.h>		  // the base class for this instrument

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

private:
	double** terrainArr;
	double radius;
	double center[2];
	double freq;
	double amp;
	int wavetableSize;
};

