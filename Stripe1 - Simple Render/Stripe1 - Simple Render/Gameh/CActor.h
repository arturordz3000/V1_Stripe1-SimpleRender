#ifndef _CACTOR_H_
#define _CACTOR_H_

#include "../Game.h"
#include "../Managersh/CResourceMgr.h"

extern CResourceMgr *ResourceMgr;

class CActor
{
public:

	CActor();
	~CActor();

	virtual void OnLoad();
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void SetResourcesId(unsigned int uiResourcesId) { this->m_pResources = ResourceMgr->GetResourcesById(uiResourcesId); }

protected:
	
	CResources *m_pResources;

	XMFLOAT3 vTranslation;
	XMFLOAT3 vRotation;
	XMFLOAT3 vScale;
	XMMATRIX mxWorld;
};

#endif