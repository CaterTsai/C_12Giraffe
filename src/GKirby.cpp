#include "GKirby.h"

//--------------------------------------------------------------
KirbyUnit::KirbyUnit(float fduration)
	:_eUnitState(eState_Flyin)
{
	float fSize_ = ofRandom(100, 150);
	float degree_ = ofRandom(-30, 30);

	ofVec2f targetP_(ofGetWidth() * ofRandom(0.2, 0.8), ofGetHeight() * ofRandom(0.2, 0.8));
	ofVec2f sourceP_ = targetP_ + ofVec2f(0, -1).rotate(ofRandom(20, 60) * ((rand() % 2 == 0)?1:-1)) * ofGetHeight();

	ofVec2f starVec_ = targetP_ - sourceP_;

	//Animation
	_animBigStarPos.setPosition(sourceP_);
	_animBigStarPos.setDuration(fduration * 0.6);
	_animBigStarPos.setCurve(AnimCurve::EASE_IN);

	_animSmallStarX.setDuration(fduration * 0.2);
	_animSmallStarX.setCurve(AnimCurve::LINEAR);

	_animSmallStarY.setDuration(fduration * 0.1);
	_animSmallStarY.setCurve(AnimCurve::EASE_IN);
	_animSmallStarY.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH_ONCE);
	
	_animStarAlpha.setDuration(fduration * 0.2);
	_animStarAlpha.setCurve(AnimCurve::VERY_LATE_LINEAR);

	_animGiraffeX.setDuration(fduration * 0.4);
	_animGiraffeX.setCurve(AnimCurve::LINEAR);

	_animGiraffeY.setDuration(fduration * 0.2);
	_animGiraffeY.setCurve(AnimCurve::EASE_IN);
	_animGiraffeY.setRepeatType(AnimRepeat::LOOP_BACK_AND_FORTH_ONCE);

	_animGiraffeRotate.setDuration(fduration * 0.1);
	_animGiraffeRotate.setCurve(AnimCurve::LINEAR);
	_animGiraffeRotate.setRepeatType(AnimRepeat::LOOP);

	_animGiraffeAlpha.setDuration(fduration * 0.4);
	_animGiraffeAlpha.setCurve(AnimCurve::VERY_LATE_LINEAR);

	//Big Star
	_BigStar.bFill = true;
	_BigStar.linecolor = colorMgr::GetInstance()->getForeColor();
	_BigStar.fillcolor = colorMgr::GetInstance()->getBackColor();
	_BigStar.fsize = fSize_;
	_BigStar.drawPos.set(sourceP_);
	_BigStar.fdegree = degree_;
	
	//Smell Star
	for(auto& star_ : _SmallStars)
	{
		star_.bFill = true;
		star_.fillcolor = colorMgr::GetInstance()->getForeColor();
		star_.linecolor = colorMgr::GetInstance()->getBackColor();
		star_.fsize = fSize_ * ofRandom(0.25, 0.4);
		star_.drawPos.set(targetP_);
		star_.fdegree = ofRandom(0, 359);
	}

	ofVec2f vec_ = ofVec2f(0, -1).rotate(ofRandom(-70, -15));
	for(auto& starVec_ : _SmallStarsVec)
	{
		starVec_ =  vec_ * fSize_ * ofRandom(1.0, 2.0);
		starVec_.y *= 0.5;
		vec_.rotate(ofRandom(30, 60));
	}

	//Giraffe
	_Giraffe.linecolor = colorMgr::GetInstance()->getForeColor();
	_Giraffe.fillcolor = colorMgr::GetInstance()->getBackColor();
	_Giraffe.fsize = fSize_ * 0.6;
	_Giraffe.drawPos.set(sourceP_ + ofVec2f(0, -_Giraffe.fsize/2));
	_Giraffe.fdegree = degree_ + 30.0;

	_GiraffeVec = starVec_.normalize() * fSize_;
	_GiraffeVec.y = -_GiraffeVec.y;

	_animBigStarPos.animateTo(targetP_);
}

//--------------------------------------------------------------
void KirbyUnit::update(float fDelta)
{
	_animBigStarPos.update(fDelta);
	_animSmallStarX.update(fDelta);
	_animSmallStarY.update(fDelta);
	_animStarAlpha.update(fDelta);

	_animGiraffeX.update(fDelta);
	_animGiraffeY.update(fDelta);
	_animGiraffeAlpha.update(fDelta);
	_animGiraffeRotate.update(fDelta);

	switch(_eUnitState)
	{
	case eState_Flyin:
		{
			_BigStar.drawPos.set(_animBigStarPos.getCurrentPosition());
			_Giraffe.drawPos.set(_BigStar.drawPos + ofVec2f(0, -_Giraffe.fsize/2));
			if(_animBigStarPos.hasFinishedAnimating() && _animBigStarPos.getPercentDone() == 1.0)
			{
				_eUnitState = eState_Crash;
				_animSmallStarX.animateFromTo(0.0, 1.0);
				_animSmallStarY.animateFromTo(0.0, 1.0);
				_animGiraffeX.animateFromTo(0.0, 1.0);
				_animGiraffeY.animateFromTo(0.0, 1.0);
				_animStarAlpha.animateFromTo(1.0, 0.0);
				_animGiraffeAlpha.animateFromTo(1.0, 0.0);
				_animGiraffeRotate.animateFromTo(0.0, 359);
			}
		}
		break;
	case eState_Crash:
		{
			ofVec2f offset_;
			offset_.x = (_GiraffeVec.x * _animGiraffeX.getCurrentValue());
			offset_.y = (_GiraffeVec.y * _animGiraffeY.getCurrentValue());
			_Giraffe.drawPos.set(_BigStar.drawPos + offset_);
			_Giraffe.falpha = _animGiraffeAlpha.getCurrentValue() * 255;
			_Giraffe.fdegree = _BigStar.fdegree + 30 + _animGiraffeRotate.getCurrentValue();

			for(int idx_ = 0; idx_ < 3; idx_++)
			{
				ofVec2f offset_;
				offset_.x = (_SmallStarsVec[idx_].x * _animSmallStarX.getCurrentValue());
				offset_.y = (_SmallStarsVec[idx_].y * _animSmallStarY.getCurrentValue());
				_SmallStars[idx_].drawPos.set(_BigStar.drawPos + offset_);
				_SmallStars[idx_].falpha = _animStarAlpha.getCurrentValue() * 255;
			}

			if(_animGiraffeX.hasFinishedAnimating() && _animGiraffeX.getPercentDone() == 1.0)
			{
				_eUnitState = eState_Finish;
			}
		}
		break;
	}

}

//--------------------------------------------------------------
void KirbyUnit::draw()
{
	if(_eUnitState == eState_Finish)
	{
		return;
	}
	
	drawMgr::GetInstance()->draw(_Giraffe);
	if(_eUnitState == eState_Flyin)
	{
		drawMgr::GetInstance()->draw(_BigStar);
	}
	else
	{
		for(auto& smallStar_ : _SmallStars)
		{
			drawMgr::GetInstance()->draw(smallStar_);
		}
	}
	
}

//--------------------------------------------------------------
bool KirbyUnit::canRemove()
{
	return (_eUnitState == eState_Finish);
}