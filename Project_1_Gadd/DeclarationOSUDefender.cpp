/**
 * \file DeclarationOSUDefender.cpp
 *
 * \author Zach Fincher
 */

#include "pch.h"
#include "DeclarationOSUDefender.h"

using namespace Gdiplus;
using namespace std;

/**
 *  Constructor
 * \param id the id of what we are loading
 * \param filename the file of what we have to load
 */
CDeclarationOSUDefender::CDeclarationOSUDefender(const std::wstring& id, const std::wstring& filename) : CDeclaration(id)
{

    mDefender = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mDefender->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}

}