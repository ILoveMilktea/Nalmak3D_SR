#include "stdafx.h"
#include "..\Include\Player_EmpMissile.h"
#include "Player_EmpMove.h"

/*
1. Create ItemInfo and This Class via itemManager (and then, emplace_back to ItemManager class's 'm_mapShopItem')
2. This Class has ItemInfo and Just only Shoot Start system. (Not Real Bullet System)
3. if u wanna Real Bullet system, plz make Component Class.
4. then, Buy the Item at ItemManager, and
5. Equip the item at PlayerInfoManager 

5. and then, 'PlayerShooter' Class take Shoot
6. 
*/

Player_EmpMissile::Player_EmpMissile(const ITEMINFO & _info)
	:PlayerItem(_info)
{
	/*
	info.itemName = L"Emp";
	info.costGold = 0;
	info.delay = 5.f;
	info.weaponSpeed = 100.f;
	*/
}

Player_EmpMissile::~Player_EmpMissile()
{
}

void Player_EmpMissile::ItemShot()
{
	/* Real Shoot
	Add Component ex)Move */

	//Emp->GetTransform()->position = Emp->GetTransform()->GetWorldPosition();
	Emp->GetTransform()->rotation = Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER)->GetTransform()->rotation;
	Emp->GetTransform()->DeleteParent();

	Player_EmpMove::Desc Move_desc;
	Move_desc.fmaxSpd = m_itemInfo.weaponSpeed;
	Emp->AddComponent<Player_EmpMove>(&Move_desc);
	
	Emp = nullptr;

}

void Player_EmpMissile::CreateBullet()
{
	/* Ready Shoot
	Create bullet,
	Add Mesh, Collider */
	
	if (Emp)
	{
		return;
	}

	Emp = INSTANTIATE(OBJECT_TAG_BULLET_PLAYER, L"Emp_Missile");
	Emp->SetScale(Vector3(1.f, 1.f, 2.f));
	Emp->SetParents(Core::GetInstance()->FindFirstObject(OBJECT_TAG_PLAYER));
	Emp->SetPosition(0.f, -1.f, 0.f);

	VIBufferRenderer::Desc Emp_render;
	Emp_render.meshName = L"box";
	Emp_render.mtrlName = L"default";
	Emp->AddComponent<VIBufferRenderer>(&Emp_render);

	SphereCollider::Desc Emp_col;
	Emp_col.radius = 1.f;
	//Emp_col.offset = Vector3(0.f, 0.f, 1.f);
	Emp_col.collisionLayer = COLLISION_LAYER_BULLET_PLAYER;
	Emp->AddComponent<SphereCollider>(&Emp_col);
	

}

void Player_EmpMissile::DeleteBullet()
{

}

