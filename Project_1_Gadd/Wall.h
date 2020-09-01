/**
 * \file Wall.h
 *
 * \author Ethan Peterson
 *
 * Class defining a wall object. Derived from CItem
 */

#pragma once

#include <string>
#include "Item.h"

class CDeclaration;

/**
 * Class defining a wall object
 */
class CWall : public CItem
{
public:
    /// Default constructor (disabled)
    CWall() = delete;

    /// Copy constructor (disabled)
    CWall(const CWall&) = delete;

    /// constructor
    CWall(CGnomeGame* game, std::shared_ptr<CDeclaration> dec);

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    virtual void Draw(Gdiplus::Graphics* graphics);

    /// Gets the width of the wall image
    /// \return width as a double
    virtual double GetWidth() override { return mWidth; }

    /// Gets the height of the wall image
    /// \return height as a double
    virtual double GetHeight() override { return mHeight; }

private:
    std::shared_ptr<CDeclaration> mDeclaration; ///< Declaration object used to load from the xml

    /// width of the wall image
    int mWidth = 32;

    /// height of the wall image
    int mHeight;
};
