#include "GMario.h"

//--------------------------------------------------------------
MarioUnit::MarioUnit(float fduration)
	:_eUnitState(eState_PipeEnter)
	,_fWaitT(fduration * 0.25)
{
	float fSize_ = ofRandom(80, 120);
	float fPosX_ = ofRandomWidth();
		
	_animPipeY.setDuration(fduration * 0.2);
	
	_animGiraffeY.setDuration(fduration * 0.15);
	_animGiraffeY.setCurve(AnimCurve::BOUNCY);

	_animFlowerY.setDuration(fduration * 0.1);
	_animFlowerY.setCurve(AnimCurve::BOUNCY);

	_animFlowerPrec.reset(0.0);
	_animFlowerPrec.setDuration(fduration * 0.1);

	//Pipe
	_Pipe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Pipe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Pipe.fsize = fSize_ / 2.2;
	_Pipe.fPipeLength = ofRandom(ofGetHeight() * 0.2, ofGetHeight() * 0.6);
	_Pipe.drawPos.set(fPosX_, ofGetHeight() + (_Pipe.fPipeLength + _Pipe.fsize)/2);

	//Giraffe
	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.bFill = true;
	_Giraffe.fsize = fSize_;
	_Giraffe.tongueL = _Giraffe.fsize * 0.1;
	_Giraffe.drawPos.set(fPosX_, ofGetHeight() + fSize_);

	//Flower
	_Flower.linecolor = colorMgr::GetInstance()->getForeColor();
	_Flower.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Flower.fsize = fSize_ * 0.3;
	_Flower.drawPos.set(fPosX_ + _Giraffe.fsize * 0.025, ofGetHeight() + _Flower.fsize);
	_Flower.fFlowerPrec = 0.0;
	_Flower.fLeafPrec = 0.0;

	_fFlowerT = fduration * 0.1;

	_animPipeY.animateFromTo(_Pipe.drawPos.y,  ofGetHeight() - _Pipe.fPipeLength/2);
}

//--------------------------------------------------------------
void MarioUnit::update(float fDelta)
{
	_animPipeY.update(fDelta);
	_animGiraffeY.update(fDelta);
	_animFlowerY.update(fDelta);
	_animFlowerPrec.update(fDelta);

	switch(_eUnitState)
	{
	case eState_PipeEnter:
		{
			_Pipe.drawPos.y = _animPipeY.getCurrentValue();
			if(_animPipeY.hasFinishedAnimating() && _animPipeY.getPercentDone() == 1.0)
			{
				_eUnitState = eState_GiraffeEnter;
				float PipeH_ = _Pipe.drawPos.y - _Pipe.fPipeLength/2;
				_animGiraffeY.animateFromTo(PipeH_+ _Giraffe.fsize, PipeH_ - _Giraffe.fsize/2);
			}
		}
		break;
	case eState_GiraffeEnter:
		{
			_Giraffe.drawPos.y = _animGiraffeY.getCurrentValue();
			if(_animGiraffeY.hasFinishedAnimating() && _animGiraffeY.getPercentDone() == 1.0)
			{
				_eUnitState = eState_FlowerEnter;
				float GiraffeH_ = _Giraffe.drawPos.y - _Giraffe.fsize/2;
				_animFlowerY.animateFromTo(GiraffeH_ + _Flower.fsize, GiraffeH_ -  _Giraffe.fsize * 0.1 -_Flower.fsize/2);
				
				_animFlowerPrec.animateToAfterDelay(1.0, _fFlowerT);
			}
		}
		break;
	case eState_FlowerEnter:
		{
			_Flower.drawPos.y = _animFlowerY.getCurrentValue();
			_Flower.fFlowerPrec = _Flower.fLeafPrec =_animFlowerPrec.getCurrentValue();
			 
			if(_animFlowerPrec.hasFinishedAnimating() && _animFlowerPrec.getPercentDone() == 1.0)
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
				_animFlowerY.animateToAfterDelay(_Giraffe.drawPos.y - _Giraffe.fsize/2 + _Flower.fsize, _fFlowerT);
				_animFlowerPrec.animateTo(0.0);
				_eUnitState = eState_FlowerExit;
			}
		}
		break;
	case eState_FlowerExit:
		{
			_Flower.drawPos.y = _animFlowerY.getCurrentValue();
			_Flower.fFlowerPrec = _Flower.fLeafPrec =_animFlowerPrec.getCurrentValue();

			if(_animFlowerPrec.hasFinishedAnimating() && _animFlowerPrec.getPercentDone() == 1.0 && 
				_animFlowerY.hasFinishedAnimating() && _animFlowerY.getPercentDone() == 1.0)
			{
				_animGiraffeY.animateTo(_Pipe.drawPos.y - _Pipe.fPipeLength/2 + _Giraffe.fsize);
				_eUnitState = eState_GiraffeExit;
			}
		}
		break;
	case eState_GiraffeExit:
		{
			_Giraffe.drawPos.y = _animGiraffeY.getCurrentValue();
			if(_animGiraffeY.hasFinishedAnimating() && _animGiraffeY.getPercentDone() == 1.0)
			{
				_eUnitState = eState_PipeExit;
				_animPipeY.animateTo(ofGetHeight() + (_Pipe.fPipeLength + _Pipe.fsize)/2);
			}
		}
		break;
	case eState_PipeExit:
		{
			_Pipe.drawPos.y = _animPipeY.getCurrentValue();

			if(_animPipeY.hasFinishedAnimating() && _animPipeY.getPercentDone() == 1.0)
			{
				_eUnitState = eState_Finish;
			}
		}
		break;
	}

}

//--------------------------------------------------------------
void MarioUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}

	if(_eUnitState == eState_FlowerEnter || _eUnitState == eState_FlowerExit || _eUnitState == eState_Waiting)
	{
		drawMgr::GetInstance()->draw(_Flower);
	}

	if(_eUnitState != eState_PipeEnter && _eUnitState != eState_PipeExit)
	{
		drawMgr::GetInstance()->draw(_Giraffe);
	}	
	drawMgr::GetInstance()->draw(_Pipe);
}

//--------------------------------------------------------------
bool MarioUnit::canRemove()
{
	return (_eUnitState == eState_Finish);
}