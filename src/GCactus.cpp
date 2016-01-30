#include "GCactus.h"

CactusUnit::CactusUnit(float fduration)
	:_eUnitState(eState_RunIn)
	,_fWaitT(fduration * 0.4)
	,_fShadowDelay(fduration * 0.1)
{

	float fsize_ = ofRandom(70, 130);
	float ftargetX_ = ofRandom(0.3, 0.7) * ofGetWidth();

	float fstartH_ = ofRandomHeight();

	//Cactus
	_Cactus.linecolor = colorMgr::GetInstance()->getForeColor();
	_Cactus.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Cactus.fsize = fsize_;
	_Cactus.drawPos.set(ftargetX_ + ofGetWidth() * 0.6, fstartH_);
	float basic_ = fsize_ / 7.0;
	_Cactus.rotateAxis.set(basic_ * -1.75, basic_ * 3.5);
	_Cactus.fdegree = cCACTUS_BASE_DEGREE;

	//Giraffe
	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.fsize = fsize_ * 0.7;
	_Giraffe.drawPos.set(_Cactus.drawPos);
	_Giraffe.offsetPos.set(_Giraffe.fsize * -0.2, _Giraffe.fsize * -0.5);
	_Giraffe.fdegree = cGIRAFFE_BASE_DEGREE;

	//Animation
	_animPosY.setDuration(fduration * 0.3);
	_animPosY.setCurve(AnimCurve::EASE_OUT);
	
	_animShadows.setDuration(fduration * 0.3);
	_animShadows.setCurve(AnimCurve::EASE_OUT);
	_animShadows.reset(_Cactus.drawPos.x);

	_animDegree.setDuration(fduration * 0.1);
	_animDegree.setCurve(AnimCurve::EASE_OUT);
	_animDegree.reset(_Cactus.fdegree);

	_animPosY.animateFromTo(_Cactus.drawPos.x, ftargetX_);
	_animShadows.animateToAfterDelay(ftargetX_, _fShadowDelay);
	_animDegree.animateToAfterDelay(_Cactus.fdegree - 30, fduration * 0.2);
}

//--------------------------------------------------------------
void CactusUnit::update(float fDelta)
{
	_animPosY.update(fDelta);
	_animShadows.update(fDelta);
	_animDegree.update(fDelta);

	switch(_eUnitState)
	{
	case eState_RunIn:
		{
			_Cactus.drawPos.x = _animPosY.getCurrentValue();
			_Cactus.fdegree = _animDegree.getCurrentValue();

			_Giraffe.drawPos.x = _animPosY.getCurrentValue();
			_Giraffe.fdegree = _Cactus.fdegree - cCACTUS_BASE_DEGREE + cGIRAFFE_BASE_DEGREE;

			if(_animPosY.hasFinishedAnimating() && _animPosY.getPercentDone() == 1.0 &&
				_animDegree.hasFinishedAnimating() && _animDegree.getPercentDone() == 1.0)
			{
				_animDegree.setCurve(AnimCurve::EASE_OUT_ELASTIC);
				_animDegree.animateTo(-15);

				_eUnitState = eState_Stop;
			}
		}
		break;
	case eState_Stop:
		{
			_Cactus.fdegree = _animDegree.getCurrentValue();
			_Giraffe.fdegree = _Cactus.fdegree - cCACTUS_BASE_DEGREE + cGIRAFFE_BASE_DEGREE;
			if(_animDegree.hasFinishedAnimating() && _animDegree.getPercentDone() == 1.0)
			{
				_eUnitState = eState_Wait;
			}
		}
		break;
	case eState_Wait:
		{
			_fWaitT -= fDelta;
			if(_fWaitT <= 0.0)
			{
				_eUnitState = eState_RunOut;
				_animPosY.animateTo(-ofGetWidth() * 0.2);
				_animShadows.animateToAfterDelay(-ofGetWidth() * 0.2,_fShadowDelay);
			}
		}
		break;
	case eState_RunOut:
		{
			_Cactus.drawPos.x = _animPosY.getCurrentValue();
			_Giraffe.drawPos.x = _animPosY.getCurrentValue();
			if(_animPosY.hasFinishedAnimating() && _animPosY.getPercentDone() == 1.0)
			{
				_eUnitState = eState_Finish;
			}
		}
		break;
	}

}

//--------------------------------------------------------------
void CactusUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}

	//Shadows
	drawShadow();

	drawMgr::GetInstance()->draw(_Giraffe);
	drawMgr::GetInstance()->draw(_Cactus);
}

//--------------------------------------------------------------
bool CactusUnit::canRemove()
{
	return _eUnitState == eState_Finish;
}

//--------------------------------------------------------------
void CactusUnit::drawShadow()
{
	float fDiff_ = abs(_Cactus.drawPos.x - _animShadows.getCurrentValue());
	
	if(fDiff_ < _Cactus.fsize * 0.1)
	{
		return;
	}

	float fDist_ = fDiff_ * 0.2;
	ofVec2f copyPos_ = _Cactus.drawPos;
	
	for(int idx_ = 0; idx_ < cCACTUS_SHADOW_NUM; idx_++)
	{
		_Cactus.falpha *= 0.8;
		_Cactus.drawPos.x += fDist_;
		_Giraffe.falpha *= 0.8;
		_Giraffe.drawPos.x += fDist_;

		fDist_ *= 1.5;

		drawMgr::GetInstance()->draw(_Giraffe);
		drawMgr::GetInstance()->draw(_Cactus);
	}

	_Cactus.falpha = 255;
	_Cactus.drawPos = copyPos_;

	_Giraffe.falpha = 255;
	_Giraffe.drawPos = copyPos_;
}