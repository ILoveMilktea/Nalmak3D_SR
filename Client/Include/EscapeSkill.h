#pragma once
#include "PlayerItem.h"
class EscapeSkill :
	public PlayerItem
{
public:
	EscapeSkill(const ITEMINFO& copy);
	virtual ~EscapeSkill();

	// PlayerItem��(��) ���� ��ӵ�
	virtual void ItemShot() override;
	virtual void CreateBullet() override;
	virtual void DeleteBullet() override;

	// PlayerItem��(��) ���� ��ӵ�
};

