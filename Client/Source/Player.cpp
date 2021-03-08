#include "stdafx.h"
#include "..\Include\Player.h"
#include "PlayerInfoManager.h"

Player::Player(Desc * _desc)
{

}

Player::~Player()
{

}

void Player::Initialize()
{

}

void Player::Update()
{

}

void Player::Release()
{
	//m_gameObject = nullptr;
	PlayerInfoManager::GetInstance()->Player_Release();
}

void Player::OnTriggerEnter(Collisions & _collision)
{
	for(auto& obj : _collision)
	{
		if (obj.GetGameObject()->GetTag() == OBJECT_TAG_BULLET_ENEMY)
		{
			
		
		}
	}
}

void Player::OnTriggerStay(Collisions & _collision)
{

}

void Player::OnTriggerExit(Collisions & _collision)
{

}



