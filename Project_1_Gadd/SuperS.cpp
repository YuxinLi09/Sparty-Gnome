/**
 * \file SuperS.cpp
 *
 * \author Yuxin Li
 */

#include "pch.h"
#include "SuperS.h"
#include <string>
#include "Declaration.h"
#include "GnomeGame.h"

using namespace std;
using namespace Gdiplus;

// need to rename
/// the file we are using as base
const wstring filename = L"images/spartan_logo.png";

/**
 * Constructor for the CSuperS diagrams
 * \param game the game we are working on
 * \param dec declaration to linker
 */
CSuperS::CSuperS(CGnomeGame* game, std::shared_ptr<CDeclaration> dec) : CItem(game, filename)
{
    mDeclaration = dec;
}

/**
 * Loads the background from the linked Declaration
 * \param node Xml Node that contains the data.
 */
void CSuperS::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CItem::XmlLoad(node);
    SetImage(mDeclaration->GetImageName());
}

void CSuperS::Collide(CItem* item)
{
    if (CheckPresentable())
    {
        RemoveDisplay();
        GetGnomeGame()->SetSuper(true);
        GetGnomeGame()->ClearSuperTime();
        ClearPresentTime();
    }
}

void CSuperS::Draw(Gdiplus::Graphics* graphics) {
    CItem::Draw(graphics);
    double timePresented = GetPresentTime();
    if (!CheckPresentable())
    {
        if (timePresented < 1) {
            wstringstream caption;

            caption << L"Invincible Mode!";
            double len = caption.str().size();
            FontFamily fontFamily(L"Arial");
            Gdiplus::Font font(&fontFamily, 30);
            SolidBrush green(Color(34, 139, 34)); //forestgreen #228B22

            graphics->DrawString(caption.str().c_str(), -1, &font, PointF(Gdiplus::REAL(GetX()-len*10), Gdiplus::REAL(GetY())), &green);
        }
    }
}
