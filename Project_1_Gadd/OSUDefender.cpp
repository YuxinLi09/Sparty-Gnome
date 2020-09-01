/**
 * \file OSUDefender.cpp
 *
 * \author Zach Fincher
 */

#include "pch.h"
#include "OSUDefender.h"
#include <string>
#include "Declaration.h"


using namespace std;
using namespace Gdiplus;

/// image for the football player
const wstring filename = L"images/OhioStateFootball-Side.png"; 

/**
 * Constructor for the CTuitionUp diagrams
 * \param game the game we are working on
 * \param dec declaration to linker
 */
COSUDefender::COSUDefender(CGnomeGame* game, std::shared_ptr<CDeclaration> dec) : CItem(game, filename)
{
    /// defalut bonus value
    mDeclaration = dec;

}

/**
 * Loads the background from the linked Declaration
 * \param node Xml Node that contains the data.
 */
void COSUDefender::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CItem::XmlLoad(node);
    SetImage(mDeclaration->GetImageName());
    mInitPos.Set(GetX(), GetY());
    mPos.Set(GetX(), GetY());
}

void COSUDefender::Update(double elapsed)
{
    CItem::Update(elapsed);
    double initSpeed = 0.5;

    CVector newV(mV.X()+initSpeed, mV.Y());
    // Update position
    CVector newP = mPos + newV;
    mV = newV;
    SetLocation(newP.X(), newP.Y());
    mPos = newP;
    if(GetX()>7000)
    {
        mPos.Set(mInitPos.X(), mInitPos.Y());
        mV.SetX(0);
    }

    if (!CheckPresentable())
    {
        if(GetX()<-200)
            AddDisplay();
    }
}