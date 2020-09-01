/**
 * \file Wall.cpp
 *
 * \author Ethan Peterson
 */
#include "pch.h"
#include "Wall.h"
#include "DeclarationWall.h"

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;

/// Wall filename 1
const wstring WallImage1 = L"images/wall1.png";

/// Wall filename 2
const wstring WallImage2 = L"images/wall2.png";

 /**
  * Constructor
  * \param game The game object we are in
  * \param dec The declaration object passed in when reading from xml
  */
CWall::CWall(CGnomeGame* game, std::shared_ptr<CDeclaration> dec) : CItem(game, WallImage1)
{
    mDeclaration = dec;
}

/**
 * Loads the wall from the linked Declaration
 * \param node Xml Node that contains the data.
 */
void CWall::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CItem::XmlLoad(node);
    SetImage(mDeclaration->GetImageName());
    mHeight = node->GetAttributeIntValue(L"height", 1);
}

/**
 * Draws the wall images onto the screen
 * \param graphics the graphics object being drawn on
 */
void CWall::Draw(Gdiplus::Graphics* graphics)
{
    double wid = this->GetImage()->GetWidth();
    double hit = this->GetImage()->GetHeight();
    const int imageHeight = 32;

    
    /// calculate the blocks needed
    const int count = mHeight / GetImage()->GetHeight();
    /// y position of the wall
    double yPos = GetY() - mHeight / 2;

    for (int i = 0; i < count; i++)
    {
        graphics->DrawImage(this->GetImage().get(),
            float(GetX() - wid / 2), float(yPos),
            (float)this->GetImage()->GetWidth(), (float)(this->GetImage()->GetHeight()+1));

        yPos += imageHeight;
    }
}
