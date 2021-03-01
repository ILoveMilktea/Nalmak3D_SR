#pragma once
#include "Component.h"
class PlayerShooter :
	public Component
{
public:
	struct  Desc
	{

	};
public:
	PlayerShooter(Desc* _Desc);
	virtual ~PlayerShooter();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

	void SetEquipment(PARTS_NUM _weaponName);
private:
	class PlayerItem* m_useEquipment = nullptr; //  shot ȣ��
	bool	m_shooterFire;
private:
	class PlayerInfoManager* m_playerMgr;
	class ItemManager* m_ItemManager;

private:
	float m_shootTime;
	PARTS_NUM m_prevParts = PARTS_MAX;
};

