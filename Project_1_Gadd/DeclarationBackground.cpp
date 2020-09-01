#include "pch.h"
#include "DeclarationBackground.h"

using namespace Gdiplus;
using namespace std;

CDeclarationBackground::CDeclarationBackground(const std::wstring& id, const std::wstring& filename) : CDeclaration(id)
{
	mBackground = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mBackground->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}
