/**
 * \file Item.cpp
 *
 * \author Logan
 */



#include "pch.h"
#include "Item.h"
#include "GnomeGame.h"

class CGnomeGame;

using namespace Gdiplus;
using namespace std;


/**
 *  Constructor 
 * \param game the game we are making
 * \param filename the file we are using
 */
CItem::CItem(CGnomeGame* game, const std::wstring& filename) : mGnomeGame(game)
{
    mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (mItemImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
    }
}

/**
 * Destructor
 */
CItem::~CItem()
{
}

/**
 * Draw our item
 * \param graphics The graphics context to draw on
 */
void CItem::Draw(Gdiplus::Graphics* graphics)
{
	double wid = mItemImage->GetWidth();
	double hit = mItemImage->GetHeight();

	if (mPresented)
	{
		graphics->DrawImage(mItemImage.get(),
			float(GetX() - wid / 2), float(GetY() - hit / 2),
			(float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());
	}
}
/**
 * Save this item to an XML node
 * \param node The node we are going to be a child of
 * \return itemNode the node we are saving
 */
std::shared_ptr<xmlnode::CXmlNode>
CItem::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto itemNode = node->AddChild(L"item");

    itemNode->SetAttribute(L"x", mP.X());
    itemNode->SetAttribute(L"y", mP.Y());

    return itemNode;
}

/**
 * Handle updates in time of the items
 *
 * This is called before we draw and allows us to
 * move the items. This is done by adding our speed multiplied
 * by the amount of time that has elapsed
 * \param elapsed Time elapsed since the class call
 */
void CItem::Update(double elapsed)
{

    mTime += elapsed;
    mGameOverTime += elapsed;
}

/**
 *  Test to see if we hit this object with a mouse.
 * \param x X position to test
 * \param y Y position to test
 * \return true if hit.
 */
bool CItem::HitTest(int x, int y)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image.
    // Subtracting the center makes x, y relative to the center of 
    // the image. Adding half the size makes x, y relative to the top 
    // corner of the image.
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    auto format = mItemImage->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mItemImage->GetPixel((int)testX, (int)testY, &color);
        return color.GetAlpha() != 0;
    }
    else {
        return true;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
    }
}

/**
 * Sets the image of the item
 */
void CItem::SetImage(const std::shared_ptr<Gdiplus::Bitmap>& file)
{
	mItemImage = file;
}

/**
 * Sets the image of the item
 * \param filename file to get image from
 */
void CItem::SetImageFile(const std::wstring& filename)
{
	mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (mItemImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}
void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	mP.Set( node->GetAttributeDoubleValue(L"x", 1) , node->GetAttributeDoubleValue(L"y", 1) );
}

