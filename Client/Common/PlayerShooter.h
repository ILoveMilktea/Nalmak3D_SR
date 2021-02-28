#pragma once
#include "Component.h"
class PlayerShooter :
	public Component
{
public:
	PlayerShooter();
	virtual ~PlayerShooter();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

	void SetEquipment(class PlayerItem* _equip);
private:
	class PlayerItem* m_useEquipment; //  shot ȣ��
};

