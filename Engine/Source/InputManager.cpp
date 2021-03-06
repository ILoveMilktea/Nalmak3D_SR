#include "..\Include\InputManager.h"
#include "DeviceManager.h"
#include "RenderManager.h"
IMPLEMENT_SINGLETON(InputManager)

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
	Release();
}

void InputManager::Initialize()
{
	/*for (UINT16 i = 0; i < KEY_STATE::KEY_STATE_MAX; ++i)
	{
	m_isButtonDown.emplace_back(pair<i,)
	m_bButtonUp[i] = false;
	m_bButtonDown[i] = false;
	m_bButtonPress[i] = false;
	}*/
}

void InputManager::Update()
{
	ProcessKeyState();
	ProcessMouseScreenPosition();

}

void InputManager::Release()
{
}

void InputManager::ProcessMouseScreenPosition()
{
	m_prevMouseScreenPosition = m_mouseScreenPosition;

	POINT point = {};
	GetCursorPos(&point);
	ScreenToClient(DeviceManager::GetInstance()->GetHWND(), &point);
	m_mouseScreenPosition.x = (float)(point.x);
	m_mouseScreenPosition.y = (float)(point.y);
}


void InputManager::ProcessKeyState()
{
	SHORT res[KEY_STATE::KEY_STATE_MAX] = {};

	for (int i = 0; i < KEY_STATE_MAX; ++i)
	{
		switch (i)
		{
		case KEY_STATE_LEFT_MOUSE:
			res[KEY_STATE_LEFT_MOUSE] = GetAsyncKeyState(VK_LBUTTON);
			break;
		case KEY_STATE_RIGHT_MOUSE:
			res[KEY_STATE_RIGHT_MOUSE] = GetAsyncKeyState(VK_RBUTTON);
			break;
		case KEY_STATE_WHEEL_MOUSE:
			res[KEY_STATE_WHEEL_MOUSE] = GetAsyncKeyState(VK_MBUTTON);
			break;
		case KEY_STATE_LEFT_ARROW:
			res[KEY_STATE_LEFT_ARROW] = GetAsyncKeyState(VK_LEFT);
			break;
		case KEY_STATE_RIGHT_ARROW:
			res[KEY_STATE_RIGHT_ARROW] = GetAsyncKeyState(VK_RIGHT);
			break;
		case KEY_STATE_DOWN_ARROW:
			res[KEY_STATE_DOWN_ARROW] = GetAsyncKeyState(VK_DOWN);
			break;
		case KEY_STATE_UP_ARROW:
			res[KEY_STATE_UP_ARROW] = GetAsyncKeyState(VK_UP);
			break;
		case KEY_STATE_SHIFT:
			res[KEY_STATE_SHIFT] = GetAsyncKeyState(VK_SHIFT);
			break;
		case KEY_STATE_ALT:
			res[KEY_STATE_ALT] = GetAsyncKeyState(VK_MENU);
			break;
		case KEY_STATE_TAB:
			res[KEY_STATE_TAB] = GetAsyncKeyState(VK_TAB);
			break;
		case KEY_STATE_SPACE:
			res[KEY_STATE_SPACE] = GetAsyncKeyState(VK_SPACE);
			break;
		case KEY_STATE_ESC:
			res[KEY_STATE_ESC] = GetAsyncKeyState(VK_ESCAPE);
			break;
		case KEY_STATE_ENTER:
			res[KEY_STATE_ENTER] = GetAsyncKeyState(VK_RETURN);
			break;
		case KEY_STATE_W:
			res[KEY_STATE_W] = GetAsyncKeyState('W');
			break;
		case KEY_STATE_A:
			res[KEY_STATE_A] = GetAsyncKeyState('A');
			break;
		case KEY_STATE_S:
			res[KEY_STATE_S] = GetAsyncKeyState('S');
			break;
		case KEY_STATE_D:
			res[KEY_STATE_D] = GetAsyncKeyState('D');
			break;
		case KEY_STATE_F:
			res[KEY_STATE_F] = GetAsyncKeyState('F');
			break;
		case KEY_STATE_E:
			res[KEY_STATE_E] = GetAsyncKeyState('E');
			break;
		case KEY_STATE_O:
			res[KEY_STATE_O] = GetAsyncKeyState('O');
			break;
		case KEY_STATE_K:
			res[KEY_STATE_K] = GetAsyncKeyState('K');
			break;
		case KEY_STATE_L:
			res[KEY_STATE_L] = GetAsyncKeyState('L');
			break;
		case KEY_STATE_Q:
			res[KEY_STATE_Q] = GetAsyncKeyState('Q');
			break;
		case KEY_STATE_P:
			res[KEY_STATE_P] = GetAsyncKeyState('P');
			break;
		case KEY_STATE_C:
			res[KEY_STATE_C] = GetAsyncKeyState('C');
			break;
		case KEY_STATE_R:
			res[KEY_STATE_R] = GetAsyncKeyState('R');
			break;
		case KEY_STATE_X:
			res[KEY_STATE_X] = GetAsyncKeyState('X');
			break;
		case KEY_STATE_F1:
			res[KEY_STATE_F1] = GetAsyncKeyState(VK_F1);
			break;
		case KEY_STATE_F2:
			res[KEY_STATE_F2] = GetAsyncKeyState(VK_F2);
			break;
		case KEY_STATE_F3:
			res[KEY_STATE_F3] = GetAsyncKeyState(VK_F3);
			break;
		case KEY_STATE_F4:
			res[KEY_STATE_F4] = GetAsyncKeyState(VK_F4);
			break;
		case KEY_STATE_F5:
			res[KEY_STATE_F5] = GetAsyncKeyState(VK_F5);
			break;
		case KEY_STATE_F6:
			res[KEY_STATE_F6] = GetAsyncKeyState(VK_F6);
			break;
		case KEY_STATE_F7:
			res[KEY_STATE_F7] = GetAsyncKeyState(VK_F7);
			break;
		case KEY_STATE_F8:
			res[KEY_STATE_F8] = GetAsyncKeyState(VK_F8);
			break;
		case KEY_STATE_F9:
			res[KEY_STATE_F9] = GetAsyncKeyState(VK_F9);
			break;
		case KEY_STATE_1:
			res[KEY_STATE_1] = GetAsyncKeyState('1');
			break;
		case KEY_STATE_2:
			res[KEY_STATE_2] = GetAsyncKeyState('2');
			break;
		case KEY_STATE_3:
			res[KEY_STATE_3] = GetAsyncKeyState('3');
			break;
		case KEY_STATE_0:
			res[KEY_STATE_0] = GetAsyncKeyState('0');
			break;

		default:
			break;
		}
	}

	for (UINT16 i = 0; i < KEY_STATE::KEY_STATE_MAX; ++i)
	{
		m_bButtonUp[i] = false;
		m_bButtonDown[i] = false;

		if (res[i] & 0X0001) // button Down
		{
			m_bButtonDown[i] = true;
		}
		else if (res[i] & 0X8000) // button Press
		{
			m_bButtonDown[i] = false;
			m_bButtonPress[i] = true;
		}
		else if (m_bButtonPress[i] == true)
		{
			m_bButtonPress[i] = false;
			m_bButtonUp[i] = true;
		}
	}
}
