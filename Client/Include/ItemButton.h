#pragma once
#ifndef __ITEMBUTTON_H__
#define __ITEMBUTTON_H__

#include "Button.h"
class ItemButton :
	public Button
{
public:
	struct Desc
	{
		Button::Desc desc_button = Button::Desc();
	};
public:
	ItemButton(Desc* _desc);

	void SetPartsNumber(PARTS_NUM _num) { m_partsNumber = _num; }
	const PARTS_NUM& GetPartsNumber() { return m_partsNumber; }

private:
	PARTS_NUM m_partsNumber;
};


#endif // !__ITEMBUTTON_H__
