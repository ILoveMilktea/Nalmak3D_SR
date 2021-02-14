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
	m_mouseScreenPosition.x = (float)(point.x - RenderManager::GetInstance()->GetWindowWidth() * 0.5f);
	m_mouseScreenPosition.y = (float)(RenderManager::GetInstance()->GetWindowHeight() * 0.5f - point.y);
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
