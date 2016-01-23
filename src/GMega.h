#ifndef CT_12GIRAFFE_GMEGA
#define CT_12GIRAFFE_GMEGA

#include "GBasic.h"
#include "ofxAnimatableFloat.h"

static const int cMAX_CHARGE_LEVEL = 3;

class MegaUnit : public IBasicUnit
{
public:
	MegaUnit(float fduration) ;
	void update(float fDelta)  override;
	void draw()  override;
	bool canRemove()  override;

private:
	enum eMegaState
	{
		eState_Enter	=	0
		,eState_Charge
		,eState_Fire
		,eState_Exit
		,eState_Finish
	}_eUnitState;

	ofxAnimatableFloat	_animPosY, _animScaleX, _animTongue;

	int _iChargeLevel, _iChargeSpeed;
	float	_fChargeTimer, _fChargeT, _fWaitT;
	stGiraffeP		_Giraffe;
};

class GMega : public GBasic<MegaUnit>
{
public:
	GMega()
		:GBasic(eGiraffe_Mega, 0.0)
	{}

	GMega(float fDuration)
		:GBasic(eGiraffe_Mega, fDuration)
	{}
};

#endif // !CT_12GIRAFFE_GMEGA
