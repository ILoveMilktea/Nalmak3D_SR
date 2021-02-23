#pragma once
#include "Component.h"
class PlayerInfoManager :
	public Component
{
public:
	struct Desc
	{
		int attack;
		int hp;
		int maxHp;
		float minSpeed = 1;
		float maxSpeed = 30;
		float speed = 5;
		float dirsenser = 0.5f;
	};
public:
	PlayerInfoManager(Desc* _Desc);
	virtual ~PlayerInfoManager();


public:
	// Component을(를) 통해 상속됨
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

};

