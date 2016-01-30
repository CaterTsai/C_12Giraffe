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
	_p.drawPos.set(ofGetWidth()/2, ofGetHeight()/2);
	_p.fdegree = 90;
	_p.bflip = true;
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
	//ofLine(ofVec2f(ofGetWidth()/2, 0), ofVec2f(ofGetWidth()/2, ofGetHeight()));
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
	case 't':
		{
			_GMap[NAME_MGR::G_DROP]->add(0, 0);
		}
		break;
	case 'y':
		{
			_GMap[NAME_MGR::G_TRAVERSE]->add(0, 0);
		}
		break;
	case 'u':
		{
			_GMap[NAME_MGR::G_MEGA]->add(0, 0);
		}
		break;
	case 'i':
		{
			_GMap[NAME_MGR::G_MARIO]->add(0, 0);
		}
		break;
	case 'o':
		{
			_GMap[NAME_MGR::G_KIRBY]->add(0, 0);
		}
		break;
	case 'p':
		{
			_GMap[NAME_MGR::G_CACTUS]->add(0, 0);
		}
		break;
	case '[':
		{
			_GMap[NAME_MGR::G_POKEMON]->add(0, 0);
		}
		break;
	case ']':
		{
			_GMap[NAME_MGR::G_PACMAN]->add(0, 0);
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

	auto pDrop_ = ofPtr<GDrop>(new GDrop(1.5));
	_GMap.insert(make_pair(NAME_MGR::G_DROP, pDrop_));

	auto pTraverse_ = ofPtr<GTraverse>(new GTraverse(1.5));
	_GMap.insert(make_pair(NAME_MGR::G_TRAVERSE, pTraverse_));

	auto pMega_ = ofPtr<GMega>(new GMega(1.5));
	_GMap.insert(make_pair(NAME_MGR::G_MEGA, pMega_));

	auto pMario_ = ofPtr<GMario>(new GMario(1.5));
	_GMap.insert(make_pair(NAME_MGR::G_MARIO, pMario_));

	auto pKirby_ = ofPtr<GKirby>(new GKirby(1.5));
	_GMap.insert(make_pair(NAME_MGR::G_KIRBY, pKirby_));

	auto pCactus_ = ofPtr<GCactus>(new GCactus(1.5));
	_GMap.insert(make_pair(NAME_MGR::G_CACTUS, pCactus_));

	auto pPokemon_ = ofPtr<GPokemon>(new GPokemon(1.5));
	_GMap.insert(make_pair(NAME_MGR::G_POKEMON, pPokemon_));

	auto pPACMan_ = ofPtr<GPACMan>(new GPACMan(3.0));
	_GMap.insert(make_pair(NAME_MGR::G_PACMAN, pPACMan_));
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