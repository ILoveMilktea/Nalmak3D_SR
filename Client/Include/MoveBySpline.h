#pragma once
#include "Component.h"

class MoveBySpline :
	public Component
{
public:
	struct Desc
	{
		float moveTime = 5.f;
		bool isLoop = false;
		bool isPlay = false;
	};
public:
	MoveBySpline(Desc* _desc);
	~MoveBySpline();

	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;

public:
	void ClearPoints();
	void Play();
	MoveBySpline* AddSplinePoint(const Vector3& _point);
	bool IsPlaying() { return m_isPlay; }
private:
	SplineCurve m_spline;
private:
	float m_timer;
	float m_moveTimePerSec;
	bool m_isLoop;
	bool m_isPlay;
	
};

