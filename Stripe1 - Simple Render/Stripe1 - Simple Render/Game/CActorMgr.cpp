#include "../Game.h"

CActorMgr::CActorMgr()
{
	// Damos acceso global a esta instancia
	ActorMgr = this;
}

CActorMgr::~CActorMgr()
{

}

void CActorMgr::LoadActor(CActor *lActor)
{
	this->m_lActors.push_back(lActor);
}

void CActorMgr::UnloadActors()
{
	this->m_lActors.clear();
}

void CActorMgr::UpdateActors()
{
	std::list<CActor*>::iterator iActor;
	for (iActor = this-> m_lActors.begin(); iActor != this-> m_lActors.end(); iActor++) {
		(*iActor)->Update();
	}
}

void CActorMgr::DrawActors()
{
	std::list<CActor*>::iterator iActor;
	for (iActor = this->m_lActors.begin(); iActor != this->m_lActors.end(); iActor++) {
		(*iActor)->Draw();
	}
}