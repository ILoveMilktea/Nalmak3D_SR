#pragma once
#include "IRenderer.h"
#include "Nalmak3D_TerrainToolView.h"

class TerrainTool : public IRenderer
{
public:
	struct Desc
	{
		wstring mtrlName = L"default";
		Material* mtrl = nullptr;

		int width = 100;
		int depth = 100;
		float interval = 0.1f;
		float brushPower = 1.f;
		float brushRadius = 1.f;
	};
public:
	TerrainTool(Desc* _desc);
	~TerrainTool();
private:
	static int m_terrainID;
private:
	// IRenderer을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render() override;
	virtual void BindingStreamSource() override;
public:
	float GetHeight(const Vector3& _pos);
private:
	INPUT_LAYOUT_POSITION_NORMAL_UV* m_vertexInfo;
	int m_width;
	int m_depth;
	float m_interval;
	float m_brushPower;
	float m_brushRadius;
	bool m_isChangeData;
	class Camera* m_mainCam;

	class CNalmak3D_TerrainToolView* m_view;
};
