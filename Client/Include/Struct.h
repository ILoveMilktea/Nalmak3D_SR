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
