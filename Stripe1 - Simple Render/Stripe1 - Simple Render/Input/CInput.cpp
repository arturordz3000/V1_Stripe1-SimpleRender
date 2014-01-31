#include "../Game.h"

CInput::CInput()
{
	Input = this;
}

CInput::~CInput()
{
	Input = NULL;
}

void CInput::ResetKeyboard()
{
	this->m_uiPressedKey = 0;
}

void CInput::SetPressedKey(WPARAM key)
{
	this->m_uiPressedKey = key;
}

bool CInput::IsKeyDown(WPARAM key)
{
	return this->m_uiPressedKey == key;
}