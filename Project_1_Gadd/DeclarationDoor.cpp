/**
 * \file DeclarationDoor.cpp
 *
 * \author Samuel Duckworth
 */

#include "pch.h"
#include "DeclarationDoor.h"

using namespace Gdiplus;
using namespace std;

/**
 *  Constructor
 * \param id the id of what we are loading
 * \param filename the file of what we have to load
 */
CDeclarationDoor::CDeclarationDoor(const std::wstring& id, const std::wstring& filename) : CDeclaration(id)
{

    mDoorImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mDoorImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	};

}