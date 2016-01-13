#pragma once

#include "constParameter.h"
#include "drawMgr.h"
#include "12Giraffe.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
		
private:
	float _fMainTimer;
	//stJetpackP	_p;

#pragma region Giraffe12
//--------------------------------------
//12Giraffe
//--------------------------------------
public:
	void initialGiraffe();
private:
	bool												_bGSetup;
	map<string, ofPtr<IGBasic>>	_GMap;
#pragma endregion
};
