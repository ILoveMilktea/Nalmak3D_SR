#include "stdafx.h"
#include "..\Include\verticalBillboard.h"




verticalBillboard::verticalBillboard(Desc * _desc)
{
}

verticalBillboard::~verticalBillboard()
{
}

void verticalBillboard::Initialize()
{
	m_mtrl = GetComponent<VIBufferRenderer>()->GetMaterial();
	m_cam = Core::GetInstance()->GetMainCamera();
}

void verticalBillboard::Update()
{
	Matrix billboard;
	D3DXMatrixIdentity(&billboard);
	Matrix view = m_cam->GetViewMatrix();

	billboard._11 = view._11;
	billboard._13 = view._13;
	billboard._31 = view._31;
	billboard._33 = view._33;

	D3DXMatrixInverse(&billboard, 0, &billboard);

	m_mtrl->SetMatrix("g_billboardMatrix", billboard);
}
