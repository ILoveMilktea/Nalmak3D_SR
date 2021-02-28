#pragma once



typedef struct tagBullet
{
	int m_iMinDmg;
	int m_iMaxDmg;

	float m_fMaxSpd;
	float m_fCurSpd;

}BULETT_STATUS;

typedef struct tagEnemy
{
	int		m_iFullHp;
	int		m_iCurHp;

	float	m_fMaxSpd;
	float	m_fCurSpd;
	float	m_fLookSpd;

	ENEMY_STATE	m_eCurState;

	/* for machine gun*/
	int		m_iDmg_Gun;
	float	m_fFpm_Gun; //Fire per minute ������
	int		m_iFullRound_Gun;
	int		m_iCurRound_Gun;
	float	m_fReloadTime_Gun; //time to Reloaing

	/* for straight missile */
	int		m_iDmg_Missile;
	int		m_iMinDmg_Missile;
	float	m_fFpm_Missile;
	int		m_iFullRound_Missile;
	int		m_iCurRound_Missile;
	float	m_fReloadTime_Missile;

	/* for homing missile */
	int		m_iDmg_Homing;
	float	m_fFpm_Homing;
	int		m_iFullRound_Homing;
	int		m_iCurRound_Homing;
	float	m_fReloadTime_Homing;




}ENEMY_STATUS;


typedef struct tagItemInfo
{
	tagItemInfo() {};
	tagItemInfo(const tagItemInfo& other) {
		//itemtype = other.itemtype;
		costGold = other.costGold;
		itemName = other.itemName;
		weaponSpeed = other.weaponSpeed;
		delay = other.delay;
		weaponAttak = other.weaponAttak;
		weaponAmmo = other.weaponAmmo;
	};

	tagItemInfo(const wstring& _itemName, float& _weaponSpeed, float& _delay, int& _weaponAttak, int& _weaponAmmo, int& _gold) :
		 weaponSpeed(_weaponSpeed), delay(_delay) , weaponAttak(_weaponAttak), weaponAmmo(_weaponAmmo), costGold(_gold)
	{
		//strcpy X
		itemName = _itemName;
	};

	wstring itemName;
	float	 weaponSpeed;
	float	 delay;
	int	 weaponAttak;
	int  weaponAmmo;
	int  costGold;

}ITEMINFO;
