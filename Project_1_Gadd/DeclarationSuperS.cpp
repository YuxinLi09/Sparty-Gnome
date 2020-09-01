/**
 * \file DeclarationSuperS.cpp
 *
 * \author Yuxin Li
 */

#include "pch.h"
#include "DeclarationSuperS.h"

using namespace Gdiplus;
using namespace std;

/**
 *  Constructor
 * \param id the id of what we are loading
 * \param filename the file of what we have to load
 */
CDeclarationSuperS::CDeclarationSuperS(const std::wstring& id, const std::wstring& filename) : CDeclaration(id)
{

    mSuperS = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mSuperS->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}

}