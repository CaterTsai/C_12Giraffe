#include "GElevator.h"

#pragma region ElevatorUnit
ElevatorUnit::ElevatorUnit(float fduration)
	:_fWaitTime(fduration * 0.3)
	,_eUnitState(eState_Up)
	,_bShowGiraffe(false)
{
	ofVec2f drawPos_(
		ofRandom(ofGetWidth() * 0.1, ofGetWidth() * 0.9)
		,ofRandom(ofGetHeight() * 0.1, ofGetHeight() * 0.9)
	);

	float fsize_ = ofRandom(100, 170);
	
	_Elevator.linecolor = colorMgr::GetInstance()->getForeColor();
	_Elevator.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Elevator.drawPos = drawPos_;
	_Elevator.fsize = fsize_;

	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.bFill = true;
	_Giraffe.fsize = fsize_ * 0.6;
	_Giraffe.tongueL = _Giraffe.fsize * 0.1;
	_Giraffe.drawPos.set(drawPos_.x , drawPos_.y + fsize_ * 0.2);

	_Mark.bFill = true;
	_Mark.flineWidth = 0.0;
	_Mark.fillcolor.set(0);
	_Mark.fsize = _Giraffe.fsize * 0.35;
	_Mark.scaleVec = ofVec2f(0.0);
	_Mark.drawPos.set(drawPos_.x, drawPos_.y -fsize_ * 0.25 );

	_animElevatorUp.setDuration(0.3 * fduration);
	_animElevatorUp.setCurve(AnimCurve::EASE_IN_EASE_OUT);

	_animElevatorDoor.setDuration(0.5 * fduration);
	_animElevatorDoor.setCurve(AnimCurve::BOUNCY);

	_animMarkScale.setDuration(0.1 * fduration);
	_animMarkScale.setCurve(AnimCurve::BOUNCY);

	//Start
	_animElevatorUp.animateFromTo(0.0, 1.0);
}

//--------------------------------------------------------------
void ElevatorUnit::update(float fDelta)
{
	_animElevatorUp.update(fDelta);
	_animElevatorDoor.update(fDelta);
	_animMarkScale.update(fDelta);
	switch(_eUnitState)
	{
	case eState_Up:
		{
			_Elevator.upPerc = _animElevatorUp.getCurrentValue();
			if(_animElevatorUp.getPercentDone() == 1.0 && _animElevatorUp.hasFinishedAnimating())
			{
				_animElevatorDoor.animateFromTo(0.0, 1.0);
				_eUnitState = eState_Open;
				_bShowGiraffe = true; 
			}
		}
		break;
	case eState_Open:
		{
			_Elevator.openPerc = _animElevatorDoor.getCurrentValue();
			if(_animElevatorDoor.getPercentDone() == 1.0 && _animElevatorDoor.hasFinishedAnimating())
			{
				_animMarkScale.animateFromTo(0.0, 1.0);
				_eUnitState = eState_Wait;
			}
		}
		break;
	case eState_Wait:
		{
			_Mark.scaleVec.set(_animMarkScale.getCurrentValue());
			_fWaitTime -= fDelta;
			if(_fWaitTime <= 0.0)
			{
				_animElevatorDoor.animateFromTo(1.0, 0.0);
				_eUnitState = eState_Close;
			}
		}
		break;
	case eState_Close:
		{
			_Elevator.openPerc = _animElevatorDoor.getCurrentValue();
			if(_animElevatorDoor.getPercentDone() == 1.0 && _animElevatorDoor.hasFinishedAnimating())
			{
				_animElevatorUp.animateFromTo(1.0, 0.0);
				_eUnitState = eState_Down;
				_bShowGiraffe = false;
			}
		}
		break;
	case eState_Down:
		{
			_Elevator.upPerc = _animElevatorUp.getCurrentValue();
			if(_animElevatorUp.getPercentDone() == 1.0 && _animElevatorUp.hasFinishedAnimating())
			{
				_eUnitState = eState_Finish;
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void ElevatorUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}

	if(_bShowGiraffe)
	{
		drawMgr::GetInstance()->draw(_Mark);
		drawMgr::GetInstance()->draw(_Giraffe);
	}

	drawMgr::GetInstance()->draw(_Elevator);
}

//--------------------------------------------------------------
bool ElevatorUnit::canRemove()
{
	return _eUnitState == eState_Finish;
}
#pragma endregion