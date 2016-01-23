#ifndef CT_12GIRAFFE_GMARIO
#define CT_12GIRAFFE_GMARIO

#include "GBasic.h"
#include "ofxAnimatableFloat.h"

class MarioUnit : public IBasicUnit
{
public:
	MarioUnit(float fdurtaion);
	void update(float fDelta)  override;
	void draw()  override;
	bool canRemove()  override;

private:
	enum eMarioState
	{
		eState_PipeEnter	=	0
		,eState_GiraffeEnter
		,eState_FlowerEnter
		,eState_Waiting
		,eState_FlowerExit
		,eState_GiraffeExit
		,eState_PipeExit
		,eState_Finish
	}_eUnitState;

	stGiraffeP			_Giraffe;
	stPipeP				_Pipe;
	stFireFlowerP	_Flower;

	ofxAnimatableFloat	_animGiraffeY, _animPipeY, _animFlowerY;
	ofxAnimatableFloat _animFlowerPrec;

	float _fWaitT, _fFlowerT;
};

class GMario : public GBasic<MarioUnit>
{
public:
	GMario()
		:GBasic(eGiraffe_Mario, 0.0)
	{}

	GMario(float fDuration)
		:GBasic(eGiraffe_Mario, fDuration)
	{}
};

#endif // !CT_12GIRAFFE_GMARIO
