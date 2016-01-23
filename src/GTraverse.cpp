#include "GTraverse.h"


//--------------------------------------------------------------
TraverseUnit::TraverseUnit(float fDuration)
	:_fWaitTime(0.2 * fDuration)
	,_eUnitState(eState_Enter)
{
	float fsize_ = ofRandom(100, 150);

	int startSide_ = rand() % 4;
	int targetSide_ = startSide_ + (1 + rand() % 3); 
	_start = getRangePos(startSide_);
	_target = getRangePos(targetSide_);

	_start = _start.getInterpolated(_target, -0.2);
	_target = _target.getInterpolated(_start, -0.2);

	_maxNeckL = _start.distance(_target);
	_drawPos.set(_target.getInterpolated(_start, 0.5));
	_rotateDegree = -(_target - _start).angle(ofVec2f(0, -1));

	//Giraffe
	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.fsize = fsize_;
	_Giraffe.drawPos.set(0, 0);
	_Giraffe.fneckLength = 0.0;
	_Giraffe.offsetPos.set(0, _maxNeckL * 0.5 - _Giraffe.fneckLength * 0.5);

	_animNeck.setDuration(fDuration * 0.4);
	_animNeck.animateFromTo(0.0, 1.0);
}

//--------------------------------------------------------------
void TraverseUnit::update(float fDelta)
{
	_animNeck.update(fDelta);

	switch(_eUnitState)
	{
	case eState_Enter:
		{
			_Giraffe.fneckLength = _animNeck.getCurrentValue() * _maxNeckL;
			_Giraffe.offsetPos.set(0, _maxNeckL * 0.5 + _Giraffe.fneckLength * -0.5);
			if(_animNeck.hasFinishedAnimating() && _animNeck.getPercentDone() == 1.0)
			{
				_eUnitState = eState_Wait;
			}
		}
		break;
	case eState_Wait:
		{
			_fWaitTime -= fDelta;
			if(_fWaitTime <= 0.0)
			{
				_eUnitState = eState_Exit;
				_animNeck.animateFromTo(1.0, 0.0);
			}
		}
		break;
	case eState_Exit:
		{
			_Giraffe.fneckLength = _animNeck.getCurrentValue() * _maxNeckL;
			_Giraffe.offsetPos.set(0, _maxNeckL * -0.5 + _Giraffe.fneckLength * 0.5);
			_Giraffe.fneckLength = _animNeck.getCurrentValue() * _maxNeckL;
			if(_animNeck.hasFinishedAnimating() && _animNeck.getPercentDone() == 1.0)
			{
				_eUnitState = eState_Finish;
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void TraverseUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}
	ofPushMatrix();
	ofTranslate(_drawPos);
	ofRotateZ(_rotateDegree);
	{
		drawMgr::GetInstance()->draw(_Giraffe);
	}
	ofPopMatrix();
}

//--------------------------------------------------------------
bool TraverseUnit::canRemove()
{
	return (_eUnitState == eState_Finish);
}

//--------------------------------------------------------------
ofVec2f TraverseUnit::getRangePos(int iside)
{
	ofVec2f result_(0);
	switch(iside % 4)
	{
	case 0:
		{
			result_.x = ofRandomWidth();
			result_.y = 0;
		}
		break;
	case 1:
		{
			result_.x = ofRandomWidth();
			result_.y = ofGetHeight();
		}
		break;
	case 2:
		{
			result_.x = 0;
			result_.y = ofRandomHeight();
		}
		break;
	case 3:
		{
			result_.x = ofGetWidth();
			result_.y = ofRandomHeight();
		}
		break;
	}
	return result_;
}