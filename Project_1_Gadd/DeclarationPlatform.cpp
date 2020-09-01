/**
 * \file DeclarationPlatform.cpp
 *
 * \author Yiteng Zhang
 *
 */

#include "pch.h"
#include "DeclarationPlatform.h"

using namespace Gdiplus;
using namespace std;

CDeclarationPlatform::CDeclarationPlatform(const std::wstring& id, const std::wstring& filename, const std::wstring& filename2, const std::wstring& filename3) : CDeclaration(id)
{
    mPlatformImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mPlatformImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}

	mLeft = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mLeft->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
	mRight = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mRight->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}

}
