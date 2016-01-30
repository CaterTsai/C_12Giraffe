#include "GPokemon.h"

PokemonUnit::PokemonUnit(float fduration)
	:_eUnitState(eState_BallIn)
	,_fWaitT(0.2 * fduration)
	,_fSummonT(0.1 * fduration)
{
	float fsize_= ofRandom(100, 150);
	float fPosY_ = ofRandom(0.3, 0.7) * ofGetHeight();
	float fStartX_ = 0 - fsize_ * 0.3;
	float fTargetX_ = ofRandom(0.2, 0.5) * ofGetWidth();
	
	int iRotateNum_ = static_cast<int>(abs(fTargetX_ - fStartX_) / (fsize_ * 0.3 * PI) + 0.5);

	//Giraffe
	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.bFill = true;
	_Giraffe.fsize = fsize_ * 0.3;
	_Giraffe.tongueL = _Giraffe.fsize * 0.1;

	//Open Giraffe
	_OpenGiraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_OpenGiraffe.fillcolor = colorMgr::GetInstance()->getForeColor();
	_OpenGiraffe.drawPos.set(fTargetX_, fPosY_);
	_OpenGiraffe.bFill = true;
	_OpenGiraffe.fsize = fsize_;
	_OpenGiraffe.tongueL = fsize_ * 0.1;
	_OpenGiraffe.scaleVec = ofVec2f(0, 0);
	
	//Pokeball
	_Pokeball.linecolor = colorMgr::GetInstance()->getForeColor();
	_Pokeball.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Pokeball.fsize = fsize_ * 0.3;
	_Pokeball.openPerc = 0.0;
	_Pokeball.drawPos.set(fStartX_, fPosY_);

	//Animation
	_animBallX.setDuration(fduration * 0.3);
	_animBallX.setCurve(AnimCurve::EASE_OUT);

	_animBallRotate.setDuration(fduration * 0.3);
	_animBallRotate.setCurve(AnimCurve::EASE_OUT);

	_animBallOpen.setDuration(fduration * 0.15);

	_animGiraffeScale.setDuration(fduration * 0.2);
	_animGiraffeScale.reset(0.0);

	_animGiraffePos.setDuration(fduration * 0.2);
	_animGiraffePos.setPosition(ofVec2f(fTargetX_, fPosY_));

	_animGiraffeColor.setDuration(fduration * 0.2);
	_animGiraffeColor.setColor(colorMgr::GetInstance()->getForeColor());

	_animGiraffeOpen.setDuration(fduration * 0.15);
	_animGiraffeOpen.setCurve(AnimCurve::OBJECT_DROP);
	
	_animBallX.animateFromTo(fStartX_, fTargetX_);
	_animBallRotate.animateFromTo(0, iRotateNum_ * 360.0);
}

//--------------------------------------------------------------
void PokemonUnit::update(float fDelta)
{
	_animBallX.update(fDelta);
	_animBallRotate.update(fDelta);
	_animBallOpen.update(fDelta);
	_animGiraffeScale.update(fDelta);
	_animGiraffePos.update(fDelta);
	_animGiraffeOpen.update(fDelta);
	_animGiraffeColor.update(fDelta);

	switch(_eUnitState)
	{
	case eState_BallIn:
		{
			_Pokeball.drawPos.x = _animBallX.getCurrentValue();
			_Pokeball.fdegree = _animBallRotate.getCurrentValue();
			if(_animBallX.hasFinishedAnimating() && _animBallX.getPercentDone() == 1.0 &&
				_animBallRotate.hasFinishedAnimating() && _animBallRotate.getPercentDone() == 1.0)
			{
				ofVec2f fGiraffePos_(_Pokeball.drawPos + ofVec2f(_OpenGiraffe.fsize, _Pokeball.fsize * 0.5 -_OpenGiraffe.fsize * 0.5));
				_animBallOpen.animateFromTo(0.0, 0.5);
				_animGiraffeScale.animateToAfterDelay(1.0, _fSummonT);
				_animGiraffePos.animateToAfterDelay(fGiraffePos_, _fSummonT);
				_animGiraffeColor.animateToAfterDelay(colorMgr::GetInstance()->getBackColor(), _fSummonT);


				_eUnitState = eState_Summon;
			}
		}
		break;
	case eState_Summon:
		{
			_Pokeball.openPerc = _animBallOpen.getCurrentValue();
			_OpenGiraffe.drawPos.set(_animGiraffePos.getCurrentPosition());
			_OpenGiraffe.scaleVec.set(_animGiraffeScale.getCurrentValue());
			_OpenGiraffe.fillcolor = _animGiraffeColor.getCurrentColor();

			if(_animGiraffePos.hasFinishedAnimating() && _animGiraffePos.getPercentDone() == 1.0 &&
				_animGiraffeScale.hasFinishedAnimating() && _animGiraffeScale.getPercentDone() == 1.0)
			{
				_Giraffe.drawPos = _OpenGiraffe.drawPos;
				_animGiraffeOpen.animateFromTo(0.0, 1.0);
				_eUnitState = eState_Open;
			}
		}
		break;
	case eState_Open:
		{
			_OpenGiraffe.openPerc = _animGiraffeOpen.getCurrentValue();
			if(_animGiraffeOpen.hasFinishedAnimating() && _animGiraffeOpen.getPercentDone() == 1.0)
			{
				_eUnitState = eState_Waiting;
			}
		}
		break;
	case eState_Waiting:
		{
			_fWaitT -= fDelta;
			if(_fWaitT <= 0.0)
			{
				_animGiraffeOpen.setCurve(AnimCurve::EASE_IN_EASE_OUT);
				_animGiraffeOpen.animateFromTo(1.0, 0.0);
				_eUnitState = eState_Close;
			}
		}
		break;
	case eState_Close:
		{
			_OpenGiraffe.openPerc = _animGiraffeOpen.getCurrentValue();
			if(_animGiraffeOpen.hasFinishedAnimating() && _animGiraffeOpen.getPercentDone() == 1.0)
			{
				_animBallOpen.animateToAfterDelay(0.0, _fSummonT);
				_animGiraffeScale.animateTo(0.0);
				_animGiraffePos.animateTo(_Pokeball.drawPos);
				_animGiraffeColor.animateTo(colorMgr::GetInstance()->getForeColor());
				_eUnitState = eState_Back;
			}
		}
		break;
	case eState_Back:
		{
			_Pokeball.openPerc = _animBallOpen.getCurrentValue();
			_OpenGiraffe.drawPos.set(_animGiraffePos.getCurrentPosition());
			_OpenGiraffe.scaleVec.set(_animGiraffeScale.getCurrentValue());
			_OpenGiraffe.fillcolor = _animGiraffeColor.getCurrentColor();

			if(_animBallOpen.hasFinishedAnimating() && _animBallOpen.getPercentDone() == 1.0 &&
				_animGiraffeScale.hasFinishedAnimating() && _animGiraffeScale.getPercentDone() == 1.0)
			{
				_animBallX.animateTo(_Pokeball.fsize * -1);
				_animBallRotate.animateTo(0);
				_eUnitState = eState_Ballout;
			}
		}
		break;
	case eState_Ballout:
		{
			_Pokeball.drawPos.x = _animBallX.getCurrentValue();
			_Pokeball.fdegree = _animBallRotate.getCurrentValue();
			if(_animBallX.hasFinishedAnimating() && _animBallX.getPercentDone() == 1.0 &&
				_animBallRotate.hasFinishedAnimating() && _animBallRotate.getPercentDone() == 1.0)
			{
				_eUnitState = eState_Finish;
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void PokemonUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}

	drawMgr::GetInstance()->draw(_Pokeball);

	if(_eUnitState == eState_Open || _eUnitState == eState_Waiting || _eUnitState == eState_Close)
	{
		drawMgr::GetInstance()->draw(_Giraffe);
	}

	if(_eUnitState != eState_BallIn && _eUnitState != eState_Ballout)
	{
		drawMgr::GetInstance()->draw(_OpenGiraffe);
	}


}

//--------------------------------------------------------------
bool PokemonUnit::canRemove()
{
	return _eUnitState == eState_Finish;
}