#include "GJump.h"

#pragma region JumpUnit
//--------------------------------------------------------------
JumpUnit::JumpUnit(float fduration)
	:_eUnitState(eState_Jump)
{
	_fHeight = ofRandom(0.3 * ofGetHeight(), 0.8 * ofGetHeight());
	float fDuration_ = _fHeight/(ofGetHeight() * 0.8) * fduration;

	_animHeight.setDuration(fDuration_ / 3.0);
	_animHeight.setCurve(AnimCurve::EASE_OUT);
		
	_animRotate.setDuration(fduration / 3.0);
	_animRotate.setCurve(AnimCurve::EASE_IN_EASE_OUT);
	
	_animHeight.animateFromTo(0, _fHeight);

	_Giraffe.drawPos.set(ofRandomWidth(), 0);
	_Giraffe.fdegree = ofRandom(0, 359);
	_fDegree = _Giraffe.fdegree;

	//Firework
	_Firework.drawPos.set(_Giraffe.drawPos.x, ofGetHeight() - _fHeight);
	_Firework.fdegree = _fDegree;
	_Firework.levelNum[0] = 1;
	_Firework.levelNum[1] = 5;
	_Firework.levelNum[2] = 5;

	_Firework.levelAlpha[0] = 255;
	_Firework.levelAlpha[1] = 255;
	_Firework.levelAlpha[2] = 255;

	_Firework.levelDegree[1] = 36;

	_fFireDist1 = _Giraffe.fsize * 0.5;
	_fFireDist2 = _Giraffe.fsize * 1.0;

	_animFire.setDuration(fduration / 5.0);
	_animFire.setCurve(AnimCurve::EASE_OUT);
	_animAlpha.setDuration(fduration / 5.0);
	_animAlpha.setCurve(AnimCurve::LATE_LINEAR);
}

//--------------------------------------------------------------
void JumpUnit::update(float fDelta)
{
	_animHeight.update(fDelta);
	_animRotate.update(fDelta);
	_animFire.update(fDelta);
	_animAlpha.update(fDelta);
	switch(_eUnitState)
	{
	case eState_Jump:
		{
			_Giraffe.drawPos.y = ofGetHeight() - _animHeight.getCurrentValue();
			if(_animHeight.getPercentDone() == 1.0 && _animHeight.hasFinishedAnimating())
			{
				_eUnitState = eState_Rotate;
				_animRotate.animateFromTo(0, 360);
			}
		}
		break;
	case eState_Rotate:
		{
			_Giraffe.fdegree =_fDegree + _animRotate.getCurrentValue();
			if(_animRotate.getPercentDone() == 1.0 && _animRotate.hasFinishedAnimating())
			{
				_eUnitState = eState_Firework;
				_animFire.animateFromTo(0, 1);
				_animAlpha.animateFromTo(255, 0);
			}
		}
		break;
	case eState_Firework:
		{
			float falpha_ = _animAlpha.getCurrentValue();
			_Firework.levelAlpha[0] = falpha_;
			_Firework.levelAlpha[1] = falpha_;
			_Firework.levelAlpha[2] = falpha_;

			float fanimVal_ = _animFire.getCurrentValue();
			_Firework.levelDist[1] = _fFireDist1 * fanimVal_;
			_Firework.levelDist[2] = _fFireDist2 * fanimVal_;

			if(_animAlpha.getPercentDone() == 1.0 && _animAlpha.hasFinishedAnimating())
			{
				_animHeight.setCurve(AnimCurve::EASE_IN);
				_animHeight.animateTo(0);
				_eUnitState = eState_Fall;
			}
		}
		break;
	case eState_Fall:
		{	
			_Giraffe.drawPos.y = ofGetHeight() - _animHeight.getCurrentValue();
			if(_animHeight.getPercentDone() == 1.0 && _animHeight.hasFinishedAnimating())
			{
				_eUnitState = eState_Finish;
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void JumpUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}

	if(_eUnitState == eState_Firework)
	{
		drawMgr::GetInstance()->draw(_Firework);
	}

	drawMgr::GetInstance()->draw(_Giraffe);
}

//--------------------------------------------------------------
bool JumpUnit::canRemove()
{
	return (_eUnitState == eState_Finish);
}
#pragma endregion



