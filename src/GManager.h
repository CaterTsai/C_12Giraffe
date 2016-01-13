#ifndef CT_12GIRAFFE_GMANAGER
#define CT_12GIRAFFE_GMANAGER

#include "constParameter.h"
#include "drawMgr.h"
#include "GBasic.h"

class GManager
{
public:
	void setup();
	void update(float fDelta);
	void draw();

private:
	map<string, ofPtr<GBasic>>	_GMap;
};

#endif // !CT_12GIRAFFE_GMANAGER
