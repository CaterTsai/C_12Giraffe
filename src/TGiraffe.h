#ifndef CT_12GIRAFFE_TGIRAFFE
#define CT_12GIRAFFE_TGIRAFFE

#include "constParameter.h"
#include "GParameter.h"
#include "drawMgr.h"
#include "ofxAnimatableFloat.h"

class TGiraffe
{
public:
	TGiraffe();
	void update(float fDelta);
	void draw();

	void transform();
	bool isTransform();
private:
	enum eState
	{
		eState_ZoomIn	=	0
		,eState_Wait
		,eState_RotateAndOut
	}_eState;
	bool			_isTransform;
	stGiraffeP	_Giraffe;
	float			_fBasicSize, _fStartScale, _fWaitTimer;
	ofxAnimatableFloat	_animScale, _animRotate;

	ofImage	_screen;
};

#endif // !CT_12GIRAFFE_TGIRAFFE
