#include "..\Include\Event.h"
#include "Nalmak_Include.h"



void Event::AddHandler(const EventHandler& _handler)
{
	m_handlers.emplace_back(new EventHandler{ _handler });
}

void Event::RemoveHandler(const EventHandler& _handler)
{
	for (vector<EventHandler*>::iterator to_remove = m_handlers.begin();
		to_remove != m_handlers.end();
		++to_remove)
	{
		if (*(*to_remove) == _handler)
		{
			m_handlers.erase(to_remove);
			break;
		}
	}
}

void Event::Release()
{
	for (auto& handler : m_handlers)
		SAFE_DELETE(handler);

	m_handlers.clear();
}

void Event::operator()()
{
	NotifyHandlers();
}

Event &Event::operator+=(const EventHandler& _handler)
{
	AddHandler(_handler);

	return *this;
}

Event &Event::operator-=(const EventHandler& _handler)
{
	RemoveHandler(_handler);

	return *this;
}

void Event::NotifyHandlers()
{
	for (vector<EventHandler*>::iterator func = m_handlers.begin();
		func != m_handlers.end();
		++func)
	{
		if (*func != nullptr)
			(*(*func))();
	}
}

void Event::DoEvent(size_t _num)
{
	(*m_handlers[_num])();
}
