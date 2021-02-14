#pragma once

#ifdef _AFX
#include "Nalmak_Include.h"


class CEdit;
class  NALMAK_DLL Nalmak_MFC_Utility
{
public:
	static void SetEditBoxFloat(CEdit* _edit, float _value);
	static float GetEditBoxFloat(int _id);
};

#endif