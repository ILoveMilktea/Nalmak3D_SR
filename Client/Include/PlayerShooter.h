#pragma once
#include "Component.h"
class PlayerShooter :
	public Component
{
public:
	PlayerShooter();
	virtual ~PlayerShooter();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

	void SetEquipment(class PlayerItem* _equip);
private:
	class PlayerItem* m_useEquipment; //  shot 호출
};

