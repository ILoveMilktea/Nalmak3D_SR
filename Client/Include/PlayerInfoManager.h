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
		int gold = 2000;
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
	const int& GetGold() { return m_gold; }

	// temporary members
	const float& GetTimeLimit() { return m_timelimit; }
	const float& GetScore() { return m_score; }
	GameObject* GetPlayer() { return m_player; }
	map<wstring, vector<wstring>>& GetInven() { return m_haveItemList; }
	const wstring* GetWeaponArray() { return m_currentlyWeapon; }

	const wstring& GetWeapon(PARTS_NUM _partsNumn) { return m_currentlyWeapon[_partsNumn]; }
	const wstring& GetSkill(PARTS_NUM _partsNumn) { return m_currentlySkill[_partsNumn]; }

public: //using
	bool EquipItem(PARTS_NUM eID , const wstring& _itemtype  ,const wstring& _equipItemName);
	void MinGold(int _value);



private:
	static PlayerInfoManager* m_instance;
private:
	int m_attack = 0;
	int m_hp = 0;
	int m_maxHp = 0;
	int m_gold = 0;

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

private: // 이중stl쓰기 
	// type, vector<itemname>
	map<wstring, vector<wstring>> m_haveItemList;
private:
	wstring m_currentlySkill[PARTS_NUM::PARTS_MAX] = {};
	wstring  m_currentlyWeapon[PARTS_NUM::PARTS_MAX] = {};


};
