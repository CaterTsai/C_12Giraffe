#include "ofApp.h"

#pragma region Basic Method
//--------------------------------------------------------------
void ofApp::setup()
{
	ofEnableSmoothing();
	ofBackground(255);

	drawMgr::GetInstance();

	//Setup giraffe
	initialGiraffe();

	//_p.drawPos.set(ofGetWidth()/2, ofGetHeight()/2);



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

	//Debug
	//drawMgr::GetInstance()->draw(_p);
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
#pragma endregion

