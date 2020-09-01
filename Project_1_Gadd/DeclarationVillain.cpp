#include "pch.h"
#include "DeclarationVillain.h"

using namespace Gdiplus;
using namespace std;

CDeclarationVillain::CDeclarationVillain(const std::wstring& id, const std::wstring& filename) : CDeclaration(id)
{

	mVillain = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mVillain->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}

}