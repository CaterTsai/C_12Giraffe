#include "GJetPack.h"

#pragma region JetpackUnit
//--------------------------------------------------------------
JetpackUnit::JetpackUnit(float fduration)
	:_fWaitTime(fduration * 0.4)
	,_fFlyoutTime(fduration * 0.4)
	,_eUnitState(eState_Flyin)
{
	float fsize_ = ofRandom(60, 150);
	ofVec2f startPos_ = getRangePos();
	_targetPos = getRangePos();

	//Giraffe and Jetpack
	ofVec2f neck_( 7 - 25, -35 - 50);
	neck_.normalize();
	ofVec2f up_(0, -1);
	_fneckDegree = up_.angle(neck_);

	_Giraffe.fsize = fsize_;
	_Giraffe.fdegree = -_fneckDegree;
	_Giraffe.tongueL = _Giraffe.fsize * 0.1;
	_Giraffe.drawPos = startPos_;

	_Jetpack.fsize = fsize_ * 0.5;
	_Jetpack.fBeltLength = fsize_ * 0.25;
	_Jetpack.drawPos = startPos_;
	_Jetpack.fFireLength = _Jetpack.fsize * 0.7;

	_fFloatDist =  ofRandom(fsize_ * 0.2, fsize_ * 0.4);

	float frotateDegree_ = ofVec2f(0, -1).angle(ofVec2f(ofGetWidth()/2, ofGetHeight()/2) - startPos_);
	
	//Animation
	_animPosX.setDuration(fduration * 0.4);
	_animPosX.setCurve(AnimCurve::EASE_OUT);

	_animPosY.setDuration(fduration * 0.4);
	_animPosY.setCurve(AnimCurve::EASE_OUT);

	_animFloat.setDuration(fduration * 0.2);
	_animFloat.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH);	

	_animRotate.setDuration(fduration * 0.4);
	_animRotate.setCurve(AnimCurve::LATE_EASE_IN_EASE_OUT);

	_animPosX.animateFromTo(startPos_.x, ofGetWidth()/2);
	_animPosY.animateFromTo(startPos_.y, ofGetHeight()/2);
	_animRotate.animateFromTo(frotateDegree_, 0);

}

//--------------------------------------------------------------
void JetpackUnit::update(float fDelta)
{
	_animPosX.update(fDelta);
	_animPosY.update(fDelta);
	_animRotate.update(fDelta);
	_animFloat.update(fDelta);

	switch(_eUnitState)
	{
	case eState_Flyin:
		{
			float frotateDegree_ = _animRotate.getCurrentValue();
			ofVec2f pos_(_animPosX.getCurrentValue(), _animPosY.getCurrentValue());
			ofVec2f vec_(0, -1);
			vec_ = vec_.getRotated(frotateDegree_ + 90);

			 if(pos_.distance(_Giraffe.drawPos) > 2.0)
			 {
				 _Giraffe.drawPos.set(pos_);
				_Jetpack.drawPos.set(pos_ +  vec_ * _Jetpack.fBeltLength);
				_Giraffe.fdegree = -_fneckDegree + frotateDegree_;
				_Jetpack.fdegree = frotateDegree_;
			 }

			 if((_animPosX.hasFinishedAnimating() && _animPosX.getPercentDone() == 1.0) &&
				(_animPosY.hasFinishedAnimating() && _animPosY.getPercentDone() == 1.0))
			{
					_eUnitState = eState_Wait;
					float fStartPercent_ = ofRandom(0.2, 0.8);
					_fFloatStartY = _Giraffe.drawPos.y - fStartPercent_ * _fFloatDist;
					
					_Jetpack.fFireLength = _Jetpack.fsize * 0.4;

					_animFloat.animateFromTo(0, 1);
					_animFloat.setPercentDone(fStartPercent_);
			}
		}
		break;
	case eState_Wait:
		{
			float fFloatY_ = _fFloatStartY + _fFloatDist * _animFloat.getCurrentValue();
			ofVec2f pos_( _Giraffe.drawPos.x, fFloatY_);

			 _Giraffe.drawPos.set(pos_);
			_Jetpack.drawPos.set(pos_.x + _Jetpack.fBeltLength, pos_.y);
			_fWaitTime -= fDelta;
			if(_fWaitTime <= 0.0)
			{
				_eUnitState = eState_Rotate;

				float frotateDegree_ = ofVec2f(0, -1).angle(_targetPos -  _Giraffe.drawPos);
				_animRotate.animateFromTo(0, frotateDegree_);
			}
		}
		break;
	case eState_Rotate:
		{
			float frotateDegree_ = _animRotate.getCurrentValue();

			ofVec2f vec_(0, -1);
			vec_ = vec_.getRotated(frotateDegree_ + 90);
			
			_Giraffe.fdegree = -_fneckDegree + frotateDegree_;
			_Jetpack.drawPos.set(_Giraffe.drawPos +  vec_ * _Jetpack.fBeltLength);
			_Jetpack.fdegree = frotateDegree_;

			if(_animRotate.hasFinishedAnimating() && _animRotate.getPercentDone() == 1.0)
			{				
				_Jetpack.fFireLength = _Jetpack.fsize * 0.7;
				
				_animPosX.setCurve(AnimCurve::EASE_IN);
				_animPosX.animateFromTo(_Giraffe.drawPos.x, _targetPos.x);
				
				_animPosY.setCurve(AnimCurve::EASE_IN);
				_animPosY.animateFromTo(_Giraffe.drawPos.y, _targetPos.y);
				_eUnitState = eState_Flyout;
			}
		}
		break;
	case eState_Flyout:
		{
			ofVec2f pos_(_animPosX.getCurrentValue(), _animPosY.getCurrentValue());
			ofVec2f vec_(pos_ - _Giraffe.drawPos);
			vec_.normalize();
			ofVec2f vecV_ = vec_.getRotated(90);
			float frotateDegree_ = ofVec2f(0, -1).angle(vec_);

			 if(pos_.distance(_Giraffe.drawPos) > 2.0)
			{
				 _Giraffe.drawPos.set(pos_);
				_Jetpack.drawPos.set(pos_ +  vecV_ * _Jetpack.fBeltLength);
				_Giraffe.fdegree = -_fneckDegree + frotateDegree_;
				_Jetpack.fdegree = frotateDegree_;
			 }

			if((_animPosX.hasFinishedAnimating() && _animPosX.getPercentDone() == 1.0) &&
				(_animPosY.hasFinishedAnimating() && _animPosY.getPercentDone() == 1.0))
			{
					_eUnitState = eState_Finish;
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void JetpackUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}

	drawMgr::GetInstance()->draw(_Giraffe);
	drawMgr::GetInstance()->draw(_Jetpack);
}

//--------------------------------------------------------------
bool JetpackUnit::canRemove()
{
	return (_eUnitState == eState_Finish);
}

//--------------------------------------------------------------
ofVec2f JetpackUnit::getRangePos()
{
	ofVec2f result_(0);
	switch(rand() % 4)
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
			result_.y = ofGetHeight();;
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
#pragma endregion
