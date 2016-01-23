#pragma once

#include "constParameter.h"
#include "drawMgr.h"
#include "12Giraffe.h"
#include "TGiraffe.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
		
private:
	float _fMainTimer;
	stCactusP	_p;

#pragma region Giraffe12
//--------------------------------------
//12Giraffe
//--------------------------------------
public:
	void initialGiraffe();
	void resetGiraffe();
private:
	bool												_bGSetup;
	map<string, ofPtr<IGBasic>>	_GMap;
#pragma endregion

#pragma region TGiraffe
private:
	TGiraffe	_tGiraffe;
#pragma endregion
};
