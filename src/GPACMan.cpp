#include "GPACMan.h"

//--------------------------------------------------------------
PACManUnit::PACManUnit(float fduration)
	:_eUnitState(eState_LeftIn)
	,_fWaitT(fduration * 0.05)
	,_fPosDelayT(fduration * 0.1)
{
	ofSeedRandom();

	float fsize_ = ofRandom(80, 120);

	_startP = getRangePos();
	_endP = _startP.getInterpolated(ofVec2f(ofGetWidth()/2, ofGetHeight()/2), 2.2);
	_startP = _startP.getInterpolated(ofVec2f(ofGetWidth()/2, ofGetHeight()/2), -0.2);

	ofVec2f vec_ = (_endP - _startP);
	vec_.x = -abs(vec_.x);

	float fdegree_ = vec_.angle(ofVec2f(-1, 0));
	if(_startP.x > _endP.x)
	{
		fdegree_ *= -1;
	}

	//Ghost
	_Ghost.linecolor = colorMgr::GetInstance()->getForeColor();
	_Ghost.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Ghost.fsize = fsize_;
	_Ghost.fdegree = fdegree_;
	
	//PACMan
	_PACMan.linecolor = colorMgr::GetInstance()->getForeColor();
	_PACMan.fillcolor = colorMgr::GetInstance()->getBackColor();
	_PACMan.fsize = fsize_;
	_PACMan.fdegree = fdegree_;
	_PACMan.mouthPerc = 0.0;

	//Giraffe
	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.fsize = fsize_ * 0.8;
	_Giraffe.tongueL = _Giraffe.fsize * 0.1;
	_Giraffe.fdegree = fdegree_;
	_Giraffe.offsetPos.set(0, _Giraffe.fsize * -0.9);

	//Flip
	if(_startP.x <= ofGetWidth()/2)
	{
		_Ghost.bflip = true;
		_PACMan.bflip = true;
		_Giraffe.bflip = true;
	}

	//Animatable
	_animMouth.setDuration(fduration * 0.05);
	_animMouth.setCurve(AnimCurve::LINEAR);
	_animMouth.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
	
	_animPPos.setDuration(fduration * 0.4);
	_animPPos.setCurve(AnimCurve::LINEAR);
	_animPPos.setPosition(_startP);

	_animGPos.setDuration(fduration * 0.4);
	_animGPos.setCurve(AnimCurve::LINEAR);
	_animGPos.setPosition(_startP);
	
	_animMouth.animateFromTo(0.0, 1.0);
	_animPPos.animateTo(_endP);
	_animGPos.animateToAfterDelay(_endP, _fPosDelayT);

}

//--------------------------------------------------------------
void PACManUnit::update(float fDelta)
{
	_animMouth.update(fDelta);
	_animPPos.update(fDelta);
	_animGPos.update(fDelta);

	switch(_eUnitState)
	{
	case eState_LeftIn:
	case eState_RightIn:
		{
			_PACMan.drawPos.set(_animPPos.getCurrentPosition());
			_PACMan.mouthPerc = _animMouth.getCurrentValue();
			_Ghost.drawPos.set(_animGPos.getCurrentPosition());
			_Giraffe.drawPos.set(_PACMan.drawPos);

			if(_animPPos.hasFinishedAnimating() && _animPPos.getPercentDone() == 1.0 &&
				_animGPos.hasFinishedAnimating() && _animGPos.getPercentDone() == 1.0)
			{
				_eUnitState = (_eUnitState == eState_LeftIn)?eState_Waiting:eState_Finish;
				_Giraffe.bflip ^= true;
				_PACMan.bflip ^= true;
				_Ghost.bflip ^= true;
				_Ghost.scared ^= true;
			}
		}
		break;
	case eState_Waiting:
		{
			_fWaitT -= fDelta;
			if(_fWaitT <= 0.0)
			{
				_eUnitState = eState_RightIn;
				
				_animGPos.animateTo(_startP);
				_animPPos.animateToAfterDelay(_startP, _fPosDelayT);
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void PACManUnit::draw()
{
	if(_eUnitState == eState_Finish || _eUnitState == eState_Waiting)
	{
		return;
	}

	drawMgr::GetInstance()->draw(_Giraffe);
	drawMgr::GetInstance()->draw(_Ghost);
	drawMgr::GetInstance()->draw(_PACMan);

}

//--------------------------------------------------------------
bool PACManUnit::canRemove()
{
	return _eUnitState == eState_Finish;
}

//--------------------------------------------------------------
ofVec2f PACManUnit::getRangePos(int iside)
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