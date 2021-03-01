#pragma once
#include "Component.h"

class StageSelectCamera :
	public Component
{
public:
	struct Desc
	{

	};
public:
	StageSelectCamera(Desc* _desc);
	~StageSelectCamera();
private:
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;

private:
	void MoveToPointBySpline(int _index);
	void AddSplinePoint(const Vector3& _point);
private:
	bool m_isAwake = false;
	vector<vector<Vector3>> m_movePoints;

	class MoveBySpline* m_spline;

};

