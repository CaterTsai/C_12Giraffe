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
void drawMgr::draw(stOpenGiraffeP& param)
{
	DEOpenGiraffe::draw(param);
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
void drawMgr::draw(stBoxP& param)
{
	DEBox::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stJetpackP& param)
{
	DEJetpack::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stPipeP& param)
{
	DEPipe::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stFireFlowerP& param)
{
	DEFireFlower::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stStarP& param)
{
	DEStar::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stCactusP& param)
{
	DECacuts::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stPokeBallP& param)
{
	DEPokeBall::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stPACManP& param)
{
	DEPACMan::draw(param);
}

//--------------------------------------------------------------
void drawMgr::draw(stGhostP& param)
{
	DEGhost::draw(param);
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

