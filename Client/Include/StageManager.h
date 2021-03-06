#pragma once
#include "Component.h"
class StageManager :
	public Component
{
private:
	static StageManager* m_instance;
public:
	static StageManager* GetInstance();
	static void DeleteInstance();

public:
	struct Desc
	{

	};
public:
	StageManager(Desc* _desc);
	~StageManager();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public: /* Get */
	template <class T>
	float Get_StageTime(const wstring& _name) const
	{
		return m_stateControl->GetState<T>(_name)->Get_Time();
	};
	
	template <class T>
	float Get_StageScore(const wstring& _name) const
	{
		return m_stateControl->GetState<T>(_name)->Get_Score();
	};

	float Get_DogTime() const;
	float Get_DogScore()const;

	float Get_EvasionTime()const;
	float Get_EvasionScore()const;

	float Get_BossTime()const;
	float Get_BossSocre()const;



public: /* Set */
	template <class T>
	float Set_StageScore(const wstring& _name, float _score) const
	{
		return m_stateControl->GetState<T>(_name)->Set_Score(_score);
	};

	template <class T>
	float Add_StageScore(const wstring& _name, float _score) const
	{
		return m_stateControl->GetState<T>(_name)->Add_Score(_score);
	};

	void Set_DogScore(float _score);
	void Add_DogScore(float _score);

	void Set_EvasionScore(float _score);
	void Add_EvasionScore(float _score);

	void Set_BossScore(float _score);
	void Add_BossScore(float _score);



public:
	void ToTutorial();
	void ToDog();
	void ToEvasion();
	void ToBoss();
	void ToScene(const wstring& _sceneName);

private:
	StateControl*	m_stateControl;
	
	

};

