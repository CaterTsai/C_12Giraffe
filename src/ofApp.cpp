#include "ofApp.h"

#pragma region Basic Method
//--------------------------------------------------------------
void ofApp::setup()
{
	ofEnableSmoothing();
	ofSetCircleResolution(30);
	ofBackground(255);

	colorMgr::GetInstance();
	drawMgr::GetInstance();

	//Setup giraffe
	initialGiraffe();

	//Debug
	//_p.drawPos.set(ofGetWidth()/2, ofGetHeight()/2);
	//_p.fsize = _p.fsize * 1000;
	//_p.offsetPos.set(_p.fsize * 0.05, 0.4 * _p.fsize);
	
	_fMainTimer = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update()
{
	float fDelta_ = ofGetElapsedTimef() - _fMainTimer;
	_fMainTimer += fDelta_;

	if(_bGSetup)
	{
		for(auto& Iter_ : _GMap)
		{
			Iter_.second->update(fDelta_);
		}
	}

	_tGiraffe.update(fDelta_);
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if(_bGSetup)
	{
		for(auto& Iter_ : _GMap)
		{
			Iter_.second->draw();
		}
	}

	_tGiraffe.draw();

	//Debug
	//drawMgr::GetInstance()->draw(_p);

	//ofSetColor(255, 0, 0);
	//ofLine(ofVec2f(0, ofGetHeight()/2), ofVec2f(ofGetWidth(), ofGetHeight()/2));
}

//--------------------------------------------------------------
void ofApp::exit()
{
	drawMgr::Destroy();
	colorMgr::Destroy();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch(key)
	{
	case 'q':
		{
			_GMap[NAME_MGR::G_JUMP]->add(0, 0);
		}
		break;
	case 'w':
		{
			_GMap[NAME_MGR::G_ENTER]->add(0, 0);
		}
		break;
	case 'e':
		{
			_GMap[NAME_MGR::G_ELEVATOR]->add(0, 0);
		}
		break;
	case 'r':
		{
			_GMap[NAME_MGR::G_JETPACK]->add(0, 0);
		}
		break;
	case '1':
		{
			if(!_tGiraffe.isTransform())
			{	
				resetGiraffe();
				colorMgr::GetInstance()->changeColor();

				_tGiraffe.transform();
				ofBackground(colorMgr::GetInstance()->getBackColor());
			}
		}
		break;
	}
}
#pragma endregion

#pragma region Giraffe12
void ofApp::initialGiraffe()
{
	_bGSetup = true;

	auto pJump_ = ofPtr<GJump>(new GJump(1.0));
	_GMap.insert(make_pair(NAME_MGR::G_JUMP, pJump_));

	auto pEnter_ = ofPtr<GEnter>(new GEnter(1.0));
	_GMap.insert(make_pair(NAME_MGR::G_ENTER, pEnter_));

	auto pElevetor_ = ofPtr<GElevator>(new GElevator(1.5));
	_GMap.insert(make_pair(NAME_MGR::G_ELEVATOR, pElevetor_));

	auto pJetpack_ = ofPtr<GJetpack>(new GJetpack(1.5));
	_GMap.insert(make_pair(NAME_MGR::G_JETPACK, pJetpack_));
}

//--------------------------------------------------------------
void ofApp::resetGiraffe()
{
	for(auto& Iter_ : _GMap)
	{
		Iter_.second->reset();
	}
}
#pragma endregion

