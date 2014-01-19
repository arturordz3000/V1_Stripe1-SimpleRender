#ifndef _CGAME_H_
#define _CGAME_H_

#include "../Game.h"
#include "../Graphics.h"

extern class CGame *Game;
extern CGraphics *Graphics;

class CGame
{
public:

	CGame();
	~CGame();

	int Run();
	void Exit();

private:
	
	CGraphics *m_pGraphics;

	bool m_bIsRunning;
};

#endif