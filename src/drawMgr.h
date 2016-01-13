#ifndef CT_12GIRAFFE_DRAWMGR
#define CT_12GIRAFFE_DRAWMGR

#include "constParameter.h"
#include "DEParameter.h"

#include "DEGiraffe.h"
#include "DESwingGiraffe.h"
#include "DELongGiraffe.h"
#include "DEThreeLevelFirework.h"
#include "DEElevator.h"
#include "DEExclamationMark.h"
#include "DEJetpack.h"

class drawMgr
{
public:
	void draw(stGiraffeP& param);
	void draw(stSwingGiraffeP& param);
	void draw(stLongGiraffeP& param);

	void draw(stThreeLevelFireworkP& param);
	void draw(stElevatorP& param);
	void draw(stJetpackP& param);

	void draw(stExclamationMarkP& param);
//-------------------
//Singleton
//-------------------
public:
	static drawMgr* GetInstance();
	static void Destroy();

private:
	drawMgr(){};
	drawMgr(drawMgr const&);
	void operator=(drawMgr const&);
	static drawMgr *pInstance;
};

#endif // !CT_12GIRAFFE_DRAWMGR
