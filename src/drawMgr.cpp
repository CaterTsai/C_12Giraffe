#include "drawMgr.h"

//--------------------------------------------------------------
void drawMgr::draw(stGiraffeP& param)
{
	DEGiraffe::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stSwingGiraffeP& param)
{
	DESwingGiraffe::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stLongGiraffeP& param)
{
	DELongGiraffe::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stThreeLevelFireworkP& param)
{
	DEThreeLevelFirework::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stElevatorP& param)
{
	DEElevator::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stJetpackP& param)
{
	DEJetpack::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stExclamationMarkP& param)
{
	DEExclamation::draw(param);
}

#pragma region Singleton
//--------------------------------------------------------------
drawMgr* drawMgr::pInstance = 0;
drawMgr* drawMgr::GetInstance()
{
	if(pInstance == 0)
	{
		pInstance = new drawMgr();
	}
	return pInstance;
}

//--------------------------------------------------------------
void drawMgr::Destroy()
{
	if(pInstance != 0)
	{
		delete pInstance;
	}
}
#pragma endregion

