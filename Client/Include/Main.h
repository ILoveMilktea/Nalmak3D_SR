#pragma once
#ifndef __MAIN_H__
#define __MAIN_H__

class Main
{
public:
	Main();
	~Main();
public:
	HRESULT Initialize();
	void Update();
	void Release();
};

#endif

