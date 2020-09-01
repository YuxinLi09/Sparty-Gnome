/**
 * \file TuitionUp.cpp
 *
 * \author Logan Wolfe
 */

#include "pch.h"
#include "TuitionUp.h"
#include <string>
#include "Declaration.h"
#include "GnomeGame.h"


using namespace std;
using namespace Gdiplus;

/// the file we are using as base
const wstring filename = L"images/stanley.png";
/**
 * Constructor for the CTuitionUp diagrams
 * \param game the game we are working on
 * \param dec declaration to linker 
 */
CTuitionUp::CTuitionUp(CGnomeGame* game, std::shared_ptr<CDeclaration> dec) : CItem(game, filename)
{
	/// defalut bonus value
	mValue = 100;
    mDeclaration = dec;
}

/**
 * Loads the background from the linked Declaration
 * \param node Xml Node that contains the data.
 */
void CTuitionUp::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CItem::XmlLoad(node);
    SetImage(mDeclaration->GetImageName());
    mInitPos.Set(GetX(), GetY());
    mPos.Set(GetX(), GetY());
    mV.SetX(0);
    mV.SetY(0);
}

void CTuitionUp::Collide(CItem* item)
{
    if (CheckPresentable() && !mBonus)
    {
        CItem::GetGnomeGame()->SetCoefficient();
        mBonus = true;
        ClearPresentTime();
    }
}

void CTuitionUp::Draw(Gdiplus::Graphics* graphics) {
    CItem::Draw(graphics);
    double timePresented = GetPresentTime();
    if (!CheckPresentable())
    {
        if (timePresented < 1) {
            const int FontSizeChange = 1;
            wstringstream caption;

            caption << L"Tuition Increase!";

            FontFamily fontFamily(L"Arial");
            Gdiplus::Font font(&fontFamily, 30);
            SolidBrush green(Color(34, 139, 34));
            graphics->DrawString(caption.str().c_str(), -1, &font, PointF(Gdiplus::REAL(mInitPos.X()), Gdiplus::REAL(mInitPos.Y())), &green);
        }
    }
    if (mBonus)
    {
        Update();
    }
}

void CTuitionUp::Update()
{
    double initSpeed = -25;
    CVector newV(mV.X(), mV.Y() - initSpeed);
    // Update position
    CVector newP = mPos + newV;
    mV = newV;
    SetLocation(newP.X(), newP.Y());
    mPos = newP;
    if (mPos.Y() == 0)
    {
        RemoveDisplay();
    }
}