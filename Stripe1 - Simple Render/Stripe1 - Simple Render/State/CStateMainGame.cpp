#include "../Game.h"

void CStateMainGame::OnLoad()
{

}

CStateMainGame::CStateMainGame() : CState()
{

}

CStateMainGame::~CStateMainGame()
{

}

void CStateMainGame::DoFrame()
{
	ActorMgr->UpdateActors();
	ActorMgr->DrawActors();
}