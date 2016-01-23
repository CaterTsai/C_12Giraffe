#ifndef CT_12GIRAFFE_GKIRBY
#define CT_12GIRAFFE_GKIRBY

#include "GBasic.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"


class KirbyUnit : public IBasicUnit
{
public:
	KirbyUnit(float fduration) ;
	void update(float fDelta)  override;
	void draw()  override;
	bool canRemove()  override;

private:
	enum eKirbyState
	{
		eState_Flyin	=	0
		,eState_Crash
		,eState_Finish
	}_eUnitState;

	ofxAnimatableOfPoint	_animBigStarPos;
	ofxAnimatableFloat	_animSmallStarX, _animSmallStarY, _animGiraffeRotate;
	ofxAnimatableFloat	_animGiraffeX, _animGiraffeY, _animGiraffeAlpha;
	ofxAnimatableFloat	_animStarAlpha;

	stGiraffeP		_Giraffe;
	stStarP			_BigStar;

	stStarP			_SmallStars[3];
	ofVec2f			_GiraffeVec, _SmallStarsVec[3];
};

class GKirby : public GBasic<KirbyUnit>
{
public:
	GKirby()
		:GBasic(eGiraffe_Kirby, 0.0)
	{}

	GKirby(float fDuration)
		:GBasic(eGiraffe_Kirby, fDuration)
	{}
};

#endif // !CT_12GIRAFFE_GKIRBY
