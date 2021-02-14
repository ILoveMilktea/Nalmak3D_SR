#pragma once

#ifndef __EVENT_H__
#define __EVENT_H__

#include "EventHandler.h"


class NALMAK_DLL Event
{
public:
	void AddHandler(const EventHandler& _handler);
	void RemoveHandler(const EventHandler& _handler);
	void Release();
	void operator()();
	Event &operator+=(const EventHandler& _handler);
	Event &operator-=(const EventHandler& _handler);

private:
	vector<EventHandler*> m_handlers;
public:
	void NotifyHandlers();
	void DoEvent(size_t _num);
};



#endif // !__EVENT_H__
