#pragma once
#include "Component.h"
class PlayerInfoManager :
	public Component
{
public:
	struct Desc
	{
		int attack = 30;
		int hp = 100;
		int maxHp = 100;
		float minSpeed = 1;
		float maxSpeed = 30;
		float speed = 5;
		float dirsenser = 0.5f;
	};
public:
	PlayerInfoManager(Desc* _Desc);
	virtual ~PlayerInfoManager();


public:
	virtual void Initialize() override;
	virtual void Update() override;

public:
	static PlayerInfoManager* GetInstance();
	static void DeleteInstance();
public:
	void SetDamage(const int& _value);
	void SetHp(const int& _value);
	void SetAttack(const int& _value);
	void SetFullHp(const int& _value);
	void SetSpeed(const float& _value);
	void AddSpeed(float _value);
	void SetDirSeneser(const float& _value);
	void SetRollAngle(const float& _value);
	void SetMinSpeed(const float& _value);
	void SetMaxSpeed(const float& _value);

	void SetTimeLimit(const float& _value);
	void SetScore(const float& _value);
	void SetPlayer(GameObject* _player);

public:
	const int& GetHp() const;
	const int& GetAttack() const;
	const int& GetMaxHp() const;
	const float& GetSpeed() const;
	const float& GetDirSenser() const;
	Vector3& GetAddRot() { return  m_addedRot;  }
	const float& GetRollAngle() {return m_rollAngle;}
	const float& GetMinSpeed() { return m_minSpeed; }
	const float& GetMaxSpeed() { return m_maxSpeed; }
	ItemDesc** GetItemDescInfoArray() {return m_playerItem;}
	//const ItemDesc** GetItemDescInfoArray() {return m_playerItem;}
	
	// temporary members
	const float& GetTimeLimit() { return m_timelimit; }
	const float& GetScore() { return m_score; }
	GameObject* GetPlayer() { return m_player; }
	
public:
	void EquipWepon(PARTS_NUM _enumID ,ItemDesc* _desc);

private:
	static PlayerInfoManager* m_instance;
private:
	int m_attack = 0;
	int m_hp = 0;
	int m_maxHp = 0;

	float m_speed = 0;
	float m_rollAngle;
	float m_dirsensor = 0;
	float m_minSpeed = 0;
	float	m_maxSpeed = 0;
	Vector3 m_addedRot = {};

	// temporary members
	float m_timelimit = 0.f;
	float m_score = 0.f;
	GameObject* m_player;


private:
	ItemDesc* m_playerItem[PARTS_NUM::PARTS_MAX];

};
