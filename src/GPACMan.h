#ifndef CT_12GIRAFFE_GPACMAN
#define CT_12GIRAFFE_GPACMAN

#include "GBasic.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"

class PACManUnit : public IBasicUnit
{
public:
	PACManUnit(float fduration);
	void update(float fDelta) override;
	void draw() override;
	bool canRemove() override;

private:
	ofVec2f getRangePos(int iside = rand()%4);

private:
	enum ePACManState
	{
		eState_LeftIn	=	0
		,eState_Waiting
		,eState_RightIn
		,eState_Finish
	}_eUnitState;

	float _fWaitT, _fPosDelayT;

	stPACManP	_PACMan;
	stGhostP	_Ghost;
	stGiraffeP	_Giraffe;

	ofVec2f _startP, _endP;
	ofxAnimatableFloat	_animMouth;
	ofxAnimatableOfPoint	_animPPos, _animGPos;

};

class GPACMan : public GBasic<PACManUnit>
{
public:
	GPACMan()
		:GBasic(eGiraffe_PACMan, 0.0)
	{}

	GPACMan(float fDuration)
		:GBasic(eGiraffe_PACMan, fDuration)
	{}
};

#endif // !CT_12GIRAFFE_GPACMAN
