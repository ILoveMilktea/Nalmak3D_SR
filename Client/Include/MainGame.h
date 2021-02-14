#pragma once

class Core;
class MainGame
{
public:
	MainGame();
	~MainGame();
private:
	void ApplicationSetting();
	void SystemSetting();
	void ReadyResource();
	void ReadyPrototype();
	void InstantiateDefault();
public:
	int Run();
	Core* m_engine;
};

