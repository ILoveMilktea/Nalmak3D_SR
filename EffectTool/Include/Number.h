#pragma once
#include "Component.h"

class Text;
template <typename T>
class NALMAK_DLL Number :
	public Component
{
	struct Desc
	{
		T* targetValue = nullptr;
	};
public:
	Number(Desc* _desc);

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public:
	void SetTargetValue(T _value);
	T GetTargetValue();

	wstring PrintNumber();
	
private:
	Text* m_text;
	T* m_targetValue;

	T m_observeValue;
};

