#include "stdafx.h"
#include "MFC_Utility.h"




void MFC_Utility::SetEditBoxFloat(CEdit * _edit, float _value)
{

	CString str;
	str.Format(L"%f", _value);
	_edit->SetWindowTextW(str);
}

void MFC_Utility::SetEditBoxInt(CEdit * _edit, int _value)
{
	CString str;
	str.Format(L"%d", _value);
	_edit->SetWindowTextW(str);
}

