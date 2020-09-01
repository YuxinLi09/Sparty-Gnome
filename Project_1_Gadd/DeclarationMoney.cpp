/**
 * \file DeclarationMoney.cpp
 *
 * \author Samuel Duckworth
 */

#include "pch.h"
#include "DeclarationMoney.h"

using namespace Gdiplus;
using namespace std;

CDeclarationMoney::CDeclarationMoney(const std::wstring& id, const std::wstring& filename, const int val) : CDeclaration(id)
{
    mMoney = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mMoney->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
	mValue = val;
}
