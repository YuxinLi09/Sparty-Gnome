#include "pch.h"
#include "DeclarationTuitionUp.h"

using namespace Gdiplus;
using namespace std;

/**
 *  Constructor
 * \param id the id of what we are loading
 * \param filename the file of what we have to load
 */
CDeclarationTuitionUp::CDeclarationTuitionUp(const std::wstring& id, const std::wstring& filename) : CDeclaration(id)
{

    mTuitionUp = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mTuitionUp->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}

}