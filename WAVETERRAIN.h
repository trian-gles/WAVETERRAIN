#include <Ougens.h>		  // the base class for this instrument

class WAVETERRAIN : public Instrument {

public:
	WAVETERRAIN();
	virtual ~WAVETERRAIN();
	virtual int init(double *, int);
	virtual int configure();
	virtual int run();

private:
	double* terrainArr;
	float radius;
	float center[2];
	int resolution;
};

