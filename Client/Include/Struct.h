#pragma once



typedef struct tagEnemyBullet
{

	tagEnemyBullet(
		int mindmg=0, int maxdmg=0, int fullRound=0, float reloadtime=0.f, 
		float fpm=0.f, float maxspd=0.f, float lookspd=0.f)
	{
		m_iDmg_Min = mindmg;
		m_iDmg_Max = maxdmg;

		m_fReload = reloadtime;

		m_iRound_Full = fullRound;
		m_iRound_Cur = m_iRound_Full;

		m_fFpm = fpm;

		m_fMaxSpd = maxspd;
		m_fLookSpd = lookspd;
		
	};

	int		m_iDmg_Min = 0;
	int		m_iDmg_Max = 0;

	int		m_iRound_Full = 0;
	int		m_iRound_Cur = 0;

	float	m_fReload = 0.f; //Time for Reloading

	float	m_fFpm = 0.f; //Fire per min

	float	m_fMaxSpd = 0.f;
	float	m_fLookSpd = 0.f; //for Only homing

}BULLET_STATUS;

typedef struct tagEnemy
{
	tagEnemy(
	int _iHp = 0, float _fMaxSpd = 0.f, float _fLookSpd = 0.f)
	{
		m_iFullHp = _iHp;
		m_iCurHp = m_iFullHp;

		m_fMaxSpd = _fMaxSpd;
		m_fCurSpd = 0.f;

		m_fLookSpd = _fLookSpd;
	};
	
	int		m_iFullHp;
	int		m_iCurHp;

	float	m_fMaxSpd;
	float	m_fCurSpd;
	float	m_fLookSpd;

	


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
		modelName = other.modelName;
	};

	tagItemInfo(const wstring& _itemName, float& _weaponSpeed, float& _delay, int& _weaponAttak, int& _weaponAmmo, int& _gold) :
		 weaponSpeed(_weaponSpeed), delay(_delay) , weaponAttak(_weaponAttak), weaponAmmo(_weaponAmmo), costGold(_gold)
	{
		//strcpy X
		itemName = _itemName;
	};

	wstring itemName;
	float	 weaponSpeed; //Bullet Move Spd
	float	 delay; //¿¬»ç·Â
	int	 weaponAttak;
	int  weaponAmmo; //Round
	int  costGold;

	wstring modelName;
}ITEMINFO;
