#ifndef CT_12GIRAFFE_GDROP
#define CT_12GIRAFFE_GDROP

#include "GBasic.h"
#include "ofxAnimatableFloat.h"

class DropUnit : public IBasicUnit
{
public:
	DropUnit(float fduration);
	void update(float fDelta) override;
	void draw() override;

	bool canRemove() override;

private:
	void updateOffset(float fDelta);

private:
	enum eDropState
	{
		eState_Drop	=	0
		,eState_Float
		,eState_Back
		,eState_Finish
	}_eUnitState;

	float					_fFloatTime, _fBackTime;
	stSwingGiraffeP			_Giraffe;
	ofxAnimatableFloat	_animPosY, _animSwing;
	
	ofxAnimatableFloat _animFloat;
	float		_xOffset, _xVol, _xSigma;
	float		_yOffset, _yVol, _ySigma;
	ofVec2f	_baseOffset;
	
};

class GDrop : public GBasic<DropUnit>
{
public:
	GDrop()
		:GBasic(eGiraffe_Drop, 0.0)
	{}

	GDrop(float fDuration)
		:GBasic(eGiraffe_Drop, fDuration)
	{}
};

#endif // !CT_12GIRAFFE_GDROP
