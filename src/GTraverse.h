#ifndef CT_12GIRAFFE_GTRAVERSE
#define CT_12GIRAFFE_GTRAVERSE

#include "GBasic.h"
#include "ofxAnimatableFloat.h"

class TraverseUnit : public IBasicUnit
{
public:
	TraverseUnit(float fDuration);
	void update(float fDelta) override;
	void draw() override;
	bool canRemove() override;

private:
	ofVec2f getRangePos(int iside = rand()%4);

private:
	enum eTraverseState
	{
		eState_Enter	=	0
		,eState_Wait
		,eState_Exit
		,eState_Finish
	}_eUnitState;

	float	_fWaitTime;
	
	stLongGiraffeP	_Giraffe;
	ofxAnimatableFloat	_animNeck;
	
	float	_rotateDegree, _maxNeckL;
	ofVec2f _drawPos;
	ofVec2f	_start, _target;
};

class GTraverse : public GBasic<TraverseUnit>
{
public:
	GTraverse()
		:GBasic(eGiraffe_Traverse, 0.0)
	{}

	GTraverse(float fDuration)
		:GBasic(eGiraffe_Traverse, fDuration)
	{}
};

#endif // !CT_12GIRAFFE_GTRAVERSE
