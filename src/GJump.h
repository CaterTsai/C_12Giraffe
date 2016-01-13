#ifndef CT_12GIRAFFE_GJUMP
#define CT_12GIRAFFE_GJUMP

#include "GBasic.h"
#include "ofxAnimatableFloat.h"

class JumpUnit : public IBasicUnit
{
public:
	JumpUnit(float fduration) ;
	void update(float fDelta)  override;
	void draw()  override;
	bool canRemove()  override;
private:
	enum eJumpState
	{
		eState_Jump	=	0
		,eState_Rotate
		,eState_Firework
		,eState_Fall
		,eState_Finish
	} _eUnitState;
	ofxAnimatableFloat		_animHeight, _animRotate;

	float									_fHeight, _fDegree;
	stGiraffeP							_Giraffe;

	ofxAnimatableFloat		_animFire, _animAlpha;
	float									_fFireDist1, _fFireDist2;
	stThreeLevelFireworkP	_Firework;
};

class GJump : public GBasic<JumpUnit>
{
public:
	GJump()
		:GBasic(eGiraffe_Jump, 0.0)
	{}

	GJump(float fDuration)
		:GBasic(eGiraffe_Jump, fDuration)
	{}
};



#endif // !CT_12GIRAFFE_GJUMP
