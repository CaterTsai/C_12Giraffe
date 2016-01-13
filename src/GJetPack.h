#ifndef CT_12GIRAFFE_GJETPACK
#define CT_12GIRAFFE_GJETPACK

#include "GBasic.h"
#include "ofxAnimatableFloat.h"

class JetpackUnit : public IBasicUnit
{
public:
	JetpackUnit(float fduration);

	void update(float fDelta) override;
	void draw() override;
	bool canRemove() override;

private:
	ofVec2f getRangePos();
private:
	enum eJetpackUnit
	{
		eState_Flyin = 0
		,eState_Wait
		,eState_Rotate
		,eState_Flyout
		,eState_Finish
	}_eUnitState;

	float	_fWaitTime, _fFlyoutTime;
	float _fFloatStartY, _fFloatDist;

	ofxAnimatableFloat	_animPosX, _animPosY, _animFloat, _animRotate;
	ofVec2f	_targetPos;
	float	_fneckDegree;
	stGiraffeP		_Giraffe;
	stJetpackP	_Jetpack;
};

class GJetpack : public GBasic<JetpackUnit>
{
public:
	GJetpack()
		:GBasic(eGiraffe_JetPack, 0.0)
	{}

	GJetpack(float fDuration)
		:GBasic(eGiraffe_JetPack, fDuration)
	{}
};

#endif // !CT_12GIRAFFE_GJETPACK
