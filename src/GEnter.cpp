#include "GEnter.h"

#pragma region EnterUnit
//--------------------------------------------------------------
EnterUnit::EnterUnit(float fduration, int iside)
	:_eUnitState(eState_Enter)
	,_swingDegree(-30)
{
	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.bFill = true;
	_Giraffe.fsize = ofGetHeight() * 1.4;
	_Giraffe.tongueL = _Giraffe.fsize * 0.1;
	_Giraffe.fdegree = iside * 90;
	_Giraffe.fswingDegree = 0;
	_fWaitTimer = 0.3 * fduration;

	switch(iside)
	{
	case 0:
		{
			_Giraffe.drawPos.set(ofGetWidth() + _Giraffe.fsize * 0.3, ofGetHeight()/2 + _Giraffe.fsize * 0.3);
		}
		break;
	case 1:
		{
			_Giraffe.drawPos.set(ofGetWidth()/2 -_Giraffe.fsize * 0.3, ofGetHeight() + _Giraffe.fsize * 0.3);
		}
		break;
	case 2:
		{
			_Giraffe.drawPos.set(0 - _Giraffe.fsize * 0.3,  ofGetHeight()/2 - _Giraffe.fsize * 0.3);
		}
		break;
	case 3:
		{
			_Giraffe.drawPos.set(ofGetWidth()/2 + _Giraffe.fsize * 0.3, 0 - _Giraffe.fsize * 0.3);
		}
		break;
	}
	
	_animSwing.setDuration(0.5 * fduration);
	_animSwing.setCurve(AnimCurve::EASE_IN_EASE_OUT);
	_animSwing.animateFromTo(0, 1);

	_animTongue.setDuration(0.05 * fduration);
	_animTongue.setCurve(AnimCurve::BLINK_5);
	_animTongue.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
	_animTongue.animateFromTo(-10, 10);
}

//--------------------------------------------------------------
void EnterUnit::update(float fDelta)
{
	_animSwing.update(fDelta);
	_animTongue.update(fDelta);
	switch(_eUnitState)
	{
	case eState_Enter:
	case eState_Exit:
		{
			_Giraffe.fswingDegree =  _swingDegree * _animSwing.getCurrentValue();
			if(_animSwing.hasFinishedAnimating() && _animSwing.getPercentDone() == 1.0)
			{
				_eUnitState = (_eUnitState ==  eState_Enter)?eState_Wait:eState_Finish;
			}
		}
		break;
	case eState_Wait:
		{
			_Giraffe.tongueD = -34 + _animTongue.getCurrentValue();
			_fWaitTimer -= fDelta;
			if(_fWaitTimer <= 0.0)
			{
				_eUnitState = eState_Exit;
				_animSwing.animateFromTo(1, 0);
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void EnterUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}
	drawMgr::GetInstance()->draw(_Giraffe);
}

//--------------------------------------------------------------
bool EnterUnit::canRemove()
{
	return (_eUnitState == eState_Finish);
}
#pragma endregion

#pragma region GEnter
void GEnter::add(int node, int key)
{
	if(_sideIdx >= _sideList.size())
	{
		random_shuffle(_sideList.begin(), _sideList.end());
		_sideIdx = 0;
	}

	_elementList.push_back(EnterUnit(_fDuration, _sideList[_sideIdx]));
	_sideIdx++;
}
#pragma endregion
