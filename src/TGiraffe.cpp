#include "TGiraffe.h"

//--------------------------------------------------------------
TGiraffe::TGiraffe()
	:_isTransform(false)
{
	_Giraffe.drawPos.set(ofGetWidth()/2, ofGetHeight()/2);
	_Giraffe.rotateAxis.set(_Giraffe.fsize * 0.05, 0.4 * _Giraffe.fsize);
	_fBasicSize = 100;
}

//--------------------------------------------------------------
void TGiraffe::update(float fDelta)
{
	if(!_isTransform)
	{
		return;
	}
	_animScale.update(fDelta);
	_animRotate.update(fDelta);
	switch(_eState)
	{
	case eState_ZoomIn:
		{
			_Giraffe.fsize = _fBasicSize * _animScale.getCurrentValue();
			_Giraffe.tongueL = _Giraffe.fsize * 0.1;
			_Giraffe.offsetPos.set(_Giraffe.fsize * 0.05, 0.4 * _Giraffe.fsize);

			if(_animScale.hasFinishedAnimating() && _animScale.getPercentDone() == 1.0)
			{
				_eState = eState_Wait;
			}
		}
		break;
	case eState_Wait:
		{
			_fWaitTimer -= fDelta;
			if(_fWaitTimer <= 0)
			{
				_animScale.setDuration(cTGIRAFFE_DURATION * 0.3);
				
				_animRotate.animateFromTo(0, 359);
				_animScale.animateFromTo(1.0, 0.0);
				_eState = eState_RotateAndOut;
			}
		}
		break;
	case eState_RotateAndOut:
		{
			_Giraffe.scaleVec.set(_animScale.getCurrentValue());
			_Giraffe.fdegree = _animRotate.getCurrentValue();

			if(_animScale.hasFinishedAnimating() && _animScale.getPercentDone() == 1.0)
			{
				_isTransform = false;
			}
		}
		break;
	}


}

//--------------------------------------------------------------
void TGiraffe::draw()
{
	if(!_isTransform)
	{
		return;
	}

	drawMgr::GetInstance()->draw(_Giraffe);

	if(_eState == eState_ZoomIn)
	{
		float fscreenScale_ = _animScale.getCurrentValue() / _fStartScale;
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
		ofScale(fscreenScale_, fscreenScale_);
		{
			_screen.draw(-_screen.width/2, -_screen.height/2);
		}
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void TGiraffe::transform()
{
	if(_isTransform)
	{
		return;
	}	
	
	_screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	
	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.scaleVec.set(1);
	_fStartScale = MAX(ofGetWidth(), ofGetHeight())/2 * sqrt(2) / (0.025 * _fBasicSize);
	
	_eState = eState_ZoomIn;
	_fWaitTimer = cTGIRAFFE_DURATION * 0.2;
	
	_animScale.setDuration(cTGIRAFFE_DURATION * 0.5);
	_animRotate.setDuration(cTGIRAFFE_DURATION * 0.3);
	
	_animScale.animateFromTo(_fStartScale, 1);	
	
	_isTransform = true;
}

//--------------------------------------------------------------
bool TGiraffe::isTransform()
{
	return _isTransform;
}