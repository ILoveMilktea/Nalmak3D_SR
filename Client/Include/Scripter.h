#pragma once
#ifndef __SCRIPTER_H__
#define __SCRIPTER_H__

#include "Component.h"

class Scripter :
	public Component
{
public:

	struct Desc
	{
		Text* title = nullptr;
		Text* script = nullptr;

		vector<Dialogue> startDialogue;
	};

public:
	Scripter(Desc* _desc);

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release();

	void ScriptOn();
	void ScriptOff();


public:
	void SetDialogue(vector<Dialogue> _titleList);
	
	bool LoadNextScript();
	void LoadScriptByIndex(int _index);
	
private:
	Text* m_title;
	Text* m_script;

	vector<Dialogue> m_dialogueList;
	StateControl* m_state;

	int m_dialogueIndex;

private:	/* for typing section */
	bool m_typingMode;

	int m_scriptLength;
	float m_typingTime;
	float m_typingTerm;
};


#endif // !__SCRIPTER_H__

