#include "../Game.h"

CResources::CResources()
{

}

CResources::~CResources()
{

}

CResourceMgr::CResourceMgr()
{
	ResourceMgr = this;
	iResourcesCount = 0;
}

CResourceMgr::~CResourceMgr()
{
	ResourceMgr = NULL;
}

void CResourceMgr::AddResources(CResources *pResources, unsigned int &iResourcesId)
{
	iResourcesId = iResourcesCount;
	lResources.push_back(pResources);
	iResourcesCount++;	
}