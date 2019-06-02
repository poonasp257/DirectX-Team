#ifndef _INPUT_H_
#define _INPUT_H_

enum class KeyCode {
	W, A, S, D,
	Escape, F1, F2
};

class Input
{
public:
	Input();
	Input(const Input&);
	~Input();
	
	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();
	
	bool GetKey(KeyCode key);
	bool GetKeyDown(KeyCode key);
	bool GetKeyUp(KeyCode key);

	void GetMouseLocation(int&, int&);
	void GetMouseDeltaPosition(int&, int&);

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();
private:
	IDirectInput8					   *m_directInput;
	IDirectInputDevice8				   *m_keyboard;
	IDirectInputDevice8				   *m_mouse;
	DIMOUSESTATE						m_mouseState;
	map<KeyCode, unsigned char>			m_keyState;
	unsigned char						m_keyboardState[256];
	unsigned char						m_pressedKeys[256];
	int									m_screenWidth, m_screenHeight;
	int									m_mouseX, m_mouseY;

};
#endif