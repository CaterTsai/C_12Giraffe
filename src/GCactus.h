#ifndef CT_12GIRAFFE_GCACTUS
#define CT_12GIRAFFE_GCACTUS

#include "GBasic.h"
#include "ofxAnimatableFloat.h"

const static int cCACTUS_SHADOW_NUM = 3;
const static float cCACTUS_BASE_DEGREE = -15.0;
const static float cGIRAFFE_BASE_DEGREE = 20.0;

class CactusUnit : public IBasicUnit
{
public:
	CactusUnit(float fduration);
	void update(float fDelta) override;
	void draw() override;
	bool canRemove() override;

private:
	void drawShadow();

private:
	enum eCactusState
	{
		eState_RunIn = 0
		,eState_Stop
		,eState_Wait
		,eState_RunOut
		,eState_Finish
	}_eUnitState;

	stGiraffeP		_Giraffe;
	stCactusP		_Cactus;
	float				_fWaitT, _fShadowDelay;

	ofxAnimatableFloat	_animPosY, _animShadows, _animDegree;
};

class GCactus : public GBasic<CactusUnit>
{
public:
	GCactus()
		:GBasic(eGiraffe_Cactus, 0.0)
	{}

	GCactus(float fDuration)
		:GBasic(eGiraffe_Cactus, fDuration)
	{}
};

#endif // !CT_12GIRAFFE_GCACTUS
