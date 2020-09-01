/**
 * \file Villain.cpp
 *
 * \author Ethan Peterson
 */

#include "pch.h"
#include "Villain.h"
#include "DeclarationVillain.h"

using namespace std;
using namespace Gdiplus;

/// Villain filename
const wstring VillainImage = L"images/gnome-sad.png"; // (using gnome-sad.png for now as default)

/**
  * Constructor
  * \param game The game object we are in
  * \param dec The declaration object passed in when reading from xml
  */
CVillain::CVillain(CGnomeGame* game, std::shared_ptr<CDeclaration> dec) : CItem(game, VillainImage)
{
    mDeclaration = dec;
}

/**
*  Destructor
*/
CVillain::~CVillain()
{
}


/**
 * Loads the villain from the linked Declaration
 * \param node Xml Node that contains the data.
 */
void CVillain::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CItem::XmlLoad(node);
    SetImage(mDeclaration->GetImageName());
    mInitPos.Set(GetX(), GetY());
    mPos.Set(GetX(), GetY());
}

/**
 * Used to move the villain up and down as well as across when the gnome moves
 * \param elapsed the amount of time since last frame draw
 */
void CVillain::Update(double elapsed) {
    CItem::Update(elapsed);
    double initSpeed = -0.3;
    int travelD = 150;
    if (CheckPresentable())
    {
        if (abs(mPos.Y() - mInitPos.Y()) >= travelD)
        {
            initSpeed = -initSpeed;
        }

        CVector newV(mV.X(), mV.Y() + initSpeed);
        // Update position
        CVector newP = mPos + newV;// * elapsed;
        mV = newV;
        SetLocation(newP.X(), newP.Y());
        mPos = newP;
    }

}