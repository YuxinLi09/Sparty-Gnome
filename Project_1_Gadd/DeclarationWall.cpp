#include "pch.h"
#include "DeclarationWall.h"

using namespace Gdiplus;
using namespace std;

CDeclarationWall::CDeclarationWall(const std::wstring& id, const std::wstring& filename) : CDeclaration(id)
{

	mWall = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mWall->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}
