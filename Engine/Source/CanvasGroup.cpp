#include "CanvasGroup.h"
#include "CanvasRenderer.h"

IMPLEMENT_SINGLETON(CanvasGroup)


CanvasGroup::CanvasGroup()
{
}


CanvasGroup::~CanvasGroup()
{
	Release();
}

void CanvasGroup::Initialize(_CANVAS_GROUP _count)
{
	m_groupLists.assign(_count, list<CanvasRenderer*>());
}

void CanvasGroup::Release()
{
	for (auto& group : m_groupLists)
	{
		group.clear();
	}
}

void CanvasGroup::SetGroupFade(_CANVAS_GROUP _group, float _fade)
{
	for (auto& iter : m_groupLists[_group])
	{
		iter->SetFade(_fade);
	}
}

void CanvasGroup::SetGroupInteractive(_CANVAS_GROUP _group, bool _value)
{
	for (auto& iter : m_groupLists[_group])
	{
		iter->SetInteractive(_value);
	}
}

void CanvasGroup::SetGroupBlockPicking(_CANVAS_GROUP _group, bool _value)
{
	for (auto& iter : m_groupLists[_group])
	{
		iter->SetBlockPicking(_value);
	}
}

void CanvasGroup::SetObjectActive(_CANVAS_GROUP _group, bool _value)
{
	for (auto& iter : m_groupLists[_group])
	{
		iter->GetGameObject()->SetActive(_value);
	}
}

void CanvasGroup::SetNonGroup(CanvasRenderer* _member)
{
	auto iter_begin = m_groupLists[_member->GetGroup()].begin();
	for (; iter_begin != m_groupLists[_member->GetGroup()].end(); ++iter_begin)
	{
		if (*iter_begin == _member)
		{
			iter_begin = m_groupLists[_member->GetGroup()].erase(iter_begin);
			break;
		}
	}

	m_groupLists[0].emplace_back(_member);
}

void CanvasGroup::AddGroupMember(CanvasRenderer* _member, _CANVAS_GROUP _group)
{
	m_groupLists[_group].emplace_back(_member);
}

void CanvasGroup::RemoveGroupMember(CanvasRenderer * _member, _CANVAS_GROUP _group)
{
	for (auto& member : m_groupLists[_group])
	{
		if (member == _member)
		{
			m_groupLists[_group].remove(member);
			return;
		}
	}
}

void CanvasGroup::ChangeGroup(CanvasRenderer * _member, _CANVAS_GROUP _groupToChange)
{
	auto iter_begin = m_groupLists[_member->GetGroup()].begin();
	for (; iter_begin != m_groupLists[_member->GetGroup()].end(); ++iter_begin)
	{
		if (*iter_begin == _member)
		{
			iter_begin = m_groupLists[_member->GetGroup()].erase(iter_begin);
			break;
		}
		//if (iter_begin == m_groupLists[_group].end())
		//	assert("List in Object null" && 0);
	}

	m_groupLists[_groupToChange].emplace_back(_member);
}

void CanvasGroup::AllOff()
{
	for (auto& group : m_groupLists)
	{
		for (auto& member : group)
		{
			member->GetGameObject()->SetActive(false);
		}
	}
}

void CanvasGroup::AllOn()
{
	for (auto& group : m_groupLists)
	{
		for (auto& member : group)
		{
			member->GetGameObject()->SetActive(true);
		}
	}
}

void CanvasGroup::GroupOn(_CANVAS_GROUP _group)
{
	for (auto& member : m_groupLists[_group])
	{
		member->GetGameObject()->SetActive(true);
	}
}

void CanvasGroup::GroupOff(_CANVAS_GROUP _group)
{
	for (auto& member : m_groupLists[_group])
	{
		member->GetGameObject()->SetActive(false);
	}
}

const list<CanvasRenderer*>& CanvasGroup::GetGroup(_CANVAS_GROUP _group)
{
	return m_groupLists[_group];
}

CanvasRenderer * CanvasGroup::Find(const wstring & _name)
{
	for (auto& group : m_groupLists)
	{
		for (auto& member : group)
		{
			if (member->GetGameObject()->GetName() == _name)
			{
				return member;
			}
		}
	}
	return nullptr;
}

CanvasRenderer * CanvasGroup::Find(_CANVAS_GROUP _group, const wstring & _name)
{
	for (auto& member : m_groupLists[_group])
	{
		if (member->GetGameObject()->GetName() == _name)
		{
			return member;
		}
	}
	return nullptr;
}

CanvasRenderer * CanvasGroup::FindFirstObjectbyTag(_CANVAS_GROUP _group)
{
	return m_groupLists[_group].front();;
}
