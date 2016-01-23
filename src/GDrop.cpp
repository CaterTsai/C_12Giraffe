#include "GDrop.h"

//--------------------------------------------------------------
DropUnit::DropUnit(float fduration)
	:_eUnitState(eState_Drop)
	,_fFloatTime(fduration * 0.5)
	,_fBackTime(fduration * 0.2)
	,_baseOffset(0, 0)
	,_xOffset(ofRandom(0.0, 0.5))
	,_xSigma(ofRandom(0.7, 1.3))
	,_xVol(ofRandom(5, 15))
	,_yOffset(ofRandom(0.0, 0.5))
	,_ySigma(ofRandom(0.7, 1.3))
	,_yVol(ofRandom(5, 15))
{
	_animPosY.setDuration(0.3 * fduration);
	_animPosY.setCurve(AnimCurve::EASE_OUT_ELASTIC);
	
	_animSwing.setDuration(ofRandom(0.05, 0.2) * fduration);
	_animSwing.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
	float fsize_ = ofRandom(100, 150);
	
	_animFloat.setDuration(1.0 * fduration);
	_animFloat.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);
	_animFloat.setCurve(AnimCurve::LINEAR);
	_animFloat.animateFromTo(0, 1);

	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.drawPos.set(ofRandomWidth(), -fsize_ * 2);
	_Giraffe.fsize = fsize_;
	_Giraffe.fswingDegree = 0;
	_Giraffe.tongueL = _Giraffe.fsize * 0.1;
	_Giraffe.fdegree = 180;
	_Giraffe.offsetPos.set(fsize_ * -0.1, fsize_ * -0.5);

	_animPosY.animateFromTo(_Giraffe.drawPos.y, ofRandom(ofGetHeight() * 0.3, ofGetHeight() * 0.6));
}

//--------------------------------------------------------------
void DropUnit::update(float fDelta) 
{
	_animSwing.update(fDelta);
	_animPosY.update(fDelta);
	updateOffset(fDelta);

	switch(_eUnitState)
	{
	case eState_Drop:
	case eState_Back:
		{
			_Giraffe.drawPos.y = _animPosY.getCurrentValue();
			if(_animPosY.getPercentDone() == 1.0 && _animPosY.hasFinishedAnimating())
			{
				if(_eUnitState == eState_Drop)
				{
					_eUnitState = eState_Float;
					int d_ = ofRandom(-1, 1) >= 0?1:-1;
					float fdegree_ = 20.0 * ofRandom(1.0, 3.5);
					_animSwing.animateFromTo(d_ * fdegree_, -d_ * fdegree_);
					_animSwing.setPercentDone(0.5);
				}
				else
				{
					_eUnitState = eState_Finish;
				}
			}
		}
		break;
	case eState_Float:
		{
			_Giraffe.fswingDegree = _animSwing.getCurrentValue();
			_fFloatTime -= fDelta;
			if(_fFloatTime <= 0.0)
			{
				_eUnitState = eState_Back;
				_animPosY.setDuration(_fBackTime);
				_animPosY.setCurve(AnimCurve::EASE_OUT);
				_animPosY.animateTo(-_Giraffe.fsize * 2);
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void DropUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}

	ofPushMatrix();
	ofTranslate(_baseOffset);
	{

		ofPushStyle();
			ofSetLineWidth(_Giraffe.flineWidth);
			ofSetColor(colorMgr::GetInstance()->getForeColor());
			ofLine(ofVec2f(_Giraffe.drawPos.x, -_Giraffe.fsize), _Giraffe.drawPos);
		ofPopStyle();
	
		drawMgr::GetInstance()->draw(_Giraffe);
	}
	ofPopMatrix();
}

//--------------------------------------------------------------
bool DropUnit::canRemove()
{
	return _eUnitState == eState_Finish;
}

//--------------------------------------------------------------
void DropUnit::updateOffset(float fDelta)
{
	_animFloat.update(fDelta);

	float xp_ = _animFloat.getCurrentValue() * _xSigma + _xOffset ;
	float yp_ = _animFloat.getCurrentValue() * _ySigma + _yOffset ;
	_baseOffset.x = sinf(xp_ * TWO_PI) * _xVol;
	_baseOffset.y = sinf(yp_ * TWO_PI) * _yVol;
}