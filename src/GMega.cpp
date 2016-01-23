#include "GMega.h"

//--------------------------------------------------------------
MegaUnit::MegaUnit(float fduration)
	:_eUnitState(eState_Enter)
	,_iChargeLevel(1)
	,_iChargeSpeed(10)
	,_fChargeT(fduration * 0.4)
	,_fChargeTimer(_fChargeT)
	,_fWaitT(fduration * 0.2)
{
	float fSize_ = ofRandom(80, 130);

	_animPosY.setDuration(0.15 * fduration);

	_animScaleX.reset(0.2);
	_animScaleX.setDuration(0.05 * fduration);
	
	_animTongue.setDuration(0.1 * fduration);
	_animTongue.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH_ONCE);


	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.bFill = true;
	_Giraffe.drawPos.set(ofRandomWidth(), -fSize_);
	_Giraffe.fsize = fSize_;
	_Giraffe.tongueL = fSize_ * 0.1;
	_Giraffe.scaleVec.set(0.3, 1.0);

	_animPosY.animateFromTo(-fSize_, ofRandom(0.2 * ofGetHeight(), 0.8 * ofGetHeight()));
	_animScaleX.animateToAfterDelay(1.0, 0.1 * fduration);
		
}

//--------------------------------------------------------------
void MegaUnit::update(float fDelta) 
{
	_animPosY.update(fDelta);
	_animScaleX.update(fDelta);
	_animTongue.update(fDelta);

	switch(_eUnitState)
	{
	case eState_Enter:
	case eState_Exit:
		{
			_Giraffe.drawPos.y = _animPosY.getCurrentValue();
			_Giraffe.scaleVec.x = _animScaleX.getCurrentValue();

			if(_animPosY.getPercentDone() == 1.0 && _animPosY.hasFinishedAnimating() &&
				_animScaleX.getPercentDone() == 1.0 && _animScaleX.hasFinishedAnimating())
			{
				_eUnitState = (_eUnitState == eState_Enter)?eState_Charge:eState_Finish;
			}
		}
		break;
	case eState_Charge:
		{
			_fChargeTimer -= fDelta;
			if(_fChargeTimer <= 0.0)
			{
				if(_iChargeLevel > cMAX_CHARGE_LEVEL)
				{
					_eUnitState	= eState_Fire;
					_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
					_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
					_Giraffe.tongueD = ofRandom(-45, -5);
					_animTongue.animateFromTo(_Giraffe.tongueL, _Giraffe.tongueL * 25);
				}
				else
				{
					_iChargeLevel++;
					_fChargeTimer = _fChargeT;
				}
			}
			else
			{
				if(ofGetFrameNum() % (int)(20 / _iChargeLevel) == 0 || ofGetFrameNum() % (int)(20 / _iChargeLevel) == 1)
				{
					_Giraffe.linecolor = colorMgr::GetInstance()->getBackColor();
					_Giraffe.fillcolor = colorMgr::GetInstance()->getForeColor();
				}
				else
				{
					_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
					_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
				}
			}
		}
		break;
	case eState_Fire:
		{
			_Giraffe.tongueL = _animTongue.getCurrentValue();
			
			if(_animTongue.getPercentDone() == 0.0 && _animTongue.hasFinishedAnimating() )
			{
				_fWaitT -= fDelta;
				if(_fWaitT <= 0.0)
				{
					_eUnitState = eState_Exit;
					_animPosY.animateTo(-_Giraffe.fsize);
					_animScaleX.animateTo(0.2);
				}
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void MegaUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}

	drawMgr::GetInstance()->draw(_Giraffe);
}

//--------------------------------------------------------------
bool MegaUnit::canRemove()
{
	return (_eUnitState == eState_Finish);
}