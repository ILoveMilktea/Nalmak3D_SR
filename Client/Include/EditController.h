#pragma once
#include "Component.h"
class EditController :
	public Component
{
public:
	struct Desc
	{

	};

public:
	EditController(Desc* _desc);

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

private:
	InputManager* m_input;
	bool m_editMode;
};

