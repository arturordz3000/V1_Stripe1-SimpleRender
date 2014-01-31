#include "../Game.h"

void CStateMainGame::OnLoad()
{
	CActorPlane *cPlane = new CActorPlane();
	ActorMgr->LoadActor(cPlane);
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