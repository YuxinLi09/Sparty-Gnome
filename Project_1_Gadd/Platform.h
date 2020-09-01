/**
 * \file Platform.h
 *
 * \author Yiteng Zhang
 *
 * Class defining platforms. Derived from CItem
 */

#pragma once
#include "Item.h"
#include <string>
#include <memory>

class CDeclaration;
 /**
  * Class defining a platform
  */
class CPlatform :
	public CItem
{
public:
    /// Disabling the default constructor
    CPlatform() = delete;

    /// disabling the copy constructor
    CPlatform(const CPlatform&) = delete;

	~CPlatform();

    /// constructor
    CPlatform(CGnomeGame* game, std::shared_ptr<CDeclaration> dec);

    /// load for the platform
    /// \param node the item we are loading 
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /// Draw function for a platform
    virtual void Draw(Gdiplus::Graphics* graphics);

    /// update function for a platform
    virtual void CPlatform::Update();

    /// Gets the wifth of a platform
    /// \return mWidth
    virtual double GetWidth() override { return mWidth; }
    
    /// Gets the height of a platform
    /// \return mHeight
    virtual double GetHeight() override { return mHeight; }
private:
    std::shared_ptr<CDeclaration> mDeclaration; ///< declartion for the item

    int mWidth = 32; ///< base width of a platform
    int mHeight = 32; ///< base height of a platform

    std::shared_ptr<Gdiplus::Bitmap> mRight; ///< right pos of platform
    std::shared_ptr<Gdiplus::Bitmap> mMid; ///< middle pos of platform
    std::shared_ptr<Gdiplus::Bitmap> mLeft;///< left pos of platform


};

