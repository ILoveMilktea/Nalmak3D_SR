#include "..\Include\Number.h"
#include "Text.h"

Number::Number(Desc * _desc)
	:Text(&_desc->text_desc)
{
	m_printType = _desc->printType;
	m_curValue = _desc->defaultValue;
}


void Number::UpdateValue(SetFloatFunc _setValueFunc, GetFloatFunc _getValueFunc)
{
	float targetValue = 0.f;
	_setValueFunc(&targetValue, _getValueFunc);

	if (m_curValue != targetValue)
	{
		m_curValue = targetValue;

		switch (m_printType)
		{
		case Number::NUMBER:
			PrintNumber();
			break;
		case Number::TIME_H_M_S:
			PrintTime_H_M_S();
			break;
		case Number::TIME_M:
			break;
		case Number::TIME_M_S_MS:
			PrintTime_M_S_MS();
			break;
		default:
			break;
		}
	}
}

void Number::PrintNumber()
{
	int ivalue = (int)m_curValue;
	SetText(to_wstring(ivalue));
}

void Number::PrintTime_H_M_S()
{
	int time = (int)m_curValue;

	int secondValue = time % 60;
	time /= 60;
	int minuteValue = time % 60;
	time /= 24;
	int hourValue = time;

	wstring hour	= to_wstring(hourValue);
	wstring minute	= to_wstring(minuteValue);
	wstring second	= to_wstring(secondValue);

	wstring timeText = hour + L":" + minute + L":" + second;
	SetText(timeText);
}

void Number::PrintTime_M_S_MS()
{
	int time = (int)(m_curValue * 100.f);

	int millisecondValue = time % 100;
	time /= 100;
	int secondValue = time % 60;
	time /= 60;
	int minuteValue = time % 60;

	wstring minute = to_wstring(minuteValue);
	wstring second = to_wstring(secondValue);
	wstring millisecond = to_wstring(millisecondValue);

	wstring timeText = minute + L":" + second + L":" + millisecond;
	SetText(timeText);
}
