
// Nalmak3D_TerrainTool.h : Nalmak3D_TerrainTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CNalmak3D_TerrainToolApp:
// �� Ŭ������ ������ ���ؼ��� Nalmak3D_TerrainTool.cpp�� �����Ͻʽÿ�.
//

class CNalmak3D_TerrainToolApp : public CWinAppEx
{
public:
	CNalmak3D_TerrainToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNalmak3D_TerrainToolApp theApp;
