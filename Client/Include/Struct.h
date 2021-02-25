#pragma once

typedef struct Desc
{
	Desc() {};
	Desc(const Desc& other) {
		itemtype = other.itemtype;
		weaponSpeed = other.weaponSpeed;
		delay = other.delay;
		weaponAttak = other.weaponAttak;
		weaponAmmo = other.weaponAmmo;
	};

	Desc(ITEMTYPE & _itemType, float& _weaponSpeed, float& _delay, int& _weaponAttak, int& _weaponAmmo) :
		itemtype(_itemType), weaponSpeed(_weaponSpeed), delay(_delay) , weaponAttak(_weaponAttak), weaponAmmo(_weaponAmmo)
	{
		
	};

	ITEMTYPE itemtype;
	float	 weaponSpeed;
	float	 delay;
	int	 weaponAttak;
	int  weaponAmmo;

}ItemDesc;