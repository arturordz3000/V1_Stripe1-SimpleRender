#ifndef _CINPUT_H_
#define _CINPUT_H_

class CInput
{
public:
	CInput();
	~CInput();

	void SetPressedKey(WPARAM key);
	void ResetKeyboard();
	bool IsKeyDown(WPARAM key);

private:
	WPARAM m_uiPressedKey;
};

#endif
