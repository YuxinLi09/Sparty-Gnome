/**
 * \file Door.cpp
 *
 * \author Samuel Duckworth
 */

#include "pch.h"
#include "Door.h"
#include "GnomeGame.h"
#include <string>
#include "Declaration.h"

using namespace std;
using namespace Gdiplus;

/// file of the door image
const wstring DoorFile = L"images/door.png";
/// file for the door open image
const wstring DoorOpenFile = L"images/door-open.png";

/**
 * Door Constructor
 * \param game game we are drawing into
 * \param dec decalrtion we are using
 */
CDoor::CDoor(CGnomeGame* game, std::shared_ptr<CDeclaration> dec) : CItem(game, DoorFile)
{
    mDeclaration = dec;

}

/**
 * Loads the background from the linked Declaration
 * \param node Xml Node that contains the data.
 */
void CDoor::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CItem::XmlLoad(node);
    SetImage(mDeclaration->GetImageName());
}

void CDoor::Collide(CItem* item) {
    SetImageFile(DoorOpenFile);
    if (!GetGnomeGame()->GetVictory())
    {
        if (GetGnomeGame()->GetCnt() != 3)
        {
            GetGnomeGame()->IncrementCounter();
        }
    GetGnomeGame()->SetVictory();
    ClearPresentTime();
    }

}

void CDoor::Draw(Gdiplus::Graphics* graphics) {
    CItem::Draw(graphics);
    if (GetGnomeGame()->GetVictory())
    {
        wstringstream caption;
        const float screenHeight = GetGnomeGame()->GetScreenHeight();
        const float screenWidth = GetGnomeGame()->GetScreenWidth();

        caption << L"Level Completed";

        FontFamily fontFamily(L"Arial");
        Gdiplus::Font font(&fontFamily, 60);
        SolidBrush pink(Color(255, 105, 180));

        const int offset = 24;

        double len = caption.str().size();

        graphics->DrawString(caption.str().c_str(), -1, &font, PointF(Gdiplus::REAL(GetX()- (len * offset)), Gdiplus::REAL(screenHeight / 2)), &pink);
        if (GetPresentTime() > 3)
        {
            GetGnomeGame()->SetProceed(true);
        }
    }
}