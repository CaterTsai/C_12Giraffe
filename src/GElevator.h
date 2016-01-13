#ifndef CT_12GIRAFFE_GELEVATOR
#define CT_12GIRAFFE_GELEVATOR

#include "GBasic.h"
#include "ofxAnimatableFloat.h"

class ElevatorUnit : public IBasicUnit
{
public:
	ElevatorUnit(float fduration);
	void update(float fDelta)  override;
	void draw()  override;

	bool canRemove()  override;
private:
	enum eEnterState
	{
		eState_Up	=	0
		,eState_Open
		,eState_Wait
		,eState_Close
		,eState_Down
		,eState_Finish
	} _eUnitState;

	bool								_bShowGiraffe;
	float								_fWaitTime;
	ofxAnimatableFloat	_animElevatorUp, _animElevatorDoor, _animMarkScale;
	stGiraffeP			_Giraffe;
	stExclamationMarkP	_Mark;
	stElevatorP		_Elevator;
};

class GElevator : public GBasic<ElevatorUnit>
{
public:
	GElevator()
		:GBasic(eGiraffe_Elevator, 0.0)
	{}

	GElevator(float fDuration)
		:GBasic(eGiraffe_Elevator, fDuration)
	{}
};



#endif // !CT_12GIRAFFE_GELEVATOR
