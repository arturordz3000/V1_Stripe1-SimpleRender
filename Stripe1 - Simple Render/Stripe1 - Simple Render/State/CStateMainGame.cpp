#include "../Game.h"

void CStateMainGame::OnLoad()
{
	CActorTexturedCube *cCube = new CActorTexturedCube();
	//CActorPlane *cCube = new CActorPlane();
	ActorMgr->LoadActor(cCube);
}

CStateMainGame::CStateMainGame() : CState()
{
	this->OnLoad();
}

CStateMainGame::~CStateMainGame()
{

}

void CStateMainGame::DoFrame()
{	
	ActorMgr->UpdateActors();
	ActorMgr->DrawActors();	
	Input->ResetKeyboard();
}